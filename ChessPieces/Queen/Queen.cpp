#include "Queen.h"

void Queen::updateValidMovesVector(const std::vector<std::vector<ChessPiece*>>& board) {
    validMoves.resize(21, std::pair<int, int>({-1, -1}));
    int row = getCurrentRow(), col = getCurrentCol();

    int directions[8][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1},
                            {-1, 0},  {1, 0},  {0, -1}, {0, 1}};

    for (int i = 0; i < 8; ++i) {
        int dRow = directions[i][0];
        int dCol = directions[i][1];

        for (int step = 1; step < BOARD_SIZE; ++step) {
            int newRow = row + dRow * step;
            int newCol = col + dCol * step;

            if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 &&
                newCol < BOARD_SIZE) {
                if (board[newRow][newCol] == nullptr ||
                    board[newRow][newCol]->getColor() != this->getColor()) {
                    validMoves.emplace_back(newRow, newCol);
                }

                if (board[newRow][newCol] != nullptr) {
                    break;
                }
            } else {
                break;
            }
        }
    }
}
