#include "SkillHelper.h"


static std::unordered_map<char, SkillType> charSkillTypeMap {
    {'j', GOLD}, {'m', WOOD}, {'s', WATER}, {'h', FIRE}, {'t', DIRT}
};


static const std::string skillChars = "jmsht";


bool existValidChess(int player, bool alive, short x, short y, ChessBoard &chessBoard) {
    if (player == 1) {
        for (auto &c : chessBoard.getChess1()) {
            if (c.alive == alive && c.isAtPos(x, y)) {
                return true;
            }
        }
    } else {
        for (auto &c : chessBoard.getChess2()) {
            if (c.alive == alive && c.isAtPos(x, y)) {
                return true;
            }
        }
    }

    return false;
}


SkillResult SkillHelper::useSkill(SkillType skillType, int player, short x, short y, ChessBoard &chessBoard) {
    int anotherPlayer = player == 1 ? 2 : 1;

    switch (skillType) {

        case GOLD:
            return ONE_MORE_TURN;

        case WOOD:
            if (!existValidChess(player, false, x, y, chessBoard) || existValidChess(player, true, x, y, chessBoard) || existValidChess(anotherPlayer, true, x, y, chessBoard)) {
                return SKILL_FAIL;
            }
            if (player == 1) {
                for (auto &c: chessBoard.getChess1()) {
                    if (c.isAtPos(x, y)) {
                        c.alive = true;
                    }
                }
            } else {
                for (auto &c: chessBoard.getChess2()) {
                    if (c.isAtPos(x, y)) {
                        c.alive = true;
                    }
                }
            }
            return SKILL_SUCCESS;

        case WATER:
            if (!existValidChess(anotherPlayer, true, x, y, chessBoard)) {
                return SKILL_FAIL;
            }
            if (player == 1) {
                for (auto &c: chessBoard.getChess2()) {
                    if (c.isAtPos(x, y)) {
                        c.canNotMove += 2;
                    }
                }
            } else {
                for (auto &c: chessBoard.getChess1()) {
                    if (c.isAtPos(x, y)) {
                        c.canNotMove += 2;
                    }
                }
            }
            return SKILL_SUCCESS;

        case FIRE:
            if (!existValidChess(anotherPlayer, true, x, y, chessBoard)) {
                return SKILL_FAIL;
            }
            if (player == 1) {
                for (auto &c: chessBoard.getChess2()) {
                    if (c.isAtPos(x, y)) {
                        if (c.chessCategory == KING) {
                            return SKILL_FAIL;
                        } else {
                            c.alive = false;
                        }
                    }
                }
            } else {
                for (auto &c: chessBoard.getChess1()) {
                    if (c.isAtPos(x, y)) {
                        if (c.chessCategory == KING) {
                            return SKILL_FAIL;
                        } else {
                            c.alive = false;
                        }
                    }
                }
            }
            return SKILL_SUCCESS;

        case DIRT:
            if (existValidChess(player, true, x, y, chessBoard) || existValidChess(anotherPlayer, true, x, y, chessBoard)) {
                return SKILL_FAIL;
            } else {
                if (player == 1) {
                    chessBoard.getChess1().emplace_back(Chess(BLOCK, x, y, 1, 10000));
                } else {
                    chessBoard.getChess2().emplace_back(Chess(BLOCK, x, y, 1, 10000));
                }
            }
            return SKILL_SUCCESS;
    }

    return SKILL_FAIL;
}


SkillResult SkillHelper::useSkill(char skillChar, int player, short x, short y, ChessBoard &chessBoard) {
    if (skillChars.find(skillChar) == std::string::npos) {
        return SKILL_FAIL;
    }

    return useSkill(charSkillTypeMap[skillChar], player, x, y, chessBoard);
}
