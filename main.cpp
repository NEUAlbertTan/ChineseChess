#include "App.h"
#include "FileSys.h"

#include "string"


int main() {
    static std::string path = "D:\\clionProject\\ChineseChess\\playerFile.txt";

    FileSys fileSys(path);

    App app(fileSys);

    app.mainLoop();

    return 0;
}
