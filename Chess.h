#ifndef CHINESECHESS_CHESS_H
#define CHINESECHESS_CHESS_H

#include "string"
#include "iostream"
#include "vector"
#include "unordered_map"

#include "DrawerHelper.h"


enum ChessCategory {KING, GUARD, BISHOP, KNIGHT, ROOK, CANNON, PAWN};


class Chess {
public:
    short x;
    short y;
    ChessCategory chessCategory;
    bool alive;
    unsigned playerNumber;

    Chess(ChessCategory category, short x, short y, int playerNumber) {
        chessCategory = category;
        this->x = x;
        this->y = y;
        alive = true;
        this->playerNumber = playerNumber;
    }

    bool isAtPos(short xx, short yy) const {
        return xx == this->x && yy == this->y;
    }

    void draw() const;

    void attack();

    void drawChess() const;

    void setXY(short xx, short yy) {
        this->x = xx;
        this->y = yy;
    }

};


#endif //CHINESECHESS_CHESS_H
