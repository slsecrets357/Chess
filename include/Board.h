#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Piece.h"
#include "Move.h"
#include <memory>

class Board {
private:
    std::vector<std::vector<std::shared_ptr<Piece>>> board;
    std::vector<std::shared_ptr<Piece>> whitePieces;
    std::vector<std::shared_ptr<Piece>> blackPieces;
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
    std::shared_ptr<Piece> getPiece(Position pos) const;

    // Add a piece to a specific position
    void addPiece(std::shared_ptr<Piece> piece, Position pos);

    // Remove a piece from a specific position
    void removePiece(std::shared_ptr<Piece> piece);

    // Promote a pawn to another piece
    void promotePiece(Position pos, std::shared_ptr<Piece> newPiece);

    // Demote a piece back to a pawn (for undoing promotions)
    void demotePiece(Position pos, std::shared_ptr<Piece> pawnPiece);

    // Check if a move puts the player in check
    bool isCheck(Color color) const;

    bool movePieceConst(Position from, Position to) const;

    void addPieceConst(std::shared_ptr<Piece> piece, Position pos) const;

    // Check if the current player is in checkmate
    bool isCheckmate(Color color) const;

    // Get the current side to move
    Color getSideToMove() const;

    void printSideToMove() const {
        if (sideToMove == Color::WHITE) {
            std::cout << "white player's turn now." << std::endl;
        } else {
            std::cout << "dark player's turn now." << std::endl;
        }
    }

    // Switch the side to move
    void switchSideToMove();

    bool isValidPosition(Position pos) const;
};

#endif // BOARD_H
