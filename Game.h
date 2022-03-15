#ifndef CHINESECHESS_GAME_H
#define CHINESECHESS_GAME_H

#include "Player.h"
#include "ChessBoard.h"
#include "DrawerHelper.h"
#include "MoveHelper.h"

#include "string"


enum GameStatus {PLAYING, PAUSE, PLAYER_1_CHECK, PLAYER_2_CHECK};


class Game {
private:
    Player _player1;
    Player _player2;
    std::string _playerID1;
    std::string _playerID2;

    int _player = 1;

    ChessBoard _chessBoard;

    GameStatus _gameStatus;

public:
    Game(Player & p1, Player & p2, std::string &id1, std::string &id2) {
        _player1 = p1;
        _player2 = p2;
        _playerID1 = id1;
        _playerID2 = id2;
        _chessBoard = ChessBoard();
        _gameStatus = PLAYING;
    }

    Game() = default;

    GameStatus startGame();

    void drawGame();

    bool updateGame();

    bool hasValidChess(short x, short y);

    int getChessByPos(short x, short y);

    bool moveChess(int tarChessIndex, short tarX, short tarY);

    bool check();

};


#endif //CHINESECHESS_GAME_H
