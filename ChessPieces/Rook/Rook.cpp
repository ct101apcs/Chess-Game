#include "Rook.h"

void Rook::updateValidMovesVector(const std::vector<std::vector<ChessPiece*>>& board) {
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    updateValidMovesForTypicalPieces(board, directions, 4, 14);
}
