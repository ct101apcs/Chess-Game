#ifndef CHESS_PIECES_H
#define CHESS_PIECES_H

#include <QApplication>
#include <QGridLayout>
#include <QIcon>
#include <QMainWindow>
#include <QPushButton>
#include <cmath>

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

    virtual bool isMoveValid(int newRow, int newCol) = 0;
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

    bool isMoveValid(int newRow, int newCol) override {
        int rowDiff = newRow - getCurrentRow();
        int colDiff = newCol - getCurrentCol();

        return (rowDiff == 0 && colDiff != 0) || (rowDiff != 0 && colDiff == 0);
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

    bool isMoveValid(int newRow, int newCol) override {
        int rowDiff = abs(newRow - getCurrentRow());
        int colDiff = abs(newCol - getCurrentCol());

        return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
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

    bool isMoveValid(int newRow, int newCol) override {
        int rowDiff = abs(newRow - getCurrentRow());
        int colDiff = abs(newCol - getCurrentCol());

        return rowDiff == colDiff;
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

    bool isMoveValid(int newRow, int newCol) override {
        int rowDiff = abs(newRow - getCurrentRow());
        int colDiff = abs(newCol - getCurrentCol());

        return (rowDiff == 0 && colDiff != 0) || (rowDiff != 0 && colDiff == 0) ||
               (rowDiff == colDiff);
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

    bool isMoveValid(int newRow, int newCol) override {
        int rowDiff = abs(newRow - getCurrentRow());
        int colDiff = abs(newCol - getCurrentCol());

        return (rowDiff <= 1 && colDiff <= 1);
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

    bool isMoveValid(int newRow, int newCol) override {
        int rowDiff = newRow - getCurrentRow();
        int colDiff = abs(newCol - getCurrentCol());

        // Depending on the pawn's color, it can move forward or backward.
        if (getColor() == PieceColor::White) {
            return (rowDiff == -1 && colDiff <= 1);
        } else {
            return (rowDiff == 1 && colDiff <= 1);
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
