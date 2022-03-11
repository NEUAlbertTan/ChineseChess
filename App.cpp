#include "App.h"
#include <cstdlib>
#include "conio.h"
#include "windows.h"


void App::savePlayers() {
    bool status = _fileSys.savePlayers(_players);
    if (!status) {
        exit(-1);
    }
}


void App::optLoginOrRegister() {
    system("cls");

    std::cout << "1: 登录, 2: 注册, 0: 退出" << std::endl;
    std::cout << "请选择：" << std::endl;

    int ch;

    while (true) {
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
                std::cout << "1: 登录, 2: 注册, 0: 退出" << std::endl;
                std::cout << "请选择：" << std::endl;
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
            _currentPlayer = p;
            foundTargetPlayer = true;
            break;
        }
    }

    if (foundTargetPlayer) {
        // TODO: replace with Messagebox
        std::cout << "登录成功！" << std::endl;
        std::cout << "欢迎：" << _currentPlayer.getName() << std::endl;
        Sleep(1000);
        gameLobby();
    } else {
        std::cout << "账号或密码错误";
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
        std::cout << "ID长度需要在6-16位";
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
        std::cout << "ID重复了噢";
        Sleep(1000);
        return;
    }

    std::cout << "password: ";
    std::cin >> password;

    if (password.size() < 6 || password.size() > 16) {
        std::cout << "密码长度需要在6-16位";
        Sleep(1000);
        return;
    }

    std::cout << "昵称: ";
    std::cin >> name;

    if (name.size() < 6 || name.size() > 16) {
        std::cout << "昵称长度需要在6-16位";
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

}
