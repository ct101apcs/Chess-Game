#include "Queen.h"

void Queen::updateValidMovesVector(const std::vector<std::vector<ChessPiece*>>& board) {
    int directions[8][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1},
                            {-1, 0},  {1, 0},  {0, -1}, {0, 1}};
    updateValidMovesForTypicalPieces(board, directions, 8, 21);
}
