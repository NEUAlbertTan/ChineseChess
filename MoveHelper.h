#ifndef CHINESECHESS_MOVEHELPER_H
#define CHINESECHESS_MOVEHELPER_H


#include "Chess.h"
#include "ChessBoard.h"
#include "unordered_map"


enum MOVE_RESULT {PLAIN, EAT, MOVE_FAIL};


class MoveHelper {
public:
    static MOVE_RESULT MoveChess(ChessCategory cate, int player, int chessIndex, short tarX, short tarY, ChessBoard & chessBoard) {
        switch (cate) {
            case KING:
                return kingMove(player, chessIndex, tarX, tarY, chessBoard);
            case GUARD:
                return guardMove(player, chessIndex, tarX, tarY, chessBoard);
            case BISHOP:
                return bishopMove(player, chessIndex, tarX, tarY, chessBoard);
            case KNIGHT:
                return knightMove(player, chessIndex, tarX, tarY, chessBoard);
            case ROOK:
                return rookMove(player, chessIndex, tarX, tarY, chessBoard);
            case CANNON:
                return cannonMove(player, chessIndex, tarX, tarY, chessBoard);
            case PAWN:
                return pawnMove(player, chessIndex, tarX, tarY, chessBoard);
            default:
                return MOVE_FAIL;
        }
    }
    
    static MOVE_RESULT kingMove(int player, int chessIndex, short tarX, short tarY, ChessBoard & chessBoard);
    
    static MOVE_RESULT guardMove(int player, int chessIndex, short tarX, short tarY, ChessBoard & chessBoard);
    
    static MOVE_RESULT bishopMove(int player, int chessIndex, short tarX, short tarY, ChessBoard & chessBoard);
    
    static MOVE_RESULT knightMove(int player, int chessIndex, short tarX, short tarY, ChessBoard & chessBoard);
    
    static MOVE_RESULT rookMove(int player, int chessIndex, short tarX, short tarY, ChessBoard & chessBoard);
    
    static MOVE_RESULT cannonMove(int player, int chessIndex, short tarX, short tarY, ChessBoard & chessBoard);
    
    static MOVE_RESULT pawnMove(int player, int chessIndex, short tarX, short tarY, ChessBoard & chessBoard);

    static bool tryEat(int player, short tarX, short tarY, ChessBoard &chessBoard);
};

#endif //CHINESECHESS_MOVEHELPER_H
