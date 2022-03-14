#include "Chess.h"


static std::unordered_map<ChessCategory, char> cateCharMap{
        {KING, 'J'},
        {GUARD, 'S'},
        {BISHOP, 'X'},
        {KNIGHT, 'M'},
        {ROOK, 'C'},
        {CANNON, 'P'},
        {PAWN, 'B'},
};


void Chess::draw() const {
    if (!alive) {
        return;
    }

    switch (chessCategory) {
        case KING:
            DrawerHelper::moveCursorTo(x, y);
            if (playerNumber == 1) {
                DrawerHelper::SetConsoleColor(enmCFC_Red);
            } else {
                DrawerHelper::SetConsoleColor(enmCFC_Black);
            }
            printf("J");
            DrawerHelper::SetConsoleColor();
            break;
        case GUARD:
            DrawerHelper::moveCursorTo(x, y);
            printf("%c",(playerNumber == 1 ? 'S' : 's'));
            break;
        case BISHOP:
            DrawerHelper::moveCursorTo(x, y);
            printf("%c",(playerNumber == 1 ? 'X' : 'x'));
            break;
        case KNIGHT:
            DrawerHelper::moveCursorTo(x, y);
            printf("%c",(playerNumber == 1 ? 'M' : 'm'));
            break;
        case ROOK:
            DrawerHelper::moveCursorTo(x, y);
            printf("%c",(playerNumber == 1 ? 'C' : 'c'));
            break;
        case CANNON:
            DrawerHelper::moveCursorTo(x, y);
            printf("%c",(playerNumber == 1 ? 'P' : 'p'));
            break;
        case PAWN:
            DrawerHelper::moveCursorTo(x, y);
            printf("%c",(playerNumber == 1 ? 'B' : 'b'));
            break;
    }
}



void Chess::drawChess() const {
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
