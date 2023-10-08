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

void setIcon(
    QAction* action, const QIcon icon, int width = CELL_SIZE / 2,
    int length = CELL_SIZE / 2
) {
    QSize iconSize(width, length);
    QPixmap pixmap = icon.pixmap(iconSize);
    if (action) {
        action->setIcon(QIcon(pixmap));
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

    transferMenu = new QMenu(this);
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
                moveMade(this->selectedPiece, row, col);
            });
        }
    }
}

bool canTransferPawn(ChessPiece* piece) {
    if (piece->getType() == PieceType::PawnType) {
        if ((piece->getColor() == PieceColor::White &&
             piece->getCurrentRow() == BOARD_SIZE - 1) ||
            (piece->getColor() == PieceColor::Black && piece->getCurrentRow() == 0)) {
            return true;
        }
    }
    return false;
}

void ChessBoard::transferPawn(ChessPiece* piece, PieceType newType) {
    int row = piece->getCurrentRow(), col = piece->getCurrentCol();

    switch (newType) {
        case PieceType::QueenType:
            board[row][col] = new Queen(row, col, piece->getColor());
            break;
        case PieceType::RookType:
            board[row][col] = new Rook(row, col, piece->getColor());
            break;
        case PieceType::KnightType:
            board[row][col] = new Knight(row, col, piece->getColor());
            break;
        case PieceType::BishopType:
            board[row][col] = new Bishop(row, col, piece->getColor());
            break;
    }
}

void ChessBoard::drawTransferMenu(ChessPiece* piece) {
    QAction* transferToQueen = transferMenu->addAction("", this, [this, piece]() {
        transferPawn(piece, PieceType::QueenType);
    });
    QAction* transferToRook = transferMenu->addAction("", this, [this, piece]() {
        transferPawn(piece, PieceType::RookType);
    });
    QAction* transferToKnight = transferMenu->addAction("", this, [this, piece]() {
        transferPawn(piece, PieceType::KnightType);
    });
    QAction* transferToBishop = transferMenu->addAction("", this, [this, piece]() {
        transferPawn(piece, PieceType::BishopType);
    });

    setIcon(
        transferToQueen, piece->getColor() == PieceColor::White
                             ? QIcon("Pictures/WhiteQueen.png")
                             : QIcon("Pictures/BlackQueen.png")
    );
    setIcon(
        transferToRook, piece->getColor() == PieceColor::White
                            ? QIcon("Pictures/WhiteRook.png")
                            : QIcon("Pictures/BlackRook.png")
    );
    setIcon(
        transferToKnight, piece->getColor() == PieceColor::White
                              ? QIcon("Pictures/WhiteKnight.png")
                              : QIcon("Pictures/BlackKnight.png")
    );
    setIcon(
        transferToBishop, piece->getColor() == PieceColor::White
                              ? QIcon("Pictures/WhiteBishop.png")
                              : QIcon("Pictures/BlackBishop.png")
    );
    QPoint pointLocation;
    pointLocation.setX(500);
    pointLocation.setY(10);
    transferMenu->exec(this->mapToGlobal(pointLocation));
}

void ChessBoard::moveMade(ChessPiece* srcPiece, int desRow, int desCol) {
    int srcRow = srcPiece->getCurrentRow(), srcCol = srcPiece->getCurrentCol();
    board[srcRow][srcCol]->updateNewProperties(desRow, desCol);
    board[desRow][desCol] = board[srcRow][srcCol];
    board[srcRow][srcCol] = nullptr;

    // Check pawn transfering
    if (canTransferPawn(board[desRow][desCol])) {
        drawTransferMenu(board[desRow][desCol]);
    }

    // Mark king or rook moved yet, then castling is not allowed
    if (board[desRow][desCol]->getType() == PieceType::KingType) {
        King* king = dynamic_cast<King*>(board[desRow][desCol]);
        if (king != nullptr) {
            if (!king->getIsMovedYet()) {
                king->markMovedYet();
            }
            board[desRow][desCol] = king;
        }
    }
    if (board[desRow][desCol]->getType() == PieceType::RookType) {
        Rook* rook = dynamic_cast<Rook*>(board[desRow][desCol]);
        if (rook != nullptr) {
            if (!rook->getIsMovedYet()) {
                rook->markMovedYet();
            }
            board[desRow][desCol] = rook;
        }
    }

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
