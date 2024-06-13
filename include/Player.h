#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Piece.h"
#include "Move.h"
#include "Board.h"

class Player {
private:
    Color color;
    std::vector<std::shared_ptr<Piece>> pieces;
    bool inCheck;

public:
    // Constructor
    Player(Color color);

    // Destructor
    ~Player();

    // Getters
    Color getColor() const {
        return color;
    }
    bool isInCheck() const {
        return inCheck;
    }
    const std::vector<std::shared_ptr<Piece>>& getPieces() const {
        return pieces;
    }

    // Setters
    void setInCheck(bool inCheck) {
        this->inCheck = inCheck;
    }

    // Add a piece to the player's collection
    void addPiece(std::shared_ptr<Piece> piece);

    // Remove a piece from the player's collection
    void removePiece(std::shared_ptr<Piece> piece);

    // Make a move on the board
    bool makeMove(Board& board, Position from, Position to);

    // Generate all possible moves for the player
    std::vector<Move> generateAllPossibleMoves(const Board& board) const;
};

#endif // PLAYER_H
