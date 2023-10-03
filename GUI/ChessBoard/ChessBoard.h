#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <vector>

#include "../../GUI/ChessPieces/ChessPieces.h"

constexpr int BOARD_SIZE = 8;

class ChessBoard : public QMainWindow {
   public:
    ChessBoard(QWidget* parent = nullptr) : QMainWindow(parent) { setupChessBoard(); }

   public slots:
    void squareClicked();

   private:
    ChessPiece* selectedPiece;
    std::vector<std::vector<ChessPiece*>> board;
    bool currentPlayer;  // true for White, false for Black

    void initializeChessPieces(int row, int col);
    void setupChessBoard();
    void cleanupChessPieces();
    void resetChessBoard();
    void updateBoardGUI();
};

#endif