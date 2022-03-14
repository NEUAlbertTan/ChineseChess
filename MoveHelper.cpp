#include "MoveHelper.h"


bool blockedByAlly(short tarX, short tarY, unsigned player, ChessBoard & chessBoard) {
    if (player == 1) {
        for (auto & c : chessBoard.getChess1()) {
            if (c.alive && c.isAtPos(tarX, tarY)) {
                return true;
            }
        }
    }

    if (player == 2) {
        for (auto & c : chessBoard.getChess2()) {
            if (c.alive && c.isAtPos(tarX, tarY)) {
                return true;
            }
        }
    }

    return false;
}


bool MoveHelper::tryEat(int player, short tarX, short tarY, ChessBoard &chessBoard) {
    if (player == 1) {
        for (auto &c : chessBoard.getChess2()) {
            if (c.alive && c.isAtPos(tarX, tarY)) {
                c.alive = false;
                return true;
            }
        }
    } else {
        for (auto &c : chessBoard.getChess1()) {
            if (c.alive && c.isAtPos(tarX, tarY)) {
                c.alive = false;
                return true;
            }
        }
    }

    return false;
}


MOVE_RESULT MoveHelper::kingMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {

    /****** king face to face ******/
    {
        bool faceToFace = false;
        short anotherKingX = 0;

        if (player == 1) {
            for (auto &c: chessBoard.getChess2()) {
                if (c.chessCategory == KING) {
                    anotherKingX = c.x;
                    break;
                }
            }
        }
        if (player == 2) {
            for (auto &c: chessBoard.getChess1()) {
                if (c.chessCategory == KING) {
                    anotherKingX = c.x;
                    break;
                }
            }
        }

        if (anotherKingX == tarX) {
            faceToFace = true;
        }

        if (faceToFace) {
            for (auto &c: chessBoard.getChess1()) {
                if (c.chessCategory != KING && c.alive && c.x == tarX) {
                    faceToFace = false;
                    break;
                }
            }
            for (auto &c: chessBoard.getChess2()) {
                if (c.chessCategory != KING && c.alive && c.x == tarX) {
                    faceToFace = false;
                    break;
                }
            }
        }

        if (faceToFace) {
            return MOVE_FAIL;
        }
    }
    /****** king face to face ******/


    /****** blocked by ally ******/
    if (blockedByAlly(tarX, tarY, player, chessBoard)) {
        return MOVE_FAIL;
    }
    /****** blocked by ally ******/


    /****** detailed move rule ******/
    {
        bool canMove = false;
        if (player == 1) {
            auto tarChess = chessBoard.getChess1()[chessIndex];
            short srcX = tarChess.x, srcY = tarChess.y;
            if (
                (srcX == 5 && srcY == 1 && (tarX == 4 && tarY == 1 || tarX == 6 && tarY == 1 || tarX == 5 && tarY == 2)) ||
                (srcX == 6 && srcY == 1 && (tarX == 5 && tarY == 1 || tarX == 6 && tarY == 2 || tarX == 5 && tarY == 2)) ||
                (srcX == 6 && srcY == 2 && (tarX == 6 && tarY == 1 || tarX == 6 && tarY == 3 || tarX == 5 && tarY == 2)) ||
                (srcX == 6 && srcY == 3 && (tarX == 6 && tarY == 2 || tarX == 5 && tarY == 2 || tarX == 5 && tarY == 3)) ||
                (srcX == 5 && srcY == 3 && (tarX == 4 && tarY == 3 || tarX == 6 && tarY == 3 || tarX == 5 && tarY == 2)) ||
                (srcX == 4 && srcY == 3 && (tarX == 4 && tarY == 2 || tarX == 5 && tarY == 2 || tarX == 5 && tarY == 3)) ||
                (srcX == 4 && srcY == 2 && (tarX == 4 && tarY == 1 || tarX == 5 && tarY == 2 || tarX == 4 && tarY == 3)) ||
                (srcX == 4 && srcY == 1 && (tarX == 4 && tarY == 2 || tarX == 5 && tarY == 2 || tarX == 5 && tarY == 1)) ||
                (srcX == 5 && srcY == 2 && (4 <= tarX && tarX <= 6 && 1 <= tarY && tarY <= 3))
            ) {
                canMove = true;
            }
        } else {
            auto tarChess = chessBoard.getChess2()[chessIndex];
            short srcX = tarChess.x, srcY = tarChess.y;
            if (
                    (srcX == 5 && srcY == 10 && (tarX == 4 && tarY == 10 || tarX == 6 && tarY == 10 || tarX == 5 && tarY == 9)) ||
                    (srcX == 6 && srcY == 10 && (tarX == 5 && tarY == 10 || tarX == 6 && tarY == 9 || tarX == 5 && tarY == 9)) ||
                    (srcX == 6 && srcY == 9 && (tarX == 6 && tarY == 10 || tarX == 6 && tarY == 8 || tarX == 5 && tarY == 9)) ||
                    (srcX == 6 && srcY == 8 && (tarX == 6 && tarY == 9 || tarX == 5 && tarY == 9 || tarX == 5 && tarY == 8)) ||
                    (srcX == 5 && srcY == 8 && (tarX == 4 && tarY == 8 || tarX == 6 && tarY == 8 || tarX == 5 && tarY == 9)) ||
                    (srcX == 4 && srcY == 8 && (tarX == 4 && tarY == 9 || tarX == 5 && tarY == 9 || tarX == 5 && tarY == 8)) ||
                    (srcX == 4 && srcY == 9 && (tarX == 4 && tarY == 10 || tarX == 5 && tarY == 9 || tarX == 4 && tarY == 8)) ||
                    (srcX == 4 && srcY == 10 && (tarX == 4 && tarY == 9 || tarX == 5 && tarY == 9 || tarX == 5 && tarY == 10)) ||
                    (srcX == 5 && srcY == 9 && (4 <= tarX && tarX <= 6 && 8 <= tarY && tarY <= 10))
                    ) {
                canMove = true;
            }
        }
        if (!canMove) {
            return MOVE_FAIL;
        } else {
            bool eatRes = tryEat(player, tarX, tarY, chessBoard);
            if (eatRes) {
                return EAT;
            } else {
                return PLAIN;
            }
        }
    }
    /****** detailed move rule ******/

    return MOVE_FAIL;
}


MOVE_RESULT MoveHelper::guardMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {

    return MOVE_FAIL;
}


MOVE_RESULT MoveHelper::bishopMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {

    return MOVE_FAIL;
}


MOVE_RESULT MoveHelper::knightMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {

    return MOVE_FAIL;
}


MOVE_RESULT MoveHelper::rookMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {

    return MOVE_FAIL;

}


MOVE_RESULT MoveHelper::cannonMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {

    return MOVE_FAIL;

}


MOVE_RESULT MoveHelper::pawnMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {


    return MOVE_FAIL;
}


