#include "MoveHelper.h"


bool MoveHelper::existChessAtPos(short x, short y, ChessBoard &chessBoard) {
    for (auto &c: chessBoard.getChess1()) {
        if (c.alive && c.isAtPos(x, y)) {
            return true;
        }
    }
    for (auto &c: chessBoard.getChess2()) {
        if (c.alive && c.isAtPos(x, y)) {
            return true;
        }
    }

    return false;
}


bool blockedByAlly(short tarX, short tarY, unsigned player, ChessBoard &chessBoard) {
    if (player == 1) {
        for (auto &c: chessBoard.getChess1()) {
            if (c.alive && c.isAtPos(tarX, tarY)) {
                return true;
            }
        }
    }

    if (player == 2) {
        for (auto &c: chessBoard.getChess2()) {
            if (c.alive && c.isAtPos(tarX, tarY)) {
                return true;
            }
        }
    }

    return false;
}


bool leadToKingFaceToFace(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {
    int srcX, srcY;
    if (player == 1) {
        auto c = chessBoard.getChess1()[chessIndex];
        srcX = c.x;
        srcY = c.y;
    } else {
        auto c = chessBoard.getChess2()[chessIndex];
        srcX = c.x;
        srcY = c.y;
    }
    short king1x = 0, king1y = 0, king2x = 0, king2y = 0;
    for (auto &c: chessBoard.getChess1()) {
        if (c.chessCategory == KING) {
            king1x = c.x;
            king1y = c.y;
            break;
        }
    }
    for (auto &c: chessBoard.getChess2()) {
        if (c.chessCategory == KING) {
            king2x = c.x;
            king2y = c.y;
            break;
        }
    }

    if (king1x != king2x) {
        return false;
    }

    if (king1x != srcX) {
        return false;
    }

    int chessCountBetweenKings = 0;
    for (auto &c: chessBoard.getChess1()) {
        if (c.alive && c.x == king1x && (king1y < c.y && c.y < king2y || king1y > c.y && c.y > king2y)) {
            ++chessCountBetweenKings;
            break;
        }
    }
    for (auto &c: chessBoard.getChess2()) {
        if (c.alive && c.x == king1x && (king1y < c.y && c.y < king2y || king1y > c.y && c.y > king2y)) {
            ++chessCountBetweenKings;
            break;
        }
    }

    return chessCountBetweenKings == 1 && tarX != srcX;
}


bool MoveHelper::tryEat(int player, short tarX, short tarY, ChessBoard &chessBoard) {
    if (player == 1) {
        for (auto &c: chessBoard.getChess2()) {
            if (c.alive && c.isAtPos(tarX, tarY)) {
                c.alive = false;
                return true;
            }
        }
    } else {
        for (auto &c: chessBoard.getChess1()) {
            if (c.alive && c.isAtPos(tarX, tarY)) {
                c.alive = false;
                return true;
            }
        }
    }

    return false;
}


bool MoveHelper::kingCanMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {

    /****** king face to face ******/

    bool faceToFace = false;
    short anotherKingX = 0, anotherKingY = 0;

    if (player == 1) {
        for (auto &c: chessBoard.getChess2()) {
            if (c.chessCategory == KING) {
                anotherKingX = c.x;
                anotherKingY = c.y;
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
            if (c.alive && c.x == tarX && (tarY < c.y && c.y < anotherKingY || tarY > c.y && c.y > anotherKingY)) {
                faceToFace = false;
                break;
            }
        }
        for (auto &c: chessBoard.getChess2()) {
            if (c.alive && c.x == tarX && (tarY < c.y && c.y < anotherKingY || tarY > c.y && c.y > anotherKingY)) {
                faceToFace = false;
                break;
            }
        }
    }

    if (faceToFace) {
        return false;
    }

    /****** king face to face ******/

    /****** detailed move rule ******/

    bool canMove = false;
    if (player == 1) {
        auto tarChess = chessBoard.getChess1()[chessIndex];
        short srcX = tarChess.x, srcY = tarChess.y;
        if (
                (srcX == 5 && srcY == 1 &&
                 (tarX == 4 && tarY == 1 || tarX == 6 && tarY == 1 || tarX == 5 && tarY == 2)) ||
                (srcX == 6 && srcY == 1 &&
                 (tarX == 5 && tarY == 1 || tarX == 6 && tarY == 2 || tarX == 5 && tarY == 2)) ||
                (srcX == 6 && srcY == 2 &&
                 (tarX == 6 && tarY == 1 || tarX == 6 && tarY == 3 || tarX == 5 && tarY == 2)) ||
                (srcX == 6 && srcY == 3 &&
                 (tarX == 6 && tarY == 2 || tarX == 5 && tarY == 2 || tarX == 5 && tarY == 3)) ||
                (srcX == 5 && srcY == 3 &&
                 (tarX == 4 && tarY == 3 || tarX == 6 && tarY == 3 || tarX == 5 && tarY == 2)) ||
                (srcX == 4 && srcY == 3 &&
                 (tarX == 4 && tarY == 2 || tarX == 5 && tarY == 2 || tarX == 5 && tarY == 3)) ||
                (srcX == 4 && srcY == 2 &&
                 (tarX == 4 && tarY == 1 || tarX == 5 && tarY == 2 || tarX == 4 && tarY == 3)) ||
                (srcX == 4 && srcY == 1 &&
                 (tarX == 4 && tarY == 2 || tarX == 5 && tarY == 2 || tarX == 5 && tarY == 1)) ||
                (srcX == 5 && srcY == 2 && (4 <= tarX && tarX <= 6 && 1 <= tarY && tarY <= 3))
                ) {
            canMove = true;
        }
    } else {
        auto tarChess = chessBoard.getChess2()[chessIndex];
        short srcX = tarChess.x, srcY = tarChess.y;
        if (
                (srcX == 5 && srcY == 10 &&
                 (tarX == 4 && tarY == 10 || tarX == 6 && tarY == 10 || tarX == 5 && tarY == 9)) ||
                (srcX == 6 && srcY == 10 &&
                 (tarX == 5 && tarY == 10 || tarX == 6 && tarY == 9 || tarX == 5 && tarY == 9)) ||
                (srcX == 6 && srcY == 9 &&
                 (tarX == 6 && tarY == 10 || tarX == 6 && tarY == 8 || tarX == 5 && tarY == 9)) ||
                (srcX == 6 && srcY == 8 &&
                 (tarX == 6 && tarY == 9 || tarX == 5 && tarY == 9 || tarX == 5 && tarY == 8)) ||
                (srcX == 5 && srcY == 8 &&
                 (tarX == 4 && tarY == 8 || tarX == 6 && tarY == 8 || tarX == 5 && tarY == 9)) ||
                (srcX == 4 && srcY == 8 &&
                 (tarX == 4 && tarY == 9 || tarX == 5 && tarY == 9 || tarX == 5 && tarY == 8)) ||
                (srcX == 4 && srcY == 9 &&
                 (tarX == 4 && tarY == 10 || tarX == 5 && tarY == 9 || tarX == 4 && tarY == 8)) ||
                (srcX == 4 && srcY == 10 &&
                 (tarX == 4 && tarY == 9 || tarX == 5 && tarY == 9 || tarX == 5 && tarY == 10)) ||
                (srcX == 5 && srcY == 9 && (4 <= tarX && tarX <= 6 && 8 <= tarY && tarY <= 10))
                ) {
            canMove = true;
        }
    }
    /****** detailed move rule ******/
    return canMove;
}


bool MoveHelper::guardCanMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {

    /****** detailed move rule ******/
    bool canMove = false;
    if (player == 1) {
        auto tarChess = chessBoard.getChess1()[chessIndex];
        short srcX = tarChess.x, srcY = tarChess.y;
        if (
                (srcX != 5 && srcY != 2 && (tarX == 5 && tarY == 2)) ||
                (srcX == 5 && srcY == 2 && (tarX == 4 && tarY == 1) || (tarX == 6 && tarY == 1) ||
                 (tarX == 4 && tarY == 3) || (tarX == 6 && tarY == 3))
                ) {
            canMove = true;
        }
    } else {
        auto tarChess = chessBoard.getChess1()[chessIndex];
        short srcX = tarChess.x, srcY = tarChess.y;
        if (
                (srcX != 5 && srcY != 9 && (tarX == 5 && tarY == 9)) ||
                (srcX == 5 && srcY == 9 && (tarX == 4 && tarY == 10) || (tarX == 6 && tarY == 10) ||
                 (tarX == 4 && tarY == 8) || (tarX == 6 && tarY == 8))
                ) {
            canMove = true;
        }
    }
    return canMove;
    /****** detailed move rule ******/
}


bool MoveHelper::bishopCanMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {

    /****** detailed move rule ******/
    bool canMove = false;
    if (player == 1) {
        auto tarChess = chessBoard.getChess1()[chessIndex];
        short srcX = tarChess.x, srcY = tarChess.y;
        if (
            (srcX == 3 && srcY == 1 && ((tarX == 1 && tarY == 3 && !existChessAtPos(2, 2, chessBoard)) || (tarX == 5 && tarY == 3 && !existChessAtPos(4, 2, chessBoard))) ) ||
            (srcX == 1 && srcY == 3 && ((tarX == 3 && tarY == 1 && !existChessAtPos(2, 2, chessBoard)) || (tarX == 3 && tarY == 5 && !existChessAtPos(2, 4, chessBoard))) ) ||
            (srcX == 3 && srcY == 5 && ((tarX == 1 && tarY == 3 && !existChessAtPos(2, 4, chessBoard)) || (tarX == 5 && tarY == 3 && !existChessAtPos(4, 4, chessBoard))) ) ||
            (srcX == 5 && srcY == 3 && ((tarX == 3 && tarY == 1 && !existChessAtPos(4, 2, chessBoard)) || (tarX == 3 && tarY == 5 && !existChessAtPos(4, 4, chessBoard)) || (tarX == 7 && tarY == 5 && !existChessAtPos(6, 4, chessBoard))) || (tarX == 7 && tarY == 1 && !existChessAtPos(6, 2, chessBoard)) ) ||
            (srcX == 7 && srcY == 5 && ((tarX == 5 && tarY == 3 && !existChessAtPos(6, 4, chessBoard)) || (tarX == 9 && tarY == 3 && !existChessAtPos(8, 4, chessBoard))) ) ||
            (srcX == 9 && srcY == 3 && ((tarX == 7 && tarY == 5 && !existChessAtPos(8, 4, chessBoard)) || (tarX == 7 && tarY == 1 && !existChessAtPos(8, 2, chessBoard))) ) ||
            (srcX == 7 && srcY == 1 && ((tarX == 9 && tarY == 3 && !existChessAtPos(8, 2, chessBoard)) || (tarX == 5 && tarY == 3 && !existChessAtPos(6, 4, chessBoard))) )
        ) {
            canMove = true;
        }
    } else {
        auto tarChess = chessBoard.getChess1()[chessIndex];
        short srcX = tarChess.x, srcY = tarChess.y;
        if (
            (srcX == 3 && srcY == 10 && ((tarX == 1 && tarY == 8 && !existChessAtPos(2, 9, chessBoard)) || (tarX == 5 && tarY == 8 && !existChessAtPos(4, 9, chessBoard))) ) ||
            (srcX == 1 && srcY == 8 && ((tarX == 3 && tarY == 10 && !existChessAtPos(2, 9, chessBoard)) || (tarX == 3 && tarY == 6 && !existChessAtPos(2, 7, chessBoard))) ) ||
            (srcX == 3 && srcY == 6 && ((tarX == 1 && tarY == 8 && !existChessAtPos(2, 7, chessBoard)) || (tarX == 5 && tarY == 8 && !existChessAtPos(4, 7, chessBoard))) ) ||
            (srcX == 5 && srcY == 8 && ((tarX == 3 && tarY == 10 && !existChessAtPos(4, 9, chessBoard)) || (tarX == 3 && tarY == 6 && !existChessAtPos(4, 7, chessBoard)) || (tarX == 7 && tarY == 6 && !existChessAtPos(6, 7, chessBoard))) || (tarX == 7 && tarY == 10 && !existChessAtPos(6, 9, chessBoard)) ) ||
            (srcX == 7 && srcY == 6 && ((tarX == 5 && tarY == 8 && !existChessAtPos(6, 7, chessBoard)) || (tarX == 9 && tarY == 8 && !existChessAtPos(8, 7, chessBoard))) ) ||
            (srcX == 9 && srcY == 8 && ((tarX == 7 && tarY == 6 && !existChessAtPos(8, 7, chessBoard)) || (tarX == 7 && tarY == 10 && !existChessAtPos(8, 9, chessBoard))) ) ||
            (srcX == 7 && srcY == 10 && ((tarX == 9 && tarY == 8 && !existChessAtPos(8, 9, chessBoard)) || (tarX == 5 && tarY == 8 && !existChessAtPos(6, 7, chessBoard))) )
        ) {
            canMove = true;
        }
    }
    return canMove;

}


bool MoveHelper::knightCanMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {
    int srcX, srcY;
    if (player == 1) {
        auto c = chessBoard.getChess1()[chessIndex];
        srcX = c.x;
        srcY = c.y;
    } else {
        auto c = chessBoard.getChess2()[chessIndex];
        srcX = c.x;
        srcY = c.y;
    }

    if (abs(tarY - srcY) == 2 && abs(tarX - srcX) == 1) {
        if (!existChessAtPos(srcX, (tarY + srcY) / 2, chessBoard)) {
            return true;
        }
    } else if (abs(tarY - srcY) == 1 && abs(tarX - srcX) == 2) {
        if (!existChessAtPos((tarX + srcX) / 2, srcY, chessBoard)) {
            return true;
        }
    }

    return false;
}


bool MoveHelper::rookCanMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {
    int srcX, srcY;
    if (player == 1) {
        auto c = chessBoard.getChess1()[chessIndex];
        srcX = c.x;
        srcY = c.y;
    } else {
        auto c = chessBoard.getChess2()[chessIndex];
        srcX = c.x;
        srcY = c.y;
    }

    if (tarX == srcX) {
        int smallerY, greaterY;
        if (tarY > srcY) {
            smallerY = srcY;
            greaterY = tarY;
        } else {
            smallerY = tarY;
            greaterY = srcY;
        }
        for (int y = smallerY + 1; y < greaterY - 1; ++y) {
            if (existChessAtPos(tarX, y, chessBoard)) {
                return false;
            }
        }
    } else if (tarY == srcY) {
        int smallerX, greaterX;
        if (tarX > srcX) {
            smallerX = srcX;
            greaterX = tarX;
        } else {
            smallerX = tarX;
            greaterX = srcX;
        }
        for (int x = smallerX + 1; x < greaterX - 1; ++x) {
            if (existChessAtPos(x, tarY, chessBoard)) {
                return false;
            }
        }
    } else {
        return false;
    }

    return true;
}


bool MoveHelper::cannonCanMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {
    int srcX, srcY;
    if (player == 1) {
        auto c = chessBoard.getChess1()[chessIndex];
        srcX = c.x;
        srcY = c.y;
    } else {
        auto c = chessBoard.getChess2()[chessIndex];
        srcX = c.x;
        srcY = c.y;
    }

    // plain move
    if (tarX == srcX) {
        int smallerY, greaterY;
        if (tarY > srcY) {
            smallerY = srcY;
            greaterY = tarY;
        } else {
            smallerY = tarY;
            greaterY = srcY;
        }
        int chessCountBetween = 0;
        for (int y = smallerY + 1; y < greaterY - 1; ++y) {
            if (existChessAtPos(tarX, y, chessBoard)) {
                ++chessCountBetween;
            }
        }
        if (chessCountBetween == 0) {
            // whether occupied by is handled before, so if tar lays a chess, it must be an enemy chess, which makes this move invalid.
            return !existChessAtPos(tarX, tarY, chessBoard);
        } else if (chessCountBetween == 1) {
            // it must be an enemy chess at tar, which makes this move an EAT move.
            return existChessAtPos(tarX, tarY, chessBoard);
        } else {
            return false;
        }
    } else if (tarY == srcY) {
        int smallerX, greaterX;
        if (tarX > srcX) {
            smallerX = srcX;
            greaterX = tarX;
        } else {
            smallerX = tarX;
            greaterX = srcX;
        }
        int chessCountBetween = 0;
        for (int x = smallerX + 1; x < greaterX - 1; ++x) {
            if (existChessAtPos(x, tarY, chessBoard)) {
                ++chessCountBetween;
            }
        }
        if (chessCountBetween == 0) {
            // whether occupied by is handled before, so if tar lays a chess, it must be an enemy chess, which makes this move invalid.
            return !existChessAtPos(tarX, tarY, chessBoard);
        } else if (chessCountBetween == 1) {
            // it must be an enemy chess at tar, which makes this move an EAT move.
            return existChessAtPos(tarX, tarY, chessBoard);
        } else {
            return false;
        }
    } else {
        return false;
    }
}


bool MoveHelper::pawnCanMove(int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {
    int srcX, srcY;
    if (player == 1) {
        auto c = chessBoard.getChess1()[chessIndex];
        srcX = c.x;
        srcY = c.y;
    } else {
        auto c = chessBoard.getChess2()[chessIndex];
        srcX = c.x;
        srcY = c.y;
    }

    if (player == 1) {
        if ((srcY <= 5 && tarY - srcY == 1 && srcX == tarX)
        || (srcY >= 6 && ((srcY == tarY && abs(srcX - tarX) == 1) || (tarY - srcY == 1 && tarX == srcX) ))
        ) {
            return true;
        } else {
            return false;
        }
    } else {
        if ((srcY >= 6 && tarY - srcY == -1 && srcX == tarX)
            || (srcY <= 5 && ((srcY == tarY && abs(srcX - tarX) == 1) || (tarY - srcY == -1 && tarX == srcX) ))
                ) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}


MOVE_RESULT MoveHelper::MoveChess(ChessCategory cate, int player, int chessIndex, short tarX, short tarY, ChessBoard &chessBoard) {

    if (blockedByAlly(tarX, tarY, player, chessBoard)) {
        return MOVE_FAIL;
    }

    if (cate != KING && leadToKingFaceToFace(player, chessIndex, tarX, tarY, chessBoard)) {
        return MOVE_FAIL;
    }

    bool canMove = false;
    switch (cate) {
        case KING:
            canMove = kingCanMove(player, chessIndex, tarX, tarY, chessBoard);
            break;
        case GUARD:
            canMove = guardCanMove(player, chessIndex, tarX, tarY, chessBoard);
            break;
        case BISHOP:
            canMove = bishopCanMove(player, chessIndex, tarX, tarY, chessBoard);
            break;
        case KNIGHT:
            canMove = knightCanMove(player, chessIndex, tarX, tarY, chessBoard);
            break;
        case ROOK:
            canMove = rookCanMove(player, chessIndex, tarX, tarY, chessBoard);
            break;
        case CANNON:
            canMove = cannonCanMove(player, chessIndex, tarX, tarY, chessBoard);
            break;
        case PAWN:
            canMove = pawnCanMove(player, chessIndex, tarX, tarY, chessBoard);
            break;
    }

    if (!canMove) {
        return MOVE_FAIL;
    } else {
        bool eatRes = tryEat(player, tarX, tarY, chessBoard);
        if (player == 1) {
            chessBoard.getChess1()[chessIndex].setXY(tarX, tarY);
        } else {
            chessBoard.getChess2()[chessIndex].setXY(tarX, tarY);
        }
        return eatRes ? EAT : PLAIN;
    }


}
