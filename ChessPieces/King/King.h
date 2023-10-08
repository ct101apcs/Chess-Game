#ifndef KING_H
#define KING_h

#include "../../ChessPieces/Bishop/Bishop.h"
#include "../../ChessPieces/Knight/Knight.h"
#include "../../ChessPieces/Pawn/Pawn.h"
#include "../../ChessPieces/Queen/Queen.h"
#include "../../ChessPieces/Rook/Rook.h"

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
    ) override;

    QIcon getIcon() const override {
        if (getColor() == PieceColor::White) {
            return QIcon("Pictures/WhiteKing.png");
        } else {
            return QIcon("Pictures/BlackKing.png");
        }
    }
    PieceType getType() const override { return PieceType::KingType; }
};

#endif