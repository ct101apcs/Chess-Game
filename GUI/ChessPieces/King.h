#ifndef KING_H
#define KING_h

#include "../ChessPieces/ChessPieces.h"

class King : public ChessPiece {
   public:
    King(
        int row = 0, int col = 0, PieceColor color = PieceColor::White,
        QWidget* parent = nullptr
    )
        : ChessPiece(row, col, color, parent) {
        setIcon(getIcon());
    }

    void updateValidMovesVector(const std::vector<std::vector<ChessPiece*>>& board
    ) override {
        validMoves.resize(8, std::pair<int, int>({-1, -1}));
        int row = getCurrentRow(), col = getCurrentCol();

        int directions[8][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1},
                                {-1, 0},  {1, 0},  {0, -1}, {0, 1}};

        for (int i = 0; i < 8; ++i) {
            int newRow = row + directions[i][0];
            int newCol = col + directions[i][1];

            if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 &&
                newCol < BOARD_SIZE) {
                if (board[newRow][newCol] == nullptr ||
                    board[newRow][newCol]->getColor() != this->getColor()) {
                    validMoves.emplace_back(newRow, newCol);
                }

                if (board[newRow][newCol] != nullptr) {
                    continue;
                }
            } else {
                continue;
            }
        }
    }

    QIcon getIcon() const override {
        if (getColor() == PieceColor::White) {
            return QIcon("Pictures/WhiteKing.png");
        } else {
            return QIcon("Pictures/BlackKing.png");
        }
    }
};

#endif