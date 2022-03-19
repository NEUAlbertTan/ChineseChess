#include "Game.h"

const std::string surrenderCode = "gg";


void Game::drawGame() {
    _chessBoard.drawChessBoard();

    DrawerHelper::moveCursorTo(11, 1);
    printf("玩家1");
    if (_player == 1) {
        printf("的回合");
    }
    DrawerHelper::moveCursorTo(11, 2);
    printf("昵称: %s", _player1.getName().c_str());
    DrawerHelper::moveCursorTo(11, 3);
    printf("天梯分: %d", _player1.getScore());
    DrawerHelper::moveCursorTo(11, 4);
    printf("可用技能: ");

    DrawerHelper::moveCursorTo(11, 6);
    printf("玩家2");
    if (_player == 2) {
        printf("的回合");
    }
    DrawerHelper::moveCursorTo(11, 7);
    printf("昵称: %s", _player2.getName().c_str());
    DrawerHelper::moveCursorTo(11, 8);
    printf("天梯分: %d", _player2.getScore());
    DrawerHelper::moveCursorTo(11, 9);
    printf("可用技能: ");

    DrawerHelper::moveCursorTo(1, 11);
    printf("输入棋子坐标: ");
}


GameStatus Game::startGame() {
    system("cls");

    while (!check()) {
        if (updateGame()) {
            // valid operation, change player
            if (_player == 1) {
                _player = 2;
            } else {
                _player = 1;
            }
        }
    }

    return _gameStatus;
}


bool Game::check() {
    auto chess_1 = _chessBoard.getChess1();
    auto chess_2 = _chessBoard.getChess2();

    for (auto &chess: chess_1) {
        if ((chess.chessCategory == KING) & !chess.alive) {
            _gameStatus = PLAYER_2_CHECK;
            return true;
        }
    }

    for (auto &chess: chess_2) {
        if ((chess.chessCategory == KING) & !chess.alive) {
            _gameStatus = PLAYER_1_CHECK;
            return true;
        }
    }

    return false;
}


std::string inputPos() {
    std::string pos;
    std::cin >> pos;
    return pos;
}


bool isValidPos(std::string &pos) {
    if (pos.size() != 2) {
        return false;
    }

    char px = pos[0], py = pos[1];

    return px >= '1' && px <= '9' && py <= 'j' && py >= 'a' || pos == surrenderCode;
}


int Game::getChessByPos(short x, short y) {
    if (_player == 1) {
        for (int i = 0; i < _chessBoard.getChess1().size(); ++i) {
            if (_chessBoard.getChess1()[i].isAtPos(x, y)) {
                return i;
            }
        }
    }

    if (_player == 2) {
        for (int i = 0; i < _chessBoard.getChess2().size(); ++i) {
            if (_chessBoard.getChess2()[i].isAtPos(x, y)) {
                return i;
            }
        }
    }

    return -1;
}


bool Game::hasValidChess(short x, short y) {

    if (_player == 1) {
        for (auto &chess: _chessBoard.getChess1()) {
            if (chess.alive && chess.isAtPos(x, y)) {
                return true;
            }
        }
    }

    if (_player == 2) {
        for (auto &chess: _chessBoard.getChess2()) {
            if (chess.alive && chess.isAtPos(x, y)) {
                return true;
            }
        }
    }

    return false;
}


void Game::surrender() {
    if (_player == 1) {
        for (auto &c: _chessBoard.getChess1()) {
            if (c.chessCategory == KING) {
                c.alive = false;
                break;
            }
        }
    } else {
        for (auto &c: _chessBoard.getChess2()) {
            if (c.chessCategory == KING) {
                c.alive = false;
                break;
            }
        }
    }
}


bool Game::updateGame() {
    system("cls");
    drawGame();
    auto srcPos = inputPos();

    // surrender
    if (srcPos == surrenderCode) {
        surrender();
        return false;
    }

    if (!isValidPos(srcPos)) {
        return false;
    }

    short srcX = srcPos[0] - '1' + 1, srcY = srcPos[1] - 'a' + 1;

    if (!hasValidChess(srcX, srcY)) {
        return false;
    }


    int tarChessIndex = getChessByPos(srcX, srcY);

    printf("移动到:");

    auto tarPos = inputPos();
    // surrender
    if (srcPos == surrenderCode) {
        surrender();
        return false;
    }

    if (!isValidPos(tarPos)) {
        return false;
    }
    short tarX = tarPos[0] - '1' + 1, tarY = tarPos[1] - 'a' + 1;

    if (tarX == srcX && tarY == srcY) {
        return false;
    }

    if (!moveChess(tarChessIndex, tarX, tarY)) {
        return false;
    }

    return true;
}


bool Game::moveChess(int tarChessIndex, short tarX, short tarY) {
    ChessCategory cate;
    if (_player == 1) {
        cate = _chessBoard.getChess1()[tarChessIndex].chessCategory;
    } else {
        cate = _chessBoard.getChess2()[tarChessIndex].chessCategory;
    }

    MOVE_RESULT moveRes = MoveHelper::MoveChess(cate, _player, tarChessIndex, tarX, tarY, _chessBoard);

    return moveRes != MOVE_FAIL;

}
