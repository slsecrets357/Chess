#ifndef MOVE_H
#define MOVE_H

#include "Piece.h"

// Forward declaration of Board to avoid circular dependency
class Board;

class Move {
private:
    Position from;
    Position to;
    Piece* movedPiece;
    Piece* capturedPiece;
    bool isCastling;
    bool isPromotion;
    Piece* promotionPiece;

public:
    // Constructors
    Move(Position from, Position to, Piece* movedPiece, Piece* capturedPiece = nullptr, 
         bool isCastling = false, bool isPromotion = false, Piece* promotionPiece = nullptr)
        : from(from), to(to), movedPiece(movedPiece), capturedPiece(capturedPiece),
          isCastling(isCastling), isPromotion(isPromotion), promotionPiece(promotionPiece) {}

    // Accessors
    Position getFrom() const { return from; }
    Position getTo() const { return to; }
    Piece* getMovedPiece() const { return movedPiece; }
    Piece* getCapturedPiece() const { return capturedPiece; }
    bool getIsCastling() const { return isCastling; }
    bool getIsPromotion() const { return isPromotion; }
    Piece* getPromotionPiece() const { return promotionPiece; }

    // Execute the move on the board
    void execute(Board& board);

    // Undo the move on the board
    void undo(Board& board);
};

#endif // MOVE_H
