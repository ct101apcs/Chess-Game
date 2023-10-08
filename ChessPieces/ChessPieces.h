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
enum class PieceType { KingType, QueenType, BishopType, KnightType, RookType, PawnType };

class ChessPiece : public QPushButton {
   private:
    int currentRow;
    int currentCol;
    PieceColor color;
    PieceType type;

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
    virtual PieceType getType() const = 0;
    int getCurrentRow() const { return currentRow; }
    int getCurrentCol() const { return currentCol; }
    PieceColor getColor() const { return color; }
    const std::vector<std::pair<int, int>>& getValidMovesVector() const {
        return validMoves;
    }
    bool isSquareControlled(const std::vector<std::vector<ChessPiece*>>&, int, int);

    void updateNewProperties(int desRow, int desCol);

    void updateValidMovesForTypicalPieces(
        const std::vector<std::vector<ChessPiece*>>& board, const int directions[][2],
        int numberOfDirections, int maxValidMoves
    );  // Rook, Queen, Bishop

   private:
    bool isHorizontallyVerticallyAttackingPiece(
        const std::vector<std::vector<ChessPiece*>>&, int, int, int
    );
    bool isDiagonallyAttackingPiece(
        const std::vector<std::vector<ChessPiece*>>&, int, int, int
    );
    bool isSafeHorizontallyVertically(
        const std::vector<std::vector<ChessPiece*>>&, int, int
    );
    bool isSafeDiagonally(const std::vector<std::vector<ChessPiece*>>&, int, int);
    bool isAttackedByKnight(const std::vector<std::vector<ChessPiece*>>&, int, int);
};

#endif
