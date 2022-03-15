#include "App.h"
#include "DrawerHelper.h"

#include "string"


int main() {

    DrawerHelper::SetConsoleColor(enmCFC_Black, enmCBC_HighWhite);

    static std::string path = R"(D:\clionProject\ChineseChess\playerFile.txt)";

    FileSys fileSys(path);

    App app(fileSys);

    app.mainLoop();


    return 0;
}
