#include "App.h"
#include "FileSys.h"

#include "string"


int main() {
    static std::string path = "./file.chess";

    FileSys fileSys(path);

    App app(fileSys);


    return 0;
}
