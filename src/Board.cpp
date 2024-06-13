#include "Board.h"
#include "Piece.h"
#include <iostream>

Board::Board() : board(8, std::vector<std::shared_ptr<Piece>>(8, nullptr)), sideToMove(Color::WHITE) {}

// Destructor
Board::~Board() {
    // commented out: no need to delete pieces since they are managed by shared_ptr
    // for (auto& row: board) {
    //     for (std::shared_ptr<Piece> piece: row) {
    //         delete piece;
    //     }
    // }
}

// Initialize the board with pieces in the starting positions
void Board::initialize() {
    // Clear the board
    for (auto& row : board) {
        std::fill(row.begin(), row.end(), nullptr);
    }

    // Add pawns
    for (int col = 0; col < 8; ++col) {
        auto whitePawn = std::make_shared<Pawn>(Color::WHITE, Position(1, col));
        auto blackPawn = std::make_shared<Pawn>(Color::BLACK, Position(6, col));
        board[1][col] = whitePawn;
        board[6][col] = blackPawn;
        whitePieces.push_back(whitePawn);
        blackPieces.push_back(blackPawn);
    }

    // Add rooks
    auto whiteRook1 = std::make_shared<Rook>(Color::WHITE, Position(0, 0));
    auto whiteRook2 = std::make_shared<Rook>(Color::WHITE, Position(0, 7));
    auto blackRook1 = std::make_shared<Rook>(Color::BLACK, Position(7, 0));
    auto blackRook2 = std::make_shared<Rook>(Color::BLACK, Position(7, 7));
    board[0][0] = whiteRook1;
    board[0][7] = whiteRook2;
    board[7][0] = blackRook1;
    board[7][7] = blackRook2;
    whitePieces.push_back(whiteRook1);
    whitePieces.push_back(whiteRook2);
    blackPieces.push_back(blackRook1);
    blackPieces.push_back(blackRook2);

    // Add knights
    auto whiteKnight1 = std::make_shared<Knight>(Color::WHITE, Position(0, 1));
    auto whiteKnight2 = std::make_shared<Knight>(Color::WHITE, Position(0, 6));
    auto blackKnight1 = std::make_shared<Knight>(Color::BLACK, Position(7, 1));
    auto blackKnight2 = std::make_shared<Knight>(Color::BLACK, Position(7, 6));
    board[0][1] = whiteKnight1;
    board[0][6] = whiteKnight2;
    board[7][1] = blackKnight1;
    board[7][6] = blackKnight2;
    whitePieces.push_back(whiteKnight1);
    whitePieces.push_back(whiteKnight2);
    blackPieces.push_back(blackKnight1);
    blackPieces.push_back(blackKnight2);

    // Add bishops
    auto whiteBishop1 = std::make_shared<Bishop>(Color::WHITE, Position(0, 2));
    auto whiteBishop2 = std::make_shared<Bishop>(Color::WHITE, Position(0, 5));
    auto blackBishop1 = std::make_shared<Bishop>(Color::BLACK, Position(7, 2));
    auto blackBishop2 = std::make_shared<Bishop>(Color::BLACK, Position(7, 5));
    board[0][2] = whiteBishop1;
    board[0][5] = whiteBishop2;
    board[7][2] = blackBishop1;
    board[7][5] = blackBishop2;
    whitePieces.push_back(whiteBishop1);
    whitePieces.push_back(whiteBishop2);
    blackPieces.push_back(blackBishop1);
    blackPieces.push_back(blackBishop2);

    // Add queens
    auto whiteQueen = std::make_shared<Queen>(Color::WHITE, Position(0, 3));
    auto blackQueen = std::make_shared<Queen>(Color::BLACK, Position(7, 3));
    board[0][3] = whiteQueen;
    board[7][3] = blackQueen;
    whitePieces.push_back(whiteQueen);
    blackPieces.push_back(blackQueen);

    // Add kings
    auto whiteKing = std::make_shared<King>(Color::WHITE, Position(0, 4));
    auto blackKing = std::make_shared<King>(Color::BLACK, Position(7, 4));
    board[0][4] = whiteKing;
    board[7][4] = blackKing;
    whitePieces.push_back(whiteKing);
    blackPieces.push_back(blackKing);

    // Set the side to move
    sideToMove = Color::WHITE;
}

// Print the board (for debugging purposes)
void Board::printBoard() const {
    std::cout << "  A B C D E F G H" << std::endl;
    for (int row = 7; row >= 0; --row) {
        std::cout << row + 1 << " ";
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
    std::shared_ptr<Piece> piece = getPiece(from);
    if (!piece) {
        std::cout << "you attempted to move a non-existent piece... don't do that again." << std::endl;
        return false;
    }
    if (piece->getColor() != sideToMove) {
        std::cout << "you can't move your opponent's piece... srsly?" << std::endl;
        return false;
    }
    if (piece && piece->isValidMove(*this, from, to)) {
        std::shared_ptr<Piece> targetPiece = getPiece(to);
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
std::shared_ptr<Piece> Board::getPiece(Position pos) const {
    if (isValidPosition(pos)) {
        return board[pos.row][pos.col];
    }
    return nullptr;
}

// Add a piece to a specific position
void Board::addPiece(std::shared_ptr<Piece> piece, Position pos) {
    if (isValidPosition(pos)) {
        board[pos.row][pos.col] = piece;
        piece->setPosition(pos);
    }
}

// Remove a piece from a specific position
void Board::removePiece(std::shared_ptr<Piece> piece) {
    Position pos = piece->getPosition();
    if (isValidPosition(pos) && board[pos.row][pos.col] == piece) {
        board[pos.row][pos.col] = nullptr;
    }
    if (piece->getColor() == Color::WHITE) {
        whitePieces.erase(std::remove(whitePieces.begin(), whitePieces.end(), piece), whitePieces.end());
    } else {
        blackPieces.erase(std::remove(blackPieces.begin(), blackPieces.end(), piece), blackPieces.end());
    }
}

// Promote a pawn to another piece
void Board::promotePiece(Position pos, std::shared_ptr<Piece> newPiece) {
    if (isValidPosition(pos) && board[pos.row][pos.col] != nullptr) {
        removePiece(board[pos.row][pos.col]);
        addPiece(newPiece, pos);
    }
}

// Demote a piece back to a pawn (for undoing promotions)
void Board::demotePiece(Position pos, std::shared_ptr<Piece> pawnPiece) {
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
            std::shared_ptr<Piece> piece = board[row][col];
            if (piece != nullptr && piece->getType() == PieceType::KING) {
                kingPos = piece->getPosition();
                break;
            }
        }
    }

    // Check if any opponent's piece can move to the king's position
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::shared_ptr<Piece> piece = board[row][col];
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
    std::shared_ptr<Piece> piece = getPiece(from);
    if (piece && piece->isValidMove(*this, from, to)) {
        std::shared_ptr<Piece> targetPiece = getPiece(to);
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

void Board::addPieceConst(std::shared_ptr<Piece> piece, Position pos) const {
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
            std::shared_ptr<Piece> piece = board[row][col];
            if (piece != nullptr && piece->getColor() == color) {
                std::vector<Position> moves = piece->generatePossibleMoves(*this);
                for (const auto& move : moves) {
                    std::shared_ptr<Piece> capturedPiece = getPiece(move);
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