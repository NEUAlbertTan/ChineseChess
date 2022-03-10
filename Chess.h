#ifndef CHINESECHESS_CHESS_H
#define CHINESECHESS_CHESS_H

#include "string"

enum ChessCategory {King, Guard, Bishop, Knight, Rook, Cannon, Pawn};

class Chess {
private:
    ChessCategory _chessCategory;

    unsigned _x, _y;

    bool _alive;

    unsigned _playerNumber;

public:
    Chess(ChessCategory category, unsigned x, unsigned y, int playerNumber) {
        _chessCategory = category;
        _x = x;
        _y = y;
        _alive = true;
        _playerNumber = playerNumber;
    }

    void draw();

    void move(unsigned tar_x, unsigned tar_y);

    void attack();

};


#endif //CHINESECHESS_CHESS_H
