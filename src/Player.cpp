#include "Player.h"

Player::Player(Color color) : color(color), inCheck(false) {
    
}

Player::~Player() {
    for (Piece* piece : pieces) {
        delete piece;
    }
}

void Player::addPiece(Piece* piece) {
    pieces.push_back(piece);
}

void Player::removePiece(Piece* piece) {
    pieces.erase(std::remove(pieces.begin(), pieces.end(), piece), pieces.end());
    // delete piece;
}

bool Player::makeMove(Board& board, Position from, Position to) {
    Piece* piece = board.getPiece(from);
    if (piece && piece->getColor() == color && piece->isValidMove(board, from, to)) {
        board.movePiece(from, to);
        return true;
    }
    return false;
}

std::vector<Move> Player::generateAllPossibleMoves(const Board& board) const {
    std::vector<Move> allMoves;
    for (Piece* piece : pieces) {
        std::vector<Position> possibleMoves = piece->generatePossibleMoves(board);
        for (const Position& pos : possibleMoves) {
            allMoves.emplace_back(piece->getPosition(), pos, piece, board.getPiece(pos));
        }
    }
    return allMoves;
}