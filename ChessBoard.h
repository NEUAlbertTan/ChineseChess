#ifndef CHINESECHESS_CHESSBOARD_H
#define CHINESECHESS_CHESSBOARD_H

#include "Chess.h"
#include "DrawerHelper.h"
#include "vector"


class ChessBoard {
private:
    std::vector<Chess> _chess1;
    std::vector<Chess> _chess2;
    DrawerHelper _drawerHelper;

    static std::vector<Chess> genChess (int turn);

public:
    explicit ChessBoard(DrawerHelper & drawerHelper) {
        _drawerHelper = drawerHelper;
        _chess1 = genChess(1);
        _chess2 = genChess(2);
    }

    ChessBoard() = default;

    void drawChessBoard();

    void update();

};


#endif //CHINESECHESS_CHESSBOARD_H
