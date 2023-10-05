#ifndef CHESS_PIECES_H
#define CHESS_PIECES_H

#include <QApplication>
#include <QGridLayout>
#include <QIcon>
#include <QMainWindow>
#include <QPushButton>
#include <cmath>
#include <vector>

constexpr int BOARD_SIZE = 8;

enum class PieceColor { White, Black };

class ChessPiece : public QPushButton {
   private:
    int currentRow;
    int currentCol;
    PieceColor color;

   protected:
    std::vector<std::pair<int, int>> validMoves;

   public:
    ChessPiece(
        int row = 0, int col = 0, PieceColor color = PieceColor::White,
        QWidget* parent = nullptr
    )
        : QPushButton(parent), currentRow(row), currentCol(col), color(color) {
        setFixedSize(50, 50);
    }
    virtual ~ChessPiece() {}

    virtual void updateValidMovesVector(const std::vector<std::vector<ChessPiece*>>& board
    ) = 0;
    virtual QIcon getIcon() const = 0;

    int getCurrentRow() const { return currentRow; }
    int getCurrentCol() const { return currentCol; }
    PieceColor getColor() const { return color; }
    const std::vector<std::pair<int, int>>& getValidMovesVector() const {
        return validMoves;
    }
};

class Rook : public ChessPiece {
   public:
    Rook(
        int row = 0, int col = 0, PieceColor color = PieceColor::White,
        QWidget* parent = nullptr
    )
        : ChessPiece(row, col, color, parent) {
        setIcon(getIcon());
    }

    void updateValidMovesVector(const std::vector<std::vector<ChessPiece*>>& board
    ) override {
        validMoves.resize(14, std::pair<int, int>({-1, -1}));
        int row = getCurrentRow(), col = getCurrentCol();

        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int i = 0; i < 4; ++i) {
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

    QIcon getIcon() const override {
        if (getColor() == PieceColor::White) {
            return QIcon("Pictures/WhiteRook.png");
        } else {
            return QIcon("Pictures/BlackRook.png");
        }
    }
};

class Knight : public ChessPiece {
   public:
    Knight(
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

        int directions[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                                {1, -2},  {1, 2},  {2, -1},  {2, 1}};

        for (int i = 0; i < 8; ++i) {
            int newRow = row + directions[i][0];
            int newCol = col + directions[i][1];

            if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 &&
                newCol < BOARD_SIZE) {
                if (board[newRow][newCol] == nullptr ||
                    board[newRow][newCol]->getColor() != this->getColor()) {
                    validMoves.emplace_back(newRow, newCol);
                }
            }
        }
    }

    QIcon getIcon() const override {
        if (getColor() == PieceColor::White) {
            return QIcon("Pictures/WhiteKnight.png");
        } else {
            return QIcon("Pictures/BlackKnight.png");
        }
    }
};

class Bishop : public ChessPiece {
   public:
    Bishop(
        int row = 0, int col = 0, PieceColor color = PieceColor::White,
        QWidget* parent = nullptr
    )
        : ChessPiece(row, col, color, parent) {
        setIcon(getIcon());
    }

    void updateValidMovesVector(const std::vector<std::vector<ChessPiece*>>& board
    ) override {
        validMoves.resize(14, std::pair<int, int>({-1, -1}));
        int row = getCurrentRow(), col = getCurrentCol();

        int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        for (int i = 0; i < 4; ++i) {
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

    QIcon getIcon() const override {
        if (getColor() == PieceColor::White) {
            return QIcon("Pictures/WhiteBishop.png");
        } else {
            return QIcon("Pictures/BlackBishop.png");
        }
    }
};

class Queen : public ChessPiece {
   public:
    Queen(
        int row = 0, int col = 0, PieceColor color = PieceColor::White,
        QWidget* parent = nullptr
    )
        : ChessPiece(row, col, color, parent) {
        setIcon(getIcon());
    }

    void updateValidMovesVector(const std::vector<std::vector<ChessPiece*>>& board
    ) override {
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

    QIcon getIcon() const override {
        if (getColor() == PieceColor::White) {
            return QIcon("Pictures/WhiteQueen.png");
        } else {
            return QIcon("Pictures/BlackQueen.png");
        }
    }
};

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
