#include "App.h"
#include "FileSys.h"

#include "string"


int main() {
    static std::string path = "./playerFile.txt";

    FileSys fileSys(path);

    App app(fileSys);

    app.login();


    return 0;
}
