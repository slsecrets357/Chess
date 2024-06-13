#include "Game.h"
#include <stdio.h>
#include "Utility.h"

Game::Game()
{
    board.initialize();
}

Game::~Game() {

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
        std::shared_ptr<Piece> piece;
        while (!successfulMove) {
            while (startGrid == -1) {
                std::cout << "Please tell me the position of the piece you would like to move ;)";
                start = getUserInput();
                startGrid = parseStringInput(start, from);
                piece = board.getPiece(from);
                if (!piece || piece->getColor() != board.getSideToMove()) {
                    std::cout << "invalid piece at " << from << ". please try again." << std::endl;
                    startGrid = -1;
                }
            }
            std::cout << "starting position is " << from << std::endl;
            std::cout << "Ok, that's a valid piece. Now tell me where. ";
            auto legalMoves = piece->generatePossibleMoves(board);
            std::cout << "here are all the possible moves you could make: \n" << std::endl;
            for (auto pos : legalMoves) {
                std::cout << pos << ", ";
            }
            std::cout << std::endl;
            while (destGrid == -1) {
                dest = getUserInput();
                destGrid = parseStringInput(dest, to);
                if (destGrid < 0) {
                    continue;
                }
                auto destPiece = board.getPiece(to);
                if (destPiece && destPiece->getColor() == board.getSideToMove()) {
                    std::cout << "changing starting position to " << to << ". rechoose where you wanna move it to." << std::endl;
                    startGrid = destGrid; // since user selected a piece of the same color, assume it's the starting position
                    destGrid = -1;
                    break;
                }
            }
            if (startGrid < 0 || destGrid < 0) {
                continue;
            }
            std::cout << "destination position is " << to << std::endl;
            startGrid = -1;
            destGrid = -1;
            if (piece && piece->getColor() == board.getSideToMove() && piece->isValidMove(board, from, to)) {
                board.movePiece(from, to);
                successfulMove = true;
                // Additional logic like checking for check or checkmate can be added here
                break;
            } else {
                std::cout << "invalid move from " << from << " to " << to << ". please try again. " << std::endl;
            }
        }
        std::cout << "moving from " << from << " to " << to << std::endl;
        board.printSideToMove();
        // switchPlayer();
    }
}
void Game::switchPlayer() {

}
bool Game::isGameOver() {
  return false;
}
void Game::processMove(Move move) {
    
}

void Game::printBoard() {
    board.printBoard();
}

int main(int argc, char *argv[])
{
    Game game;
    std::cout << "Hello, World!" << std::endl;
    game.startGame();
    game.printBoard();
    return 0;
}
