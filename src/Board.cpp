#include "Board.h"
#include "Piece.h"
#include <iostream>

Board::Board() : board(8, std::vector<Piece*>(8, nullptr)), sideToMove(Color::WHITE) {}

// Destructor
Board::~Board() {
    for (auto& row: board) {
        for (Piece* piece: row) {
            delete piece;
        }
    }
}

// Initialize the board with pieces in the starting positions
void Board::initialize() {
    // Clear the board
    for (auto& row : board) {
        std::fill(row.begin(), row.end(), nullptr);
    }

    // Add pawns
    for (int col = 0; col < 8; ++col) {
        board[1][col] = new Pawn(Color::WHITE, Position(1, col));
        board[6][col] = new Pawn(Color::BLACK, Position(6, col));
    }

    // Add rooks
    board[0][0] = new Rook(Color::WHITE, Position(0, 0));
    board[0][7] = new Rook(Color::WHITE, Position(0, 7));
    board[7][0] = new Rook(Color::BLACK, Position(7, 0));
    board[7][7] = new Rook(Color::BLACK, Position(7, 7));

    // Add knights
    board[0][1] = new Knight(Color::WHITE, Position(0, 1));
    board[0][6] = new Knight(Color::WHITE, Position(0, 6));
    board[7][1] = new Knight(Color::BLACK, Position(7, 1));
    board[7][6] = new Knight(Color::BLACK, Position(7, 6));

    // Add bishops
    board[0][2] = new Bishop(Color::WHITE, Position(0, 2));
    board[0][5] = new Bishop(Color::WHITE, Position(0, 5));
    board[7][2] = new Bishop(Color::BLACK, Position(7, 2));
    board[7][5] = new Bishop(Color::BLACK, Position(7, 5));

    // Add queens
    board[0][3] = new Queen(Color::WHITE, Position(0, 3));
    board[7][3] = new Queen(Color::BLACK, Position(7, 3));

    // Add kings
    board[0][4] = new King(Color::WHITE, Position(0, 4));
    board[7][4] = new King(Color::BLACK, Position(7, 4));

    // Set the side to move
    sideToMove = Color::WHITE;
}

// Print the board (for debugging purposes)
void Board::printBoard() const {
    for (int row = 7; row >= 0; --row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col] != nullptr) {
                std::cout << board[row][col]->getSymbol() << " ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

// Move a piece from one position to another
bool Board::movePiece(Position from, Position to) {
    Piece* piece = getPiece(from);
    if (piece && piece->isValidMove(*this, from, to)) {
        Piece* targetPiece = getPiece(to);
        if (targetPiece) {
            removePiece(targetPiece);
        }
        board[to.row][to.col] = piece;
        board[from.row][from.col] = nullptr;
        piece->setPosition(to);
        switchSideToMove();
        return true;
    }
    return false;
}

// Get the piece at a specific position
Piece* Board::getPiece(Position pos) const {
    if (isValidPosition(pos)) {
        return board[pos.row][pos.col];
    }
    return nullptr;
}

// Add a piece to a specific position
void Board::addPiece(Piece* piece, Position pos) {
    if (isValidPosition(pos)) {
        board[pos.row][pos.col] = piece;
        piece->setPosition(pos);
    }
}

// Remove a piece from a specific position
void Board::removePiece(Piece* piece) {
    Position pos = piece->getPosition();
    if (isValidPosition(pos) && board[pos.row][pos.col] == piece) {
        board[pos.row][pos.col] = nullptr;
    }
    delete piece;
}

// Promote a pawn to another piece
void Board::promotePiece(Position pos, Piece* newPiece) {
    if (isValidPosition(pos) && board[pos.row][pos.col] != nullptr) {
        removePiece(board[pos.row][pos.col]);
        addPiece(newPiece, pos);
    }
}

// Demote a piece back to a pawn (for undoing promotions)
void Board::demotePiece(Position pos, Piece* pawnPiece) {
    if (isValidPosition(pos) && board[pos.row][pos.col] != nullptr) {
        removePiece(board[pos.row][pos.col]);
        addPiece(pawnPiece, pos);
    }
}

// Check if a move puts the player in check
bool Board::isCheck(Color color) const {
    Position kingPos;
    // Find the king's position
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board[row][col];
            if (piece != nullptr && piece->getType() == PieceType::KING) {
                kingPos = piece->getPosition();
                break;
            }
        }
    }

    // Check if any opponent's piece can move to the king's position
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board[row][col];
            if (piece != nullptr && piece->getColor() != color) {
                if (piece->isValidMove(*this, {row, col}, kingPos)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::movePieceConst(Position from, Position to) const {
    Piece* piece = getPiece(from);
    if (piece && piece->isValidMove(*this, from, to)) {
        Piece* targetPiece = getPiece(to);
        if (targetPiece) {
            const_cast<Board*>(this)->removePiece(targetPiece);
        }
        const_cast<Board*>(this)->board[to.row][to.col] = piece;
        const_cast<Board*>(this)->board[from.row][from.col] = nullptr;
        piece->setPosition(to);
        const_cast<Board*>(this)->switchSideToMove();
        return true;
    }
    return false;
}

void Board::addPieceConst(Piece* piece, Position pos) const {
    if (isValidPosition(pos)) {
        const_cast<Board*>(this)->board[pos.row][pos.col] = piece;
        piece->setPosition(pos);
    }
}

// Check if the current player is in checkmate
bool Board::isCheckmate(Color color) const {
    if (!isCheck(color)) {
        return false;
    }
    // Check if any move can get the player out of check
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board[row][col];
            if (piece != nullptr && piece->getColor() == color) {
                std::vector<Position> moves = piece->generatePossibleMoves(*this);
                for (const auto& move : moves) {
                    Piece* capturedPiece = getPiece(move);
                    Position originalPos = piece->getPosition();
                    movePieceConst(originalPos, move);
                    bool stillInCheck = isCheck(color);
                    movePieceConst(move, originalPos); // Undo the move
                    if (capturedPiece != nullptr) {
                        addPieceConst(capturedPiece, move); // Restore captured piece
                    }
                    if (!stillInCheck) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Get the current side to move
Color Board::getSideToMove() const {
    return sideToMove;
}

// Switch the side to move
void Board::switchSideToMove() {
    sideToMove = (sideToMove == Color::WHITE) ? Color::BLACK : Color::WHITE;
}

bool Board::isValidPosition(Position pos) const {
    return pos.row >= 0 && pos.row < 8 && pos.col >= 0 && pos.col < 8;
}