// server.cpp
#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;

class ChatServer {
public:
    ChatServer(boost::asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
          context_(ssl::context::sslv23_server) {
        
        // Load SSL certificate and private key
        context_.use_certificate_chain_file("server.crt");
        context_.use_private_key_file("server.key", ssl::context::pem);
        
        acceptor_.set_option(tcp::acceptor::reuse_address(true));
        start_accept();
    }

private:
    void start_accept() {
        auto new_connection = std::make_shared<ssl::stream<tcp::socket>>(acceptor_.get_executor(), context_);
        acceptor_.async_accept(new_connection->lowest_layer(),
            [this, new_connection](boost::system::error_code ec) {
                if (!ec) {
                    std::cout << "New client connected" << std::endl;
                    new_connection->async_handshake(ssl::stream_base::server,
                        [this, new_connection](const boost::system::error_code& error) {
                            if (!error) {
                                clients_.push_back(new_connection);
                                start_read(new_connection);
                            }
                        });
                }
                start_accept();
            });
    }

    void start_read(std::shared_ptr<ssl::stream<tcp::socket>> socket) {
        auto buffer = std::make_shared<std::string>();
        buffer->resize(1024);
        socket->async_read_some(boost::asio::buffer(*buffer),
            [this, socket, buffer](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    buffer->resize(length);
                    broadcast(*buffer, socket);
                    start_read(socket);
                } else {
                    remove_client(socket);
                }
            });
    }

    void broadcast(const std::string& message, std::shared_ptr<ssl::stream<tcp::socket>> sender) {
        for (auto& client : clients_) {
            if (client != sender) {
                boost::asio::async_write(*client, boost::asio::buffer(message),
                    [this, client](boost::system::error_code ec, std::size_t /*length*/) {
                        if (ec) {
                            remove_client(client);
                        }
                    });
            }
        }
    }

    void remove_client(std::shared_ptr<ssl::stream<tcp::socket>> socket) {
        clients_.erase(std::remove(clients_.begin(), clients_.end(), socket), clients_.end());
        socket->lowest_layer().close();
    }

    tcp::acceptor acceptor_;
    ssl::context context_;
    std::vector<std::shared_ptr<ssl::stream<tcp::socket>>> clients_;
};

int main() {
    try {
        boost::asio::io_context io_context;
        ChatServer server(io_context, 8080);
        std::cout << "Server listening on port 8080" << std::endl;
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}