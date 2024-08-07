#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "Position.h"
#include <string>

class Board;

enum class PieceType { ROOK, KNIGHT, BISHOP, QUEEN, KING, PAWN, EMPTY };

enum class Color { WHITE, BLACK };
std::ostream& operator<<(std::ostream& os, Color color);

enum class pieceTypeWithColor { wr, wn, wb, wq, wk, wp, br, bn, bb, bq, bk, bp, empty };

class Piece {
protected:
    PieceType type;
    Color color;
    Position position;

public:
    // Constructor
    Piece(PieceType type, Color color, Position pos) : type(type), color(color), position(pos)
    {
        moves.reserve(64);
    }

    pieceTypeWithColor getPieceTypeWithColor() {
        int pieceType = static_cast<int>(type);
        int pieceColor = static_cast<int>(color);
        return static_cast<pieceTypeWithColor>(pieceType + 6 * pieceColor);
    }
    
    bool hasMoved = false;

    std::vector<Position> moves;

    // Destructor
    virtual ~Piece() {}

    // Getters
    PieceType getType() const {
        return type;
    }
    Color getColor() const {
        return color;
    }
    Position getPosition() const {
        return position;
    }

    // Setters
    void setPosition(Position pos) {
        position = pos;
    }

    virtual bool isCastling(Position to) {
        return false;
    }

    std::vector<Position> filterCheckMoves(const Board& board, std::vector<Position>& moves);

    // Check if a move is valid
    virtual bool isValidMove(const Board& board, Position from, Position to) const = 0;

    // Get the symbol for printing the piece
    virtual char getSymbol() const = 0;

    virtual std::string getPieceType() const = 0;

    // Generate all possible moves for the piece
    virtual std::vector<Position>& generatePossibleMoves(const Board& board) = 0;

    // Get FEN character for the piece
    char getFENChar() const {
        switch (type) {
            case PieceType::ROOK:
                return color == Color::WHITE ? 'R' : 'r';
            case PieceType::KNIGHT:
                return color == Color::WHITE ? 'N' : 'n';
            case PieceType::BISHOP:
                return color == Color::WHITE ? 'B' : 'b';
            case PieceType::QUEEN:
                return color == Color::WHITE ? 'Q' : 'q';
            case PieceType::KING:
                return color == Color::WHITE ? 'K' : 'k';
            case PieceType::PAWN:
                return color == Color::WHITE ? 'P' : 'p';
            default:
                return ' ';
        }
    }
};
std::ostream& operator<<(std::ostream& os, const Piece& piece);

// Derived classes for each type of piece

class King : public Piece {
public:
    King(Color color, Position pos);

    bool isValidMove(const Board& board, Position from, Position to) const override;

    char getSymbol() const override;

    std::string getPieceType() const override;

    bool isCastling(Position to) override;

    std::vector<Position>& generatePossibleMoves(const Board& board) override;

    std::vector<Position> castlingMoves;
};

class Queen : public Piece {
public:
    Queen(Color color, Position pos);

    bool isValidMove(const Board& board, Position from, Position to) const override;

    char getSymbol() const override;
    std::string getPieceType() const override;

    std::vector<Position>& generatePossibleMoves(const Board& board) override;
};

class Bishop : public Piece {
public:
    Bishop(Color color, Position pos);

    bool isValidMove(const Board& board, Position from, Position to) const override;

    char getSymbol() const override;
    std::string getPieceType() const override;

    std::vector<Position>& generatePossibleMoves(const Board& board) override;
};

class Knight : public Piece {
public:
    Knight(Color color, Position pos);

    bool isValidMove(const Board& board, Position from, Position to) const override;

    char getSymbol() const override;
    std::string getPieceType() const override;

    std::vector<Position>& generatePossibleMoves(const Board& board) override;
};

class Rook : public Piece {
public:
    Rook(Color color, Position pos);

    bool isValidMove(const Board& board, Position from, Position to) const override;

    char getSymbol() const override;
    std::string getPieceType() const override;

    std::vector<Position>& generatePossibleMoves(const Board& board) override;
};

class Pawn : public Piece {
public:
    Pawn(Color color, Position pos);

    bool isValidMove(const Board& board, Position from, Position to) const override;

    char getSymbol() const override;
    std::string getPieceType() const override;

    std::vector<Position>& generatePossibleMoves(const Board& board) override;
};

#endif // PIECE_H
