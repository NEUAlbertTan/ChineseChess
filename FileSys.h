#ifndef CHINESECHESS_FILESYS_H
#define CHINESECHESS_FILESYS_H


#include "Player.h"
#include "string"
#include "vector"
#include "fstream"
#include "iostream"


class FileSys {
private:
    std::string _filePath;

public:
    explicit FileSys(std::string & filePath) {
        _filePath = filePath;
    }

    bool savePlayers(std::vector<Player> & players);

    std::vector<Player> loadPlayers();
};


#endif //CHINESECHESS_FILESYS_H
