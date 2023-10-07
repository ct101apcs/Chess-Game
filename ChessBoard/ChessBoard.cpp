#include "ChessBoard.h"

#define CELL_SIZE 65

void setIcon(
    QPushButton* button, const QIcon icon, int width = CELL_SIZE / 2,
    int length = CELL_SIZE / 2
) {
    QSize iconSize(width, length);
    QPixmap pixmap = icon.pixmap(iconSize);
    if (button) {
        button->setIcon(QIcon(pixmap));
        button->setIconSize(iconSize);
    }
}

void ChessBoard::initializeChessPieces(int row, int col) {
    ChessPiece* piece = nullptr;

    if ((row == 0 && (col == 0 || col == 7)) || (row == 7 && (col == 0 || col == 7))) {
        piece = new Rook(row, col, row == 0 ? PieceColor::White : PieceColor::Black);
    } else if ((row == 0 && (col == 1 || col == 6)) || (row == 7 && (col == 1 || col == 6))) {
        piece = new Knight(row, col, row == 0 ? PieceColor::White : PieceColor::Black);
    } else if ((row == 0 && (col == 2 || col == 5)) || (row == 7 && (col == 2 || col == 5))) {
        piece = new Bishop(row, col, row == 0 ? PieceColor::White : PieceColor::Black);
    } else if ((row == 0 && col == 3) || (row == 7 && col == 3)) {
        piece = new King(row, col, row == 0 ? PieceColor::White : PieceColor::Black);
    } else if ((row == 0 && col == 4) || (row == 7 && col == 4)) {
        piece = new Queen(row, col, row == 0 ? PieceColor::White : PieceColor::Black);
    } else if (row == 1 || row == 6) {
        piece = new Pawn(row, col, row == 1 ? PieceColor::White : PieceColor::Black);
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
                setIcon(square, board[row][col]->getIcon());
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
                QPushButton* button = qobject_cast<QPushButton*>(item->widget());
                if (button) {
                    setIcon(button, board[move.first][move.second]->getIcon());
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

    if (!mainGridLayout) {
        return;
    }

    for (std::pair<int, int> move : selectedPiece->getValidMovesVector()) {
        int row = move.first;
        int col = move.second;
        QLayoutItem* item = mainGridLayout->itemAtPosition(row, col);
        QPushButton* button =
            (item ? qobject_cast<QPushButton*>(item->widget()) : new QPushButton);

        button->setStyleSheet(
            "QPushButton {"
            "background-color: #A9D18E;"
            "border: none;"
            "}"
            "QPushButton:hover {"
            "   background-color: #C2E4A6;"
            "}"
        );

        if (selectedPiece->getColor() ==
            (currentPlayer ? PieceColor::White : PieceColor ::Black)) {
            button->setEnabled(true);
            button->disconnect();
            connect(button, &QPushButton::clicked, this, [this, row, col]() {
                restoreMarkedSquares(this->selectedPiece->getValidMovesVector());
                moveMade(
                    this->selectedPiece->getCurrentRow(),
                    this->selectedPiece->getCurrentCol(), row, col
                );
            });
        }
    }
}

void ChessBoard::moveMade(int srcRow, int srcCol, int desRow, int desCol) {
    board[desRow][desCol] = board[srcRow][srcCol];
    board[desRow][desCol]->updateNewPostion(desRow, desCol);
    board[srcRow][srcCol] = nullptr;

    updateBoardGUI();

    currentPlayer = !currentPlayer;
    turnLabel->setText(currentPlayer ? "White's turn!" : "Black's turn!");
}

void ChessBoard::updateBoardGUI() {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            QLayoutItem* item = mainGridLayout->itemAtPosition(row, col);
            QPushButton* button = qobject_cast<QPushButton*>(item->widget());

            if (board[row][col] != nullptr) {
                setIcon(button, board[row][col]->getIcon());
                button->setEnabled(true);
                button->disconnect();
                connect(button, &QPushButton::clicked, this, [this, row, col]() {
                    squareClicked(row, col);
                });
            } else {
                setIcon(button, QIcon());
                button->setEnabled(false);
            }
        }
    }
}
