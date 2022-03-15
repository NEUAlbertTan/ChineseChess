#include "App.h"
#include <cstdlib>
#include "conio.h"
#include "windows.h"
#include "algorithm"


static const unsigned RANK_PAGE_SIZE = 5;

const static int WIN_SCORE = 50;
const static int WIN_MONEY = 50;
const static int LOSE_DEC_SCORE = 50;
const static int LOSE_MONEY = 30;


void App::savePlayers() {
    bool status = _fileSys.savePlayers(_players);
    if (!status) {
        exit(-1);
    }
}


void App::optLoginOrRegister() {
    system("cls");

    std::cout << "1: ��¼, 2: ע��, 0: �˳�" << std::endl;
    std::cout << "��ѡ��" << std::endl;

    int ch;

    while (true) {
        fflush(stdin);
        ch = getchar();
        switch (ch) {
            case '1': {
                loginPage();
                break;
            }
            case '2': {
                registerPage();
                break;
            }
            case '0': {
                exit(0);
            }

            default: {
                system("cls");
                std::cout << "1: ��¼, 2: ע��, 0: �˳�" << std::endl;
                std::cout << "��ѡ��" << std::endl;
            }
        }
    }
}


void App::loginPage() {
    system("cls");
    std::string id, password;

    std::cout << "ID: ";
    std::cin >> id;

    // TODO: replace with *
    std::cout << "password: ";
    std::cin >> password;

    bool foundTargetPlayer = false;

    for (auto & p : _players) {
        if (p.getId() == id && p.getPassword() == password) {
            _currentPlayerID = id;
            _currentPlayer = p;
            foundTargetPlayer = true;
            break;
        }
    }

    if (foundTargetPlayer) {
        // TODO: replace with Messagebox
        std::cout << "��¼�ɹ���" << std::endl;
        Sleep(1000);
        gameLobby();
    } else {
        std::cout << "�˺Ż��������";
        Sleep(1000);
        return;
    }

}


void App::registerPage() {
    system("cls");
    std::string id, password, name;

    std::cout << "ID: ";
    std::cin >> id;

    if (id.size() < 6 || id.size() > 16) {
        std::cout << "ID������Ҫ��6-16λ";
        Sleep(1000);
        return;
    }

    bool sameID = false;
    for (auto & p : _players) {
        if (p.getId() == id) {
            sameID = true;
            break;
        }
    }

    if (sameID) {
        std::cout << "ID�ظ�����";
        Sleep(1000);
        return;
    }

    std::cout << "password: ";
    std::cin >> password;

    if (password.size() < 6 || password.size() > 16) {
        std::cout << "���볤����Ҫ��6-16λ";
        Sleep(1000);
        return;
    }

    std::cout << "�ǳ�: ";
    std::cin >> name;

    if (name.size() < 6 || name.size() > 16) {
        std::cout << "�ǳƳ�����Ҫ��6-16λ";
        Sleep(1000);
        return;
    }

    Player newPlayer(id, password, name);

    addPlayer(newPlayer);
}


void App::mainLoop() {
    loadPlayers();
    while (true) {
        optLoginOrRegister();
    }
}


void App::gameLobby() {
    int ch;

    while (true) {
        system("cls");
        fflush(stdin);
        std::cout << "1: ��ʼ��Ϸ\n2: �鿴���а�\n3: ��Ϸ˵��\n4: ��������\n0���˳���Ϸ" << std::endl;
        ch = getchar();
        switch (ch) {
            case '1': {
                startGame();
                break;
            }
            case '2': {
                viewRankList();
                break;
            }
            case '3': {
                viewIntro();
                break;
            }
            case '4': {
                personalSettings();
                break;
            }
            case '0': {
                exit(0);
            }
            default: {
                break;
            }
        }
    }
}


std::string App::invitePlayer() {
    system("cls");
    fflush(stdin);
    system("cls");
    std::string id, password;

    std::cout << "ID: ";
    std::cin >> id;

    // TODO: replace with *
    std::cout << "password: ";
    std::cin >> password;

    Player targetPlayer;
    std::string targetPlayerID;
    bool foundTargetPlayer = false;

    for (auto & p : _players) {
        if (p.getId() == id && p.getPassword() == password) {
            targetPlayer = p;
            targetPlayerID = id;
            foundTargetPlayer = true;
            break;
        }
    }

    if (foundTargetPlayer) {
        // TODO: replace with Messagebox
        std::cout << "��ӭ��" << targetPlayer.getName() << std::endl;
        Sleep(1000);
        return targetPlayerID;
    } else {
        std::cout << "�˺Ż��������";
        Sleep(1000);
        return "";
    }
}


void App::startGame() {
    std::string targetPlayerID = invitePlayer();
    if (targetPlayerID.empty()) {
        return;
    }
    Player tarPlayer;
    for (auto &p: _players) {
        if (p.getId() == targetPlayerID) {
            tarPlayer = p;
            break;
        }
    }
    _game = Game(_currentPlayer, tarPlayer,_currentPlayerID, targetPlayerID);

    GameStatus gameResult = _game.startGame();

    gameSettlement(gameResult, _currentPlayerID, targetPlayerID);

}


void App::gameSettlement(GameStatus gameResult, std::string &playerID1, std::string &playerID2) {
    switch (gameResult) {
        case PLAYER_1_CHECK:
            for (auto &p: _players) {
                if (p.getId() == playerID1) {
                    p.addScore(WIN_SCORE);
                    p.addMoney(WIN_MONEY);
                } else if (p.getId() == playerID2) {
                    p.decScore(LOSE_DEC_SCORE);
                    p.addMoney(LOSE_MONEY);
                }
            }
            break;
        case PLAYER_2_CHECK:
            for (auto &p: _players) {
                if (p.getId() == playerID2) {
                    p.addScore(WIN_SCORE);
                    p.addMoney(WIN_MONEY);
                } else if (p.getId() == playerID1) {
                    p.decScore(LOSE_DEC_SCORE);
                    p.addMoney(LOSE_MONEY);
                }
            }
            break;
    }
    savePlayers();
}


void App::showRankList(int page) {

    auto count = _players.size();
    if (page)
    system("cls");
    std::cout << "1: ��һҳ; 2: ��һҳ: 0: ������ҳ��" << std::endl;
    std::cout << "��ǰҳ: " << page << std::endl;

    printf("%16s%16s%16s\n","ID", "�ǳ�", "����");

    for (int i = (page - 1) * RANK_PAGE_SIZE; i < (count < page * RANK_PAGE_SIZE ? count : page * RANK_PAGE_SIZE); ++i) {
        printf("%16s%16s%16d\n",_players[i].getId().c_str(), _players[i].getName().c_str(), _players[i].getScore());
    }

}


void App::viewRankList() {
    system("cls");

    std::sort(_players.begin(), _players.end(), [&](Player a, Player b) {
        return a.getScore() > b.getScore();
    });

    auto playerCount = _players.size();

    int ch;

    int curPage = 1;

    while (true) {
        ch = getchar();
        switch (ch) {
            case '1': {
                if (curPage <= 1) {
                    break;
                }
                showRankList(--curPage);
                break;
            }
            case '2': {
                if (curPage >= 1 + playerCount / RANK_PAGE_SIZE) {
                    break;
                }
                showRankList(++curPage);
                break;
            }
            case '0': {
                return;
            }
            default: {
                showRankList(curPage);
            }
        }
    }
}


void App::viewIntro() {
    system("cls");
    fflush(stdin);
    std::cout << "����Ϸ����˴�ͳ�����뿨����Ϸ���ص㣬��ҿ����������ս��ʹ�ü��ܡ�" << std::endl;
    std::cout << "�˴�ʡ��һǧ��" << std::endl;
    std::cout << "���س������ز˵�" << std::endl;
    getchar();
    fflush(stdin);
}


void App::personalSettings() {

    int ch;

    while (true) {
        system("cls");
        printf("ID: %16s, �ǳ�: %16s, ����:%16d, ��Ǯ:%16d\n", _currentPlayer.getId().c_str(), _currentPlayer.getName().c_str(), _currentPlayer.getScore(), _currentPlayer.getMoney());
        printf("1: �޸��ǳ�; 2: �޸�����; 0: ����");
        printf("����ѡ��: ");
        ch = getchar();

        switch (ch) {
            case '1': {
                changeNamePage();
                break;
            }
            case '2': {
                changePasswordPage();
                break;
            }
            case '0': {
                savePlayers();
                return;
            }
            default: {
                break;
            }
        }
    }
}


void App::changeNamePage() {
    system("cls");
    std::string newName;
    printf("���������ǳ�: ");
    std::cin >> newName;

    if (newName.size() < 6 || newName.size() > 16) {
        std::cout << "�ǳƳ�����Ҫ��6-16֮��!\n";
        Sleep(1000);
        return;
    }

    for (auto &p: _players) {
        if (p.getId() == _currentPlayerID) {
            _currentPlayer.setName(newName);
            p.setName(newName);
            break;
        }
    }
}


void App::changePasswordPage() {
    system("cls");
    std::string newPassword;
    printf("������������: ");
    std::cin >> newPassword;

    if (newPassword.size() < 6 || newPassword.size() > 16) {
        std::cout << "���볤����Ҫ��6-16֮��!\n";
        Sleep(1000);
        return;
    }

    for (auto &p: _players) {
        if (p.getId() == _currentPlayerID) {
            p.setPassword(newPassword);
            break;
        }
    }
}
