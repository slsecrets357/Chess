#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

class Board;

class Position {
public:
    int row;
    int col;

    // Constructors
    Position(int r, int c) : row(r), col(c) {}
    Position() : row(0), col(0) {}

    // Comparison operators
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }

    bool operator!=(const Position& other) const {
        return !(*this == other);
    }

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Position& pos) {
        os << "(" << pos.row << ", " << pos.col << ")";
        return os;
    }
};

enum class PieceType { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN };
enum class Color { WHITE, BLACK };

class Piece {
protected:
    PieceType type;
    Color color;
    Position position;

public:
    // Constructor
    Piece(PieceType type, Color color, Position pos) : type(type), color(color), position(pos) {}

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

    // Check if a move is valid
    virtual bool isValidMove(const Board& board, Position from, Position to) const = 0;

    // Get the symbol for printing the piece
    virtual char getSymbol() const = 0;

    // Generate all possible moves for the piece
    virtual std::vector<Position> generatePossibleMoves(const Board& board) const = 0;
};

// Derived classes for each type of piece

class King : public Piece {
public:
    King(Color color, Position pos);

    bool isValidMove(const Board& board, Position from, Position to) const override;

    char getSymbol() const override;

    std::vector<Position> generatePossibleMoves(const Board& board) const override;
};

class Queen : public Piece {
public:
    Queen(Color color, Position pos);

    bool isValidMove(const Board& board, Position from, Position to) const override;

    char getSymbol() const override;

    std::vector<Position> generatePossibleMoves(const Board& board) const override;
};

class Bishop : public Piece {
public:
    Bishop(Color color, Position pos);

    bool isValidMove(const Board& board, Position from, Position to) const override;

    char getSymbol() const override;

    std::vector<Position> generatePossibleMoves(const Board& board) const override;
};

class Knight : public Piece {
public:
    Knight(Color color, Position pos);

    bool isValidMove(const Board& board, Position from, Position to) const override;

    char getSymbol() const override;

    std::vector<Position> generatePossibleMoves(const Board& board) const override;
};

class Rook : public Piece {
public:
    Rook(Color color, Position pos);

    bool isValidMove(const Board& board, Position from, Position to) const override;

    char getSymbol() const override;

    std::vector<Position> generatePossibleMoves(const Board& board) const override;
};

class Pawn : public Piece {
public:
    Pawn(Color color, Position pos);

    bool isValidMove(const Board& board, Position from, Position to) const override;

    char getSymbol() const override;

    std::vector<Position> generatePossibleMoves(const Board& board) const override;
};

#endif // PIECE_H
