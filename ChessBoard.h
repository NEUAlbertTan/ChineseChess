#ifndef CHINESECHESS_CHESSBOARD_H
#define CHINESECHESS_CHESSBOARD_H

#include "Chess.h"

#include "vector"


class ChessBoard {
private:
    std::vector<Chess> chess1;
    std::vector<Chess> chess2;


public:
    ChessBoard(){}
    void drawChessBoard();

    void update();

};


#endif //CHINESECHESS_CHESSBOARD_H
