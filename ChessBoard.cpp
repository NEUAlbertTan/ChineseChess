#include "ChessBoard.h"


static int getY(int turn, int y){
    if (turn == 1) {
        return y;
    } else {
        return 11 - y;
    }
}


std::vector<Chess> ChessBoard::genChess(int turn) {
    std::vector<Chess> chess;
    chess.emplace_back(Chess(KING, 5, getY(turn, 1), turn));
    chess.emplace_back(Chess(GUARD,4, getY(turn, 1), turn));
    chess.emplace_back(Chess(GUARD, 6, getY(turn, 1), turn));
    chess.emplace_back(Chess(BISHOP, 3, getY(turn, 1), turn));
    chess.emplace_back(Chess(BISHOP, 7, getY(turn, 1), turn));
    chess.emplace_back(Chess(KNIGHT, 2, getY(turn, 1), turn));
    chess.emplace_back(Chess(KNIGHT, 8, getY(turn, 1), turn));
    chess.emplace_back(Chess(ROOK, 1, getY(turn, 1), turn));
    chess.emplace_back(Chess(ROOK, 9, getY(turn, 1), turn));
    chess.emplace_back(Chess(CANNON, 2, getY(turn, 3), turn));
    chess.emplace_back(Chess(CANNON, 8, getY(turn, 3), turn));
    chess.emplace_back(Chess(PAWN, 1, getY(turn, 4), turn));
    chess.emplace_back(Chess(PAWN, 3, getY(turn, 4), turn));
    chess.emplace_back(Chess(PAWN, 5, getY(turn, 4), turn));
    chess.emplace_back(Chess(PAWN, 7, getY(turn, 4), turn));
    chess.emplace_back(Chess(PAWN, 9, getY(turn, 4), turn));

    return chess;
}


void ChessBoard::drawChessBoard() {
    for (int i = 1; i <= 9; ++i) {
        DrawerHelper::moveCursorTo(i, 0);
        printf("%d", i);
    }
    for (int i = 0; i < 10; ++i) {
        DrawerHelper::moveCursorTo(0, i + 1);
        printf("%c", 'a' + i);
    }

    for (auto & chess : _chess1) {
        chess.drawChess();
    }
    for (auto & chess : _chess2) {
        chess.drawChess();
    }


}
