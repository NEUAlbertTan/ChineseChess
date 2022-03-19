#ifndef CHINESECHESS_MOVEHELPER_H
#define CHINESECHESS_MOVEHELPER_H


#include "Chess.h"
#include "ChessBoard.h"
#include "unordered_map"


enum MOVE_RESULT {PLAIN, EAT, MOVE_FAIL};


class MoveHelper {
public:
    static MOVE_RESULT
    MoveChess(ChessCategory cate, int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard);

    static bool kingCanMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard);

    static bool guardCanMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard);

    static bool bishopCanMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard);

    static bool knightCanMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard);

    static bool rookCanMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard);

    static bool cannonCanMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard);

    static bool pawnCanMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard);

    static bool tryEat(int player, short tarX, short tarY, ChessBoard &chessBoard);

    static bool existChessAtPos(short x, short y, ChessBoard &chessBoard);
};

#endif //CHINESECHESS_MOVEHELPER_H
