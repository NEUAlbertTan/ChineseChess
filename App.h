#ifndef CHINESECHESS_APP_H
#define CHINESECHESS_APP_H

#include "vector"
#include "string"

#include "Player.h"
#include "Game.h"
#include "FileSys.h"


class App {
private:
    std::vector<Player> _players;
    Player _currentPlayer;
    Game _game;
    FileSys _fileSys;

public:
    explicit App(FileSys & fileSys) : _fileSys(fileSys) { }

    // Player methods

    Player login(std::string id, std::string password);

    void logout();

    Player registerPlayer(std::string id, std::string password);

    void addPlayer(Player player);


    // Game methods
    Game startGame();

    bool endGame();


    // File methods
    void setFileManager(FileSys fileSys);

    bool savePlayers();

    bool loadPlayers();
};


#endif //CHINESECHESS_APP_H