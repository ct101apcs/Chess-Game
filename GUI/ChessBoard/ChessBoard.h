#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <QLabel>

#include "../../GUI/ChessPieces/ChessPieces.h"

class ChessBoard : public QMainWindow {
   public:
    ChessBoard(QWidget* parent = nullptr) : QMainWindow(parent) { setupChessBoard(); }

   public slots:
    void squareClicked(int row, int col);
    void moveMade(int srcRow, int srcCol, int desRow, int desCol);

   private:
    QGridLayout* mainGridLayout;
    ChessPiece* selectedPiece;
    QLabel* turnLabel;
    std::vector<std::vector<ChessPiece*>> board;
    bool currentPlayer;  // true for White, false for Black

    void initializeChessPieces(int row, int col);
    void setupChessBoard();
    void cleanupChessPieces();
    void resetChessBoard();
    void restoreMarkedSquares(const std::vector<std::pair<int, int>>& validMoves);
    void updateBoardGUI();
};

#endif