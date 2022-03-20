#include "App.h"

#include "string"


int main() {

    DrawerHelper::SetConsoleColor(enmCFC_Black, enmCBC_HighWhite);

    static std::string path = "players.txt";

    FileSys fileSys(path);

    App app(fileSys);

    app.mainLoop();


    return 0;
}
