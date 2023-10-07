#include "Knight.h"

void Knight::updateValidMovesVector(const std::vector<std::vector<ChessPiece*>>& board) {
    validMoves.resize(8, std::pair<int, int>({-1, -1}));
    int row = getCurrentRow(), col = getCurrentCol();

    int directions[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                            {1, -2},  {1, 2},  {2, -1},  {2, 1}};

    for (int i = 0; i < 8; ++i) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
            if (board[newRow][newCol] == nullptr ||
                board[newRow][newCol]->getColor() != this->getColor()) {
                validMoves.emplace_back(newRow, newCol);
            }
        }
    }
}
