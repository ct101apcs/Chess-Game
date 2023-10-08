#ifndef ROOK_H
#define ROOK_H

#include "../ChessPieces.h"

class Rook : public ChessPiece {
   private:
    bool isMovedYet;

   public:
    Rook(
        int row = 0, int col = 0, PieceColor color = PieceColor::White,
        QWidget* parent = nullptr
    )
        : ChessPiece(row, col, color, parent) {
        setIcon(getIcon());
        isMovedYet = false;
    }

    void updateValidMovesVector(const std::vector<std::vector<ChessPiece*>>& board
    ) override;
    void markMovedYet() { isMovedYet = true; }

    QIcon getIcon() const override {
        if (getColor() == PieceColor::White) {
            return QIcon("Pictures/WhiteRook.png");
        } else {
            return QIcon("Pictures/BlackRook.png");
        }
    }
    PieceType getType() const override { return PieceType::RookType; }
    bool getIsMovedYet() const { return isMovedYet; }
};

#endif