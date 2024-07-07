// client.cpp
#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;

class ChatClient {
public:
    ChatClient(boost::asio::io_context& io_context, const std::string& host, const std::string& port)
        : context_(ssl::context::sslv23_client),
          socket_(io_context, context_) {
        
        // Optionally, load a certificate for the client
        // socket_.set_verify_mode(ssl::verify_peer);
        // socket_.set_verify_callback(ssl::host_name_verification(host));

        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(host, port);
        boost::asio::connect(socket_.lowest_layer(), endpoints);

        socket_.handshake(ssl::stream_base::client);
        start_read();
    }

    void write(const std::string& message) {
        boost::asio::async_write(socket_, boost::asio::buffer(message),
            [this](boost::system::error_code ec, std::size_t /*length*/) {
                if (ec) {
                    std::cerr << "Write error: " << ec.message() << std::endl;
                    socket_.lowest_layer().close();
                }
            });
    }

private:
    void start_read() {
        boost::asio::async_read_until(socket_, buffer_, '\n',
            [this](boost::system::error_code ec, std::size_t /*length*/) {
                if (!ec) {
                    std::string message{std::istreambuf_iterator<char>(&buffer_), {}};
                    std::cout << "Received: " << message;
                    start_read();
                } else {
                    std::cerr << "Read error: " << ec.message() << std::endl;
                    socket_.lowest_layer().close();
                }
            });
    }

    ssl::context context_;
    ssl::stream<tcp::socket> socket_;
    boost::asio::streambuf buffer_;
};

int main() {
    try {
        boost::asio::io_context io_context;
        ChatClient client(io_context, "server_public_ip_or_domain", "8080");

        std::thread t([&io_context]() { io_context.run(); });

        std::string message;
        while (std::getline(std::cin, message)) {
            message += '\n';
            client.write(message);
        }

        io_context.stop();
        t.join();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}