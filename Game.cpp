#include "Game.h"


const std::string surrenderCode = "gg";
const std::string skipCode = "00";


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
    printf("可用技能: %s", skills1.c_str());

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
    printf("可用技能: %s", skills2.c_str());

    DrawerHelper::moveCursorTo(0, 11);
    printf("投降：gg 跳过回合：00 使用技能: -[jmsht]");

    DrawerHelper::moveCursorTo(0, 12);
}


GameStatus Game::startGame() {
    system("cls");

    // operate count
    int round = 1;

    while (!check()) {
        GameUpdateResult updateResult = updateGame();
        switch (updateResult) {
            case UPDATE_FAIL:
                break;

            case UPDATE_SUCCESS:
                if (--round > 0) {
                    break;
                }

                // thaw the frozen chess
                for (auto &c: _chessBoard.getChess1()) {
                    if (c.canNotMove > 0) {
                        --c.canNotMove;
                    }
                }
                for (auto &c: _chessBoard.getChess2()) {
                    if (c.canNotMove > 0) {
                        --c.canNotMove;
                    }
                }

                // valid operation, change player
                if (_player == 1) {
                    _player = 2;
                } else {
                    _player = 1;
                }
                // next player runs 1 round
                round = 1;
                break;

            case UPDATE_ONE_MORE:
                // this player runs two continuous round
                round = 2;
                break;
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
    printf("目标坐标：");
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


SkillResult Game::useSkill(std::string &skill) {
    char skillChar = skill[1];
    if (skillChar == 'j') {
        return SkillHelper::useSkill(skillChar, _player, 0, 0, _chessBoard);
    }

    auto pos = inputPos();
    if (!isValidPos(pos)) {
        return SKILL_FAIL;
    }

    short x = pos[0] - '1' + 1, y = pos[1] - 'a' + 1;

    return SkillHelper::useSkill(skillChar, _player, x, y, _chessBoard);
}


GameUpdateResult Game::updateGame() {
    system("cls");
    drawGame();
    auto srcPos = inputPos();

    if (srcPos[0] == '-') {
        if (srcPos.size() != 2) {
            return UPDATE_FAIL;
        }
        auto skillRes = useSkill(srcPos);
        switch (skillRes) {
            case SKILL_FAIL:
                return UPDATE_FAIL;
            case SKILL_SUCCESS:
                if (_player == 1) {
                    skills1.erase(skills1.find(srcPos[1]), 1);
                } else {
                    skills2.erase(skills2.find(srcPos[1]), 1);
                }
                return UPDATE_SUCCESS;
            case ONE_MORE_TURN:
                if (_player == 1) {
                    skills1.erase(skills1.find(srcPos[1]), 1);
                } else {
                    skills2.erase(skills1.find(srcPos[1]), 1);
                }
                return UPDATE_ONE_MORE;
        }
    }

    // surrender
    if (srcPos == surrenderCode) {
        surrender();
        return UPDATE_FAIL;
    } else if (srcPos == skipCode) {
        return UPDATE_SUCCESS;
    }

    if (!isValidPos(srcPos)) {
        return UPDATE_FAIL;
    }

    short srcX = srcPos[0] - '1' + 1, srcY = srcPos[1] - 'a' + 1;

    if (!hasValidChess(srcX, srcY)) {
        return UPDATE_FAIL;
    }

    int tarChessIndex = getChessByPos(srcX, srcY);

    if (tarChessIndex == -1) {
        return UPDATE_FAIL;
    }

    // second input
    auto tarPos = inputPos();

    if (!isValidPos(tarPos)) {
        return UPDATE_FAIL;
    }
    short tarX = tarPos[0] - '1' + 1, tarY = tarPos[1] - 'a' + 1;

    if (tarX == srcX && tarY == srcY) {
        return UPDATE_FAIL;
    }

    if (!moveChess(tarChessIndex, tarX, tarY)) {
        return UPDATE_FAIL;
    }

    return UPDATE_SUCCESS;
}


bool Game::moveChess(int tarChessIndex, short tarX, short tarY) {
    ChessCategory cate;
    if (_player == 1) {
        if (_chessBoard.getChess1()[tarChessIndex].canNotMove > 0) {
            return false;
        }
        cate = _chessBoard.getChess1()[tarChessIndex].chessCategory;
    } else {
        if (_chessBoard.getChess2()[tarChessIndex].canNotMove > 0) {
            return false;
        }
        cate = _chessBoard.getChess2()[tarChessIndex].chessCategory;
    }

    MoveResult moveRes = MoveHelper::MoveChess(cate, _player, tarChessIndex, tarX, tarY, _chessBoard);

    return moveRes != MOVE_FAIL;

}
