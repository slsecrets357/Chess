#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Piece.h"
#include "Move.h"
#include "Board.h"

class Player {
private:
    Color color;
    std::vector<Piece*> pieces;
    bool inCheck;

public:
    // Constructor
    Player(Color color);

    // Destructor
    ~Player();

    // Getters
    Color getColor() const;
    bool isInCheck() const;
    const std::vector<Piece*>& getPieces() const;

    // Setters
    void setInCheck(bool inCheck);

    // Add a piece to the player's collection
    void addPiece(Piece* piece);

    // Remove a piece from the player's collection
    void removePiece(Piece* piece);

    // Make a move on the board
    bool makeMove(Board& board, Position from, Position to);

    // Generate all possible moves for the player
    std::vector<Move> generateAllPossibleMoves(const Board& board) const;
};

#endif // PLAYER_H
