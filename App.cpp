#include "App.h"
#include <cstdlib>
#include "conio.h"
#include "windows.h"
#include "algorithm"

static const unsigned RANK_PAGE_SIZE = 5;

void App::savePlayers() {
    bool status = _fileSys.savePlayers(_players);
    if (!status) {
        exit(-1);
    }
}


void App::optLoginOrRegister() {
    // system("cls");

    std::cout << "1: 登录, 2: 注册, 0: 退出" << std::endl;
    std::cout << "请选择：" << std::endl;

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
                // system("cls");
                std::cout << "1: 登录, 2: 注册, 0: 退出" << std::endl;
                std::cout << "请选择：" << std::endl;
            }
        }
    }
}


void App::loginPage() {
    // system("cls");
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
    // system("cls");
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
    // system("cls");
    int ch;

    while (true) {
        fflush(stdin);
        std::cout << "1: 开始游戏\n2: 查看排行榜\n3: 游戏说明\n4: 个人设置\n0：退出游戏" << std::endl;
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
                // system("cls");
                std::cout << "1: 开始游戏\n2: 查看排行榜\n3: 游戏说明\n4: 个人设置\n0：退出游戏";
            }
        }
    }
}

void App::startGame() {}

void App::showRankList(int page) {

    auto count = _players.size();
    if (page)
    // system("cls");
    std::cout << "1: 上一页; 2: 下一页: 0: 返回主页面" << std::endl;
    std::cout << "当前页: " << page << std::endl;

    printf("%16s%16s%16s\n","ID", "昵称", "分数");

    for (int i = (page - 1) * RANK_PAGE_SIZE; i < (count < page * RANK_PAGE_SIZE ? count : page * RANK_PAGE_SIZE); ++i) {
        printf("%16s%16s%16d\n",_players[i].getId().c_str(), _players[i].getName().c_str(), _players[i].getScore());
    }

}

void App::viewRankList() {
    // system("cls");

    std::sort(_players.begin(), _players.end(), [&](Player a, Player b) {
        return a.getScore() > b.getScore();
    });

    auto playerCount = _players.size();

    int ch;

    int curPage = 1;

    while (true) {
        fflush(stdin);
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
    // system("cls");
    fflush(stdin);
    std::cout << "该游戏结合了传统象棋与卡牌游戏的特点，玩家可以在象棋对战中使用技能。" << std::endl;
    std::cout << "此处省略一千字" << std::endl;
    std::cout << "按回车键返回菜单" << std::endl;
    getchar();
}

void App::personalSettings() {
    // system("cls");
    printf("ID: %16s, 昵称: %16s\n分数:%16d, 金钱:%16d\n", _currentPlayer.getId().c_str(), _currentPlayer.getName().c_str(), _currentPlayer.getScore(), _currentPlayer.getMoney());
    printf("1: 修改昵称; 2: 修改密码; 0: 返回");
    printf("您的选择: ");

    int ch;

    while (true) {
        fflush(stdin);
        printf("ID: %16s, 昵称: %16s\n分数:%16d, 金钱:%16d\n", _currentPlayer.getId().c_str(), _currentPlayer.getName().c_str(), _currentPlayer.getScore(), _currentPlayer.getMoney());
        printf("1: 修改昵称; 2: 修改密码; 0: 返回");
        printf("您的选择: ");
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
                return;
            }
            default: {
                // system("cls");
                printf("ID: %16s, 昵称: %16s\n分数:%16d, 金钱:%16d\n", _currentPlayer.getId().c_str(), _currentPlayer.getName().c_str(), _currentPlayer.getScore(), _currentPlayer.getMoney());
                printf("1: 修改昵称; 2: 修改密码; 0: 返回");
                printf("您的选择: ");
            }
        }
    }
}

void App::changeNamePage() {
    // system("cls");
    std::string newName;
    printf("请输入新昵称: ");
    std::cin >> newName;

    if (newName.size() < 6 || newName.size() > 16) {
        std::cout << "昵称长度需要在6-16之间!\n";
        Sleep(1000);
        return;
    }

    _currentPlayer.setName(newName);
}

void App::changePasswordPage() {
    // system("cls");
    std::string newPassword;
    printf("请输入新密码: ");
    std::cin >> newPassword;

    if (newPassword.size() < 6 || newPassword.size() > 16) {
        std::cout << "密码长度需要在6-16之间!\n";
        Sleep(1000);
        return;
    }

    _currentPlayer.setPassword(newPassword);
}
