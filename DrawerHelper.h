#ifndef CHINESECHESS_DRAWERHELPER_H
#define CHINESECHESS_DRAWERHELPER_H


#include "windows.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <Windows.h>


enum ConsoleForegroundColor
{
    enmCFC_Red          = FOREGROUND_INTENSITY | FOREGROUND_RED,
    enmCFC_Green        = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    enmCFC_Blue         = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    enmCFC_Yellow       = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
    enmCFC_Purple       = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    enmCFC_Cyan         = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
    enmCFC_Gray         = FOREGROUND_INTENSITY,
    enmCFC_White        = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    enmCFC_HighWhite    = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    enmCFC_Black        = 0,
};

enum ConsoleBackGroundColor
{
    enmCBC_Red          = BACKGROUND_INTENSITY | BACKGROUND_RED,
    enmCBC_Green        = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
    enmCBC_Blue         = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
    enmCBC_Yellow       = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
    enmCBC_Purple       = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
    enmCBC_Cyan         = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
    enmCBC_White        = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
    enmCBC_HighWhite    = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
    enmCBC_Black        = 0,
};


class DrawerHelper {
public:
    DrawerHelper() = default;
    static void moveCursorTo(short x, short y) {
        COORD pos = {x,y};
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hOut, pos);
    }

    static void SetConsoleColor(ConsoleForegroundColor foreColor = enmCFC_Black, ConsoleBackGroundColor backColor = enmCBC_HighWhite) {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, foreColor | backColor);
    }
};


#endif //CHINESECHESS_DRAWERHELPER_H
