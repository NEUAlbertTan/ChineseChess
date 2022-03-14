#ifndef CHINESECHESS_CHESSBOARD_H
#define CHINESECHESS_CHESSBOARD_H

#include "Chess.h"
#include "DrawerHelper.h"
#include "vector"
#include "cstdio"


class ChessBoard {
private:
    std::vector<Chess> _chess1;
    std::vector<Chess> _chess2;

    static std::vector<Chess> genChess (int turn);

public:
    ChessBoard() {
        _chess1 = genChess(1);
        _chess2 = genChess(2);
    }

    void drawChessBoard();

    std::vector<Chess> getChess1() {return _chess1;}
    std::vector<Chess> getChess2() {return _chess2;}

};


#endif //CHINESECHESS_CHESSBOARD_H
