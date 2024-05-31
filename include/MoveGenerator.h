// MoveGenerator.h
#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "Board.h"
#include <vector>

class MoveGenerator {
public:
    std::vector<Move> generateLegalMoves(const Board& board, Color color);
    bool isMoveLegal(const Board& board, Move move);
    // Other move generation methods
};

#endif // MOVEGENERATOR_H
