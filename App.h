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
    std::string _currentPlayerID;
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

    Player getPlayerById(std::string &id) {
        for (auto &p : _players) {
            if (p.getId() == id) {
                return p;
            }
        }
        return {};
    }

    // Player methods

    void addPlayer(Player & player) {
        _players.emplace_back(player);
        savePlayers();
    }

    // Game methods
    std::string invitePlayer();
    void startGame();
    void gameSettlement(GameStatus gameResult, std::string &playerID1, std::string &plaerID2);

    // File methods
    void savePlayers();

    void loadPlayers() {
        _players = _fileSys.loadPlayers();
    }
};


#endif //CHINESECHESS_APP_H
