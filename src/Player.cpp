#include "Player.h"

Player::Player(Color color) : color(color), inCheck(false) {
    
}

Player::~Player() {

}

void Player::addPiece(std::shared_ptr<Piece> piece) {
    pieces.push_back(piece);
}

void Player::removePiece(std::shared_ptr<Piece> piece) {
    pieces.erase(std::remove(pieces.begin(), pieces.end(), piece), pieces.end());
    // delete piece;
}

bool Player::makeMove(Board& board, Position from, Position to) {
    std::shared_ptr<Piece> piece = board.getPiece(from);
    if (piece && piece->getColor() == color && piece->isValidMove(board, from, to)) {
        board.movePiece(from, to);
        return true;
    }
    return false;
}

std::vector<Move> Player::generateAllPossibleMoves(const Board& board) const {
    std::vector<Move> allMoves;
    for (std::shared_ptr<Piece> piece : pieces) {
        std::vector<Position> possibleMoves = piece->generatePossibleMoves(board);
        for (const Position& pos : possibleMoves) {
            allMoves.emplace_back(piece->getPosition(), pos, piece, board.getPiece(pos));
        }
    }
    return allMoves;
}