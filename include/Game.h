// Game.h
#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include <string.h>
#include "StockfishWrapper.h"

class Game {
public:
    StockfishWrapper stockfish;
    Board board;
    int startGrid = -1;
    int destGrid = -1;
    std::string start;
    std::string dest;
    Position from;
    Position to;
    std::shared_ptr<Piece> selectedPiece;
    bool successfulMove = false;

    Game();
    ~Game();
    void startGame();
    void switchPlayer();
    bool isGameOver();
    void processMove(Move move);
    void printBoard();
    void processInput(std::string input);
    void processInput(int input);
    std::string boardToFEN(); // Convert the current board state to FEN
};

#endif // GAME_H
