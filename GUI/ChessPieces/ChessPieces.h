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

   public:
    ChessPiece(
        int row = 0, int col = 0, PieceColor color = PieceColor::White,
        QWidget* parent = nullptr
    )
        : QPushButton(parent), currentRow(row), currentCol(col), color(color) {
        setFixedSize(50, 50);
    }
    virtual ~ChessPiece() {}

    virtual std::vector<std::pair<int, int>> getvalidMovesVector(
        const std::vector<std::vector<ChessPiece*>>& board, int row, int col
    ) = 0;
    virtual QIcon getIcon() const = 0;

    int getCurrentRow() const { return currentRow; }
    int getCurrentCol() const { return currentCol; }
    PieceColor getColor() const { return color; }
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

    std::vector<std::pair<int, int>> getvalidMovesVector(
        const std::vector<std::vector<ChessPiece*>>& board, int row, int col
    ) override {
        std::vector<std::pair<int, int>> validMoves;
        return validMoves;
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

    std::vector<std::pair<int, int>> getvalidMovesVector(
        const std::vector<std::vector<ChessPiece*>>& board, int row, int col
    ) override {
        std::vector<std::pair<int, int>> validMoves;

        return validMoves;
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

    std::vector<std::pair<int, int>> getvalidMovesVector(
        const std::vector<std::vector<ChessPiece*>>& board, int row, int col
    ) override {
        std::vector<std::pair<int, int>> validMoves;
        return validMoves;
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

    std::vector<std::pair<int, int>> getvalidMovesVector(
        const std::vector<std::vector<ChessPiece*>>& board, int row, int col
    ) override {
        std::vector<std::pair<int, int>> validMoves;
        return validMoves;
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

    std::vector<std::pair<int, int>> getvalidMovesVector(
        const std::vector<std::vector<ChessPiece*>>& board, int row, int col
    ) override {
        std::vector<std::pair<int, int>> validMoves;
        return validMoves;
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

    std::vector<std::pair<int, int>> getvalidMovesVector(
        const std::vector<std::vector<ChessPiece*>>& board, int row, int col
    ) override {
        std::vector<std::pair<int, int>> validMoves;

        for (int colIndex = col - 1; colIndex >= 0; colIndex--) {
            if (!board[row][colIndex]) {
                validMoves.push_back({row, colIndex});
            } else if (board[row][colIndex]->getColor() != this->getColor()) {
                validMoves.push_back({row, colIndex});
                break;
            } else {
                break;
            }
        }

        for (int colIndex = col + 1; colIndex < BOARD_SIZE; colIndex++) {
            if (!board[row][colIndex]) {
                validMoves.push_back({row, colIndex});
            } else if (board[row][colIndex]->getColor() != this->getColor()) {
                validMoves.push_back({row, colIndex});
                break;
            } else {
                break;
            }
        }

        for (int rowIndex = row - 1; rowIndex >= 0; rowIndex--) {
            if (!board[rowIndex][col]) {
                validMoves.push_back({rowIndex, col});
            } else if (board[rowIndex][col]->getColor() != this->getColor()) {
                validMoves.push_back({rowIndex, col});
                break;
            } else {
                break;
            }
        }

        for (int rowIndex = row + 1; rowIndex < BOARD_SIZE; rowIndex++) {
            if (!board[rowIndex][col]) {
                validMoves.push_back({rowIndex, col});
            } else if (board[rowIndex][col]->getColor() != this->getColor()) {
                validMoves.push_back({rowIndex, col});
                break;
            } else {
                break;
            }
        }

        return validMoves;
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
