#ifndef PAWN_H
#define PAWN_h

#include "../ChessPieces/ChessPieces.h"

class Pawn : public ChessPiece {
   public:
    Pawn(
        int row = 0, int col = 0, PieceColor color = PieceColor::White,
        QWidget* parent = nullptr
    )
        : ChessPiece(row, col, color, parent) {
        setIcon(getIcon());
    }

    void updateValidMovesVector(const std::vector<std::vector<ChessPiece*>>& board
    ) override {
        validMoves.resize(6, std::pair<int, int>({-1, -1}));
        int row = getCurrentRow(), col = getCurrentCol();

        int whiteDirections[4][2] = {{-1, 1}, {1, 1}, {2, 0}, {1, 0}};
        int blackDirections[4][2] = {{-1, -1}, {-1, 1}, {-2, 0}, {-1, 0}};

        if (this->getColor() == PieceColor::White) {
            for (int i = (this->getCurrentRow() == 1 ? 2 : 3); i < 4; ++i) {
                int newRow = row + whiteDirections[i][0];
                int newCol = col + whiteDirections[i][1];

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
            for (int i = 0; i < 2; ++i) {
                int newRow = row + whiteDirections[i][0];
                int newCol = col + whiteDirections[i][1];

                if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 &&
                    newCol < BOARD_SIZE) {
                    if (board[newRow][newCol] == nullptr) {
                        continue;
                    }
                    if (board[newRow][newCol]->getColor() != this->getColor()) {
                        validMoves.emplace_back(newRow, newCol);
                    }
                } else {
                    continue;
                }
            }
        } else {
            for (int i = (this->getCurrentRow() == 6 ? 2 : 3); i < 4; ++i) {
                int newRow = row + blackDirections[i][0];
                int newCol = col + blackDirections[i][1];

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
            for (int i = 0; i < 2; ++i) {
                int newRow = row + blackDirections[i][0];
                int newCol = col + blackDirections[i][1];

                if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 &&
                    newCol < BOARD_SIZE) {
                    if (board[newRow][newCol] == nullptr) {
                        continue;
                    }
                    if (board[newRow][newCol]->getColor() != this->getColor()) {
                        validMoves.emplace_back(newRow, newCol);
                    }
                } else {
                    continue;
                }
            }
        }
    }

    QIcon getIcon() const override {
        if (getColor() == PieceColor::White) {
            return QIcon("Pictures/WhitePawn.png");
        } else {
            return QIcon("Pictures/BlackPawn.png");
        }
    }
};

#endif