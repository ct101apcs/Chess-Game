#include "ChessBoard.h"
#define CELL_SIZE 65

void ChessBoard::initializeChessPieces(int row, int col) {
    ChessPiece* piece = nullptr;

    if ((row == 0 && (col == 0 || col == 7)) || (row == 7 && (col == 0 || col == 7))) {
        piece = new Rook(row, col, row == 0 ? PieceColor::White : PieceColor::Black);
    } else if ((row == 0 && (col == 1 || col == 6)) || (row == 7 && (col == 1 || col == 6))) {
        piece = new Knight(row, col, row == 0 ? PieceColor::White : PieceColor::Black);
    } else if ((row == 0 && (col == 2 || col == 5)) || (row == 7 && (col == 2 || col == 5))) {
        piece = new Bishop(row, col, row == 0 ? PieceColor::White : PieceColor::Black);
    } else if ((row == 0 && col == 3) || (row == 7 && col == 4)) {
        piece = new King(row, col, row == 0 ? PieceColor::White : PieceColor::Black);
    } else if ((row == 0 && col == 4) || (row == 7 && col == 3)) {
        piece = new Queen(row, col, row == 0 ? PieceColor::White : PieceColor::Black);
    } else if (row == 1 || row == 6) {
        // piece = new Pawn(row, col, row == 1 ? PieceColor::White : PieceColor::Black);
    }
    if (piece != nullptr) {
        board[row][col] = piece;
    }
}

void ChessBoard::cleanupChessPieces() {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] != nullptr) {
                delete board[row][col];
                board[row][col] = nullptr;
            }
        }
    }
}

void ChessBoard::setupChessBoard() {
    setFixedSize(900, 800);

    QWidget* gridWidget = new QWidget(this);
    gridWidget->setFixedSize(CELL_SIZE * BOARD_SIZE, CELL_SIZE * BOARD_SIZE);

    mainGridLayout = new QGridLayout(gridWidget);

    board.resize(BOARD_SIZE, std::vector<ChessPiece*>(BOARD_SIZE, nullptr));
    selectedPiece = nullptr;

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            initializeChessPieces(row, col);
            QPushButton* square = new QPushButton(gridWidget);
            square->setFixedSize(CELL_SIZE, CELL_SIZE);
            if ((row + col) % 2 != 0) {
                square->setStyleSheet(
                    "QPushButton {"
                    "   background-color: #AFABAB;"
                    "   border: none;"
                    "}"
                    "QPushButton:hover {"
                    "   background-color: rgba(0, 0, 0, 0.2);"
                    "}"
                );
            }
            if (board[row][col] != nullptr) {
                square->setIcon(board[row][col]->getIcon());
            } else {
                square->setEnabled(false);
            }
            connect(square, &QPushButton::clicked, this, [this, row, col]() {
                squareClicked(row, col);
            });
            mainGridLayout->addWidget(square, row, col);
        }
    }

    setCentralWidget(gridWidget);

    QFont wordFont;
    wordFont.setFamily("Cambria Math");
    wordFont.setStyle(QFont::StyleNormal);
    wordFont.setWeight(QFont::Normal);
    wordFont.setPointSize(20);

    turnLabel = new QLabel(this);
    turnLabel->setGeometry(CELL_SIZE * BOARD_SIZE + 20, 30, 150, 30);
    turnLabel->setFont(wordFont);
    turnLabel->setAlignment(Qt::AlignCenter);
    turnLabel->setText(currentPlayer ? "White's turn!" : "Black's turn!");

    currentPlayer = true;  // Assuming white starts
    selectedPiece = nullptr;
}

void ChessBoard::resetChessBoard() {
    cleanupChessPieces();
    setupChessBoard();
}

void ChessBoard::restoreMarkedSquares(const std::vector<std::pair<int, int>>& validMoves
) {
    for (std::pair<int, int> move : selectedPiece->getValidMovesVector()) {
        QLayoutItem* item = mainGridLayout->itemAtPosition(move.first, move.second);
        if (item && item->widget()) {
            if ((move.first + move.second) % 2 != 0) {
                item->widget()->setStyleSheet(
                    "QPushButton {"
                    "   background-color: #AFABAB;"
                    "   border: none;"
                    "}"
                    "QPushButton:hover {"
                    "   background-color: rgba(0, 0, 0, 0.2);"
                    "}"
                );
            } else {
                item->widget()->setStyleSheet("");
            }
            if (board[move.first][move.second] != nullptr) {
                QAbstractButton* button = qobject_cast<QAbstractButton*>(item->widget());
                if (button) {
                    button->setIcon(board[move.first][move.second]->getIcon());
                }
            } else {
                item->widget()->setEnabled(false);
            }
        }
    }
}
void ChessBoard::squareClicked(int row, int col) {
    ChessPiece* clickedPiece = board[row][col];

    if (selectedPiece) {
        restoreMarkedSquares(selectedPiece->getValidMovesVector());
    }

    selectedPiece = clickedPiece;
    selectedPiece->updateValidMovesVector(board);
    for (std::pair<int, int> move : selectedPiece->getValidMovesVector()) {
        QLayoutItem* item = mainGridLayout->itemAtPosition(move.first, move.second);
        if (item && item->widget()) {
            item->widget()->setStyleSheet(
                "background-color: #A9D18E;"
                "border: none;"
            );
        }
    }
}

void ChessBoard::updateBoardGUI() {
    // for (int row = 0; row < 8; row++) {
    //     for (int col = 0; col < 8; col++) {
    //         ChessPiece* piece = board[row][col];
    //         QGridLayout* mainGridLayout =
    //             qobject_cast<QGridLayout*>(&centralWidget->layout());
    //         if (!mainGridLayout) return;
    //         QPushButton* square =
    //             qobject_cast<QPushButton*>(mainGridLayout->itemAtPosition(row,
    //             col)->widget()
    //             );

    //         if (piece != nullptr) {
    //             switch (piece->getPieceType()) {
    //                 case ChessPiece::RookType:
    //                     // Handle Rook icon
    //                     square->setIcon(QIcon("Pictures/WhiteRook.png"));
    //                     break;
    //                 case ChessPiece::KnightType:
    //                     // Handle Knight icon
    //                     square->setIcon(QIcon("Pictures/WhiteKnight.png"));
    //                     break;
    //                 // Handle other piece types similarly
    //                 default:
    //                     square->setIcon(QIcon()
    //                     );  // Clear the icon if no piece is on the square
    //                     break;
    //             }
    //         } else {
    //             square->setIcon(QIcon());  // Clear the icon if no piece is on the
    //             square
    //         }
    //     }
    // }
}
