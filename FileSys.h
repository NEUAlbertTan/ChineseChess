#ifndef CHINESECHESS_FILESYS_H
#define CHINESECHESS_FILESYS_H


#include "Player.h"
#include "string"
#include "iostream"
#include "vector"


class FileSys {
private:
    std::string _filePath;

public:
    explicit FileSys(std::string & filePath) {
        _filePath = filePath;
    }

    bool saveFile();

    std::vector<Player> loadPlayers();
};


#endif //CHINESECHESS_FILESYS_H
