#ifndef CHINESECHESS_DRAWERHELPER_H
#define CHINESECHESS_DRAWERHELPER_H


#include "windows.h"


class DrawerHelper {
public:
    DrawerHelper() = default;
    static void moveCursorTo(short x, short y) {
        COORD pos = {x,y};
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hOut, pos);
    }
};


#endif //CHINESECHESS_DRAWERHELPER_H
