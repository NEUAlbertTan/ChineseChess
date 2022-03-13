#ifndef CHINESECHESS_GAME_H
#define CHINESECHESS_GAME_H

#include "Player.h"
#include "ChessBoard.h"
#include "DrawerHelper.h"


enum GameStatus {PLAYING, PAUSE, END};


class Game {
private:
    Player _player1;
    Player _player2;

    int turn = 1;

    ChessBoard _chessBoard;

    GameStatus _gameStatus;

public:
    Game(Player & p1, Player & p2) {
        auto dh = DrawerHelper();
        _player1 = p1;
        _player2 = p2;
        _chessBoard = ChessBoard(dh);
        _gameStatus = PLAYING;
    }

    Game() = default;

    void startGame();

};


#endif //CHINESECHESS_GAME_H
