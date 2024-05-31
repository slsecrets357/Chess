#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Piece.h"
#include "Move.h"

class Board {
private:
    std::vector<std::vector<Piece*>> board;
    Color sideToMove;

public:
    // Constructor
    Board();

    // Destructor
    ~Board();

    // Initialize the board with pieces in the starting positions
    void initialize();

    // Print the board (for debugging purposes)
    void printBoard() const;

    // Move a piece from one position to another
    bool movePiece(Position from, Position to);

    // Get the piece at a specific position
    Piece* getPiece(Position pos) const;

    // Add a piece to a specific position
    void addPiece(Piece* piece, Position pos);

    // Remove a piece from a specific position
    void removePiece(Piece* piece);

    // Promote a pawn to another piece
    void promotePiece(Position pos, Piece* newPiece);

    // Demote a piece back to a pawn (for undoing promotions)
    void demotePiece(Position pos, Piece* pawnPiece);

    // Check if a move puts the player in check
    bool isCheck(Color color) const;

    bool movePieceConst(Position from, Position to) const;

    void addPieceConst(Piece* piece, Position pos) const;

    // Check if the current player is in checkmate
    bool isCheckmate(Color color) const;

    // Get the current side to move
    Color getSideToMove() const;

    // Switch the side to move
    void switchSideToMove();

    bool isValidPosition(Position pos) const;
};

#endif // BOARD_H
