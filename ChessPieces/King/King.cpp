#include "King.h"

void King::updateValidMovesVector(const std::vector<std::vector<ChessPiece*>>& board) {
    validMoves.resize(8, std::pair<int, int>({-BOARD_SIZE - 1, -BOARD_SIZE - 1}));
    int row = getCurrentRow(), col = getCurrentCol();

    int directions[8][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1},
                            {-1, 0},  {1, 0},  {0, -1}, {0, 1}};

    for (int i = 0; i < 8; ++i) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
            if ((board[newRow][newCol] == nullptr ||
                 board[newRow][newCol]->getColor() != this->getColor()) &&
                isSquareControlled(board, newRow, newCol)) {
                validMoves.emplace_back(newRow, newCol);
            }
        }
    }
}
