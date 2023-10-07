#include "ChessPieces.h"

void ChessPiece::updateNewProperties(int desRow, int desCol) {
    currentRow = desRow;
    currentCol = desCol;
}

void ChessPiece::updateValidMovesForTypicalPieces(
    const std::vector<std::vector<ChessPiece*>>& board, const int directions[][2],
    int numberOfDirections, int maxValidMoves
) {
    validMoves.resize(maxValidMoves, std::pair<int, int>({-1, -1}));
    int row = getCurrentRow(), col = getCurrentCol();
    for (int i = 0; i < numberOfDirections; ++i) {
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
