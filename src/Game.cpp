#include "Game.h"
#include <stdio.h>
#include "Utility.h"

Game::Game(Player* white, Player* black) : whitePlayer(white), blackPlayer(black)
{
    board.initialize();
    currentPlayer = whitePlayer;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board.getPiece(Position(i, j));
            if (piece != nullptr) {
                if (piece->getColor() == Color::WHITE) {
                    whitePlayer->addPiece(piece);
                } else {
                    blackPlayer->addPiece(piece);
                }
            }
        }
    }
}

Game::~Game() {
    delete whitePlayer;
    delete blackPlayer;
}

void Game::startGame() {
    std::cout << "welcome to Simon's Chess Game" << std::endl;
    while (!isGameOver()) {
        auto colorString = board.getSideToMove() == Color::WHITE ? "white" : "black";
        std::cout << colorString << "'s turn" << std::endl;
        printBoard();
        bool successfulMove = false;
        std::string start;
        std::string dest;
        Position from;
        Position to;
        while (!successfulMove) {
            start = getUserInput();
            parseStringInput(start, from);
            dest = getUserInput();
            parseStringInput(dest, to);
            if(currentPlayer->makeMove(board, from, to)) {
                // Additional logic like checking for check or checkmate can be added here
                break;
            } else {
                std::cout << "invalid move from " << from << " to " << to << ". please try again. " << std::endl;
            }
        }
        std::cout << "moving from " << from << " to " << to << std::endl;
        board.printSideToMove();
        switchPlayer();
    }
}
void Game::switchPlayer() {

}
bool Game::isGameOver() {

}
void Game::processMove(Move move) {
    
}

void Game::printBoard() {
    board.printBoard();
}

int main(int argc, char *argv[])
{
    Player* white = new Player(Color::WHITE);
    Player* black = new Player(Color::BLACK);
    Game game(white, black);
    std::cout << "Hello, World!" << std::endl;
    game.startGame();
    game.printBoard();
    return 0;
}
