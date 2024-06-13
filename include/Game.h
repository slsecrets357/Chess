// Game.h
#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include <string.h>

class Game {
private:
    Board board;
    int startGrid = -1;
    int destGrid = -1;

public:
    Game();
    ~Game();
    void startGame();
    void switchPlayer();
    bool isGameOver();
    void processMove(Move move);
    void printBoard();
};

#endif // GAME_H
