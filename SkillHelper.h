#ifndef CHINESECHESS_SKILLHELPER_H
#define CHINESECHESS_SKILLHELPER_H

#include "ChessBoard.h"


enum SkillType {GOLD, WOOD, WATER, FIRE, DIRT};

enum SkillResult {SKILL_FAIL = 0, SKILL_SUCCESS, ONE_MORE_TURN};


class SkillHelper {
public:
    static SkillResult useSkill(char skillChar, int player, short x, short y, ChessBoard &chessBoard);

    static SkillResult useSkill(SkillType skillType, int player, short x, short y, ChessBoard &chessBoard);
};


#endif //CHINESECHESS_SKILLHELPER_H
