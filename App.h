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
    // TODO: currentPlayer should be reference
    Player _currentPlayer;
    Game _game;
    FileSys _fileSys;

public:
    explicit App(FileSys & fileSys) : _fileSys(fileSys) {}

    void optLoginOrRegister();

    void loginPage();

    void registerPage();

    void mainLoop();

    void gameLobby();

    void showRankList(int page);

    void viewRankList();

    static void viewIntro();

    void personalSettings();

    void changeNamePage();

    void changePasswordPage();

    // Player methods

    void addPlayer(Player & player) {
        _players.emplace_back(player);
        savePlayers();
    }

    // Game methods
    Player invitePlayer();
    void startGame();

    // File methods
    void savePlayers();

    void loadPlayers() {
        _players = _fileSys.loadPlayers();
    }
};


#endif //CHINESECHESS_APP_H
