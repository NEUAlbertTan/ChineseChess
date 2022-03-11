#ifndef CHINESECHESS_APP_H
#define CHINESECHESS_APP_H

#include "vector"
#include "string"
#include "iostream"

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

    void optLoginOrRegister();

    void loginPage();

    void registerPage();

    void mainLoop();

    void gameLobby();


    // Player methods

    void addPlayer(Player & player) {
        _players.emplace_back(player);
        savePlayers();
    }


    // Game methods
    Game startGame();

    bool endGame();


    // File methods

    void savePlayers();

    void loadPlayers() {
        _players = _fileSys.loadPlayers();
    }
};


#endif //CHINESECHESS_APP_H
