#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <QLabel>
#include <QMenu>

#include "../ChessPieces/King/King.h"

class ChessBoard : public QMainWindow {
   public:
    ChessBoard(QWidget* parent = nullptr) : QMainWindow(parent) { setupChessBoard(); }

   public slots:
    void squareClicked(int row, int col);
    void moveMade(ChessPiece* srcPiece, int desRow, int desCol);
    void transferPawn(ChessPiece* piece, PieceType newType);

   private:
    QGridLayout* mainGridLayout;
    ChessPiece* selectedPiece;
    QLabel* turnLabel;
    QMenu* transferMenu;
    std::vector<std::vector<ChessPiece*>> board;
    bool currentPlayer;  // true for White, false for Black

    void initializeChessPieces(int row, int col);
    void setupChessBoard();
    void cleanupChessPieces();
    void resetChessBoard();
    void restoreMarkedSquares(const std::vector<std::pair<int, int>>& validMoves);
    void updateBoardGUI();

    void drawTransferMenu(ChessPiece* piece);
};

#endif