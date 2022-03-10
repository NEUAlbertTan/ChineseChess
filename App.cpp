#include "App.h"

void App::savePlayers() {
    bool status = _fileSys.savePlayers(_players);
    if (!status) {
        exit(-1);
    }
}

