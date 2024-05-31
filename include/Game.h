// Game.h
#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"

class Game {
private:
    Board board;
    Player* whitePlayer;
    Player* blackPlayer;
    Player* currentPlayer;

public:
    Game(Player* white, Player* black);
    void startGame();
    void switchPlayer();
    bool isGameOver();
    void processMove(Move move);
};

#endif // GAME_H
