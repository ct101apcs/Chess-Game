#include "King.h"

bool King::isHorizontallyVerticallyAttackingPiece(
    const std::vector<std::vector<ChessPiece*>>& board, int row, int col
) {
    ChessPiece* piece = board[row][col];
    return piece &&
           (piece->getType() == PieceType::RookType ||
            piece->getType() == PieceType::QueenType ||
            piece->getType() == PieceType::KingType) &&
           piece->getColor() != this->getColor();
}

bool King::isDiagonallyAttackingPiece(
    const std::vector<std::vector<ChessPiece*>>& board, int row, int col
) {
    ChessPiece* piece = board[row][col];
    return piece &&
           (piece->getType() == PieceType::BishopType ||
            piece->getType() == PieceType::QueenType ||
            piece->getType() == PieceType::KingType ||
            piece->getType() == PieceType::PawnType) &&
           piece->getColor() != this->getColor();
}

bool King::isSafeHorizontallyVertically(
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
                if (isHorizontallyVerticallyAttackingPiece(board, newRow, newCol)) {
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

bool King::isSafeDiagonally(
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
                if (isDiagonallyAttackingPiece(board, newRow, newCol)) {
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

bool King::isAttackedByKnight(
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
            if (!board[newRow][newCol]) {
                continue;
            }
            if (board[newRow][newCol]->getType() == PieceType::KnightType &&
                board[newRow][newCol]->getColor() != this->getColor()) {
                return true;
            }
            break;
        } else {
            break;
        }
    }

    return false;
}

bool King::isSquareSafeForKing(
    const std::vector<std::vector<ChessPiece*>>& board, int row, int col
) {
    return isSafeHorizontallyVertically(board, row, col) &&
           isSafeDiagonally(board, row, col) && !isAttackedByKnight(board, row, col);
}

void King::updateValidMovesVector(const std::vector<std::vector<ChessPiece*>>& board) {
    validMoves.resize(8, std::pair<int, int>({-1, -1}));
    int row = getCurrentRow(), col = getCurrentCol();

    int directions[8][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1},
                            {-1, 0},  {1, 0},  {0, -1}, {0, 1}};

    for (int i = 0; i < 8; ++i) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
            if ((board[newRow][newCol] == nullptr ||
                 board[newRow][newCol]->getColor() != this->getColor()) &&
                isSquareSafeForKing(board, newRow, newCol)) {
                validMoves.emplace_back(newRow, newCol);
            }

            if (board[newRow][newCol] != nullptr) {
                continue;
            }
        } else {
            continue;
        }
    }
}
