#include "ChessBoard.h"

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
        piece = new Pawn(row, col, row == 0 ? PieceColor::White : PieceColor::Black);
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
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QGridLayout* gridLayout = new QGridLayout(centralWidget);
    board.resize(BOARD_SIZE, std::vector<ChessPiece*>(BOARD_SIZE, nullptr));

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            initializeChessPieces(row, col);
            QPushButton* square = new QPushButton(this);
            square->setFixedSize(50, 50);
            if ((row + col) % 2 != 0) {
                square->setStyleSheet(
                    "QPushButton {"
                    "   background-color: rgba(255, 0, 0, 128);"
                    "   border: none;"
                    "}"
                    "QPushButton:hover {"
                    "   background-color: rgba(0, 0, 0, 0.2);"
                    "}"
                );
            }
            connect(square, &QPushButton::clicked, this, &ChessBoard::squareClicked);
            if (board[row][col] != nullptr) {
                square->setIcon(board[row][col]->getIcon());
            }
            gridLayout->addWidget(square, row, col);
        }
    }

    currentPlayer = true;  // Assuming white starts
    selectedPiece = nullptr;
}

void ChessBoard::resetChessBoard() {
    cleanupChessPieces();
    setupChessBoard();
}

void ChessBoard::squareClicked() {
    QPushButton* clickedSquare = qobject_cast<QPushButton*>(sender());

    int row, col;
    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == clickedSquare) {
                break;  // Found the square
            }
        }
        if (col < BOARD_SIZE) {
            break;  // Found the square
        }
    }

    ChessPiece* clickedPiece = board[row][col];

    if (selectedPiece == nullptr) {
        if (clickedPiece != nullptr &&
            (clickedPiece->getColor() == PieceColor::White ? true : false) ==
                currentPlayer) {
            selectedPiece = clickedPiece;
        }
    } else {
        if (selectedPiece->isMoveValid(row, col)) {
            // If the move is valid, perform the move

            // Update the board: move the selected piece to the new position
            board[selectedPiece->getCurrentRow()][selectedPiece->getCurrentCol()] =
                nullptr;
            board[row][col] = selectedPiece;

            // Update the graphical representation of the board
            updateBoardGUI();

            // Deselect the piece
            selectedPiece = nullptr;

            // Switch the current player's turn
            currentPlayer = !currentPlayer;
        } else {
            // The move is invalid; deselect the piece
            selectedPiece = nullptr;
        }
    }
}

void ChessBoard::updateBoardGUI() {
    // for (int row = 0; row < 8; row++) {
    //     for (int col = 0; col < 8; col++) {
    //         ChessPiece* piece = board[row][col];
    //         QGridLayout* gridLayout =
    //             qobject_cast<QGridLayout*>(&centralWidget->layout());
    //         if (!gridLayout) return;
    //         QPushButton* square =
    //             qobject_cast<QPushButton*>(gridLayout->itemAtPosition(row,
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
