#include "Bishop.h"

void Bishop::updateValidMovesVector(const std::vector<std::vector<ChessPiece*>>& board) {
    int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    updateValidMovesForTypicalPieces(board, directions, 4, 14);
}
