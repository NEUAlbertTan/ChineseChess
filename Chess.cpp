#include "Chess.h"


static std::unordered_map<ChessCategory, char> cateCharMap{
        {KING, 'J'},
        {GUARD, 'S'},
        {BISHOP, 'X'},
        {KNIGHT, 'M'},
        {ROOK, 'C'},
        {CANNON, 'P'},
        {PAWN, 'B'},
        {BLOCK, '#'}
};


void Chess::draw() const {
    if (!alive) {
        return;
    }
    char chessChar = cateCharMap[chessCategory];

    DrawerHelper::moveCursorTo(x, y);
    if (playerNumber == 1) {
        DrawerHelper::SetConsoleColor(enmCFC_Red);
    } else {
        DrawerHelper::SetConsoleColor(enmCFC_Black);
    }
    printf("%c", chessChar);
    DrawerHelper::SetConsoleColor();
}
