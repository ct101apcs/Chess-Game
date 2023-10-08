#include "ChessPieces.h"

#include "../ChessPieces/Bishop/Bishop.h"
#include "../ChessPieces/Knight/Knight.h"
#include "../ChessPieces/Queen/Queen.h"
#include "../ChessPieces/Rook/Rook.h"

void ChessPiece::updateNewProperties(int desRow, int desCol) {
    currentRow = desRow;
    currentCol = desCol;
}

void ChessPiece::updateValidMovesForTypicalPieces(
    const std::vector<std::vector<ChessPiece*>>& board, const int directions[][2],
    int numberOfDirections, int maxValidMoves
) {
    validMoves.resize(
        maxValidMoves, std::pair<int, int>({-BOARD_SIZE - 1, -BOARD_SIZE - 1})
    );
    int row = getCurrentRow(), col = getCurrentCol();
    for (int i = 0; i < numberOfDirections; ++i) {
        int dRow = directions[i][0];
        int dCol = directions[i][1];

        for (int step = 1; step < BOARD_SIZE; ++step) {
            int newRow = row + dRow * step;
            int newCol = col + dCol * step;

            if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 &&
                newCol < BOARD_SIZE) {
                if (board[newRow][newCol] == nullptr ||
                    board[newRow][newCol]->getColor() != this->getColor()) {
                    validMoves.emplace_back(newRow, newCol);
                }

                if (board[newRow][newCol] != nullptr) {
                    break;
                }
            } else {
                break;
            }
        }
    }
}

bool ChessPiece::isHorizontallyVerticallyAttackingPiece(
    const std::vector<std::vector<ChessPiece*>>& board, int row, int col, int step
) {
    ChessPiece* piece = board[row][col];
    return piece &&
           (piece->getType() == PieceType::RookType ||
            piece->getType() == PieceType::QueenType ||
            (step == 1 && piece->getType() == PieceType::KingType)) &&
           piece->getColor() != this->getColor();
}

bool ChessPiece::isDiagonallyAttackingPiece(
    const std::vector<std::vector<ChessPiece*>>& board, int row, int col, int step
) {
    ChessPiece* piece = board[row][col];
    return piece &&
           (piece->getType() == PieceType::BishopType ||
            piece->getType() == PieceType::QueenType ||
            step == 1 && (piece->getType() == PieceType::KingType) ||
            (step == 1 && piece->getType() == PieceType::PawnType)) &&
           piece->getColor() != this->getColor();
}

bool ChessPiece::isSafeHorizontallyVertically(
    const std::vector<std::vector<ChessPiece*>>& board, int row, int col
) {
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i = 0; i < 4; ++i) {
        int dRow = directions[i][0];
        int dCol = directions[i][1];

        for (int step = 1; step < BOARD_SIZE; ++step) {
            int newRow = row + dRow * step;
            int newCol = col + dCol * step;

            if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 &&
                newCol < BOARD_SIZE) {
                if (!board[newRow][newCol]) {
                    continue;
                }
                if (isHorizontallyVerticallyAttackingPiece(board, newRow, newCol, step)) {
                    return false;
                }
                break;
            } else {
                break;
            }
        }
    }

    return true;
}

bool ChessPiece::isSafeDiagonally(
    const std::vector<std::vector<ChessPiece*>>& board, int row, int col
) {
    int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (int i = 0; i < 4; ++i) {
        int dRow = directions[i][0];
        int dCol = directions[i][1];

        for (int step = 1; step < BOARD_SIZE; ++step) {
            int newRow = row + dRow * step;
            int newCol = col + dCol * step;

            if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 &&
                newCol < BOARD_SIZE) {
                if (!board[newRow][newCol]) {
                    continue;
                }
                if (isDiagonallyAttackingPiece(board, newRow, newCol, step)) {
                    return false;
                }
                break;
            } else {
                break;
            }
        }
    }

    return true;
}

bool ChessPiece::isAttackedByKnight(
    const std::vector<std::vector<ChessPiece*>>& board, int row, int col
) {
    int directions[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                            {1, -2},  {1, 2},  {2, -1},  {2, 1}};

    for (int i = 0; i < 8; ++i) {
        int dRow = directions[i][0];
        int dCol = directions[i][1];

        int newRow = row + dRow;
        int newCol = col + dCol;

        if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
            ChessPiece* piece = board[newRow][newCol];
            if (piece && piece->getType() == PieceType::KnightType &&
                piece->getColor() != this->getColor()) {
                return true;
            }
        }
    }

    return false;
}

bool ChessPiece::isSquareControlled(
    const std::vector<std::vector<ChessPiece*>>& board, int row, int col
) {
    return isSafeHorizontallyVertically(board, row, col) &&
           isSafeDiagonally(board, row, col) && !isAttackedByKnight(board, row, col);
}
