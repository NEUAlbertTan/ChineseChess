#include "FileSys.h"

bool FileSys::savePlayers(std::vector<Player> & players) {
    std::ofstream out;

    try {
        out.open(_filePath);
    } catch (std::exception & e) {
        std::cerr << "Failed to open players' file.";
        return false;
    }

    for (auto & player : players) {
        out << player.getId() << ' ' << player.getPassword() << ' ' << player.getName() << ' ' << player.getScore() << ' ' << player.getMoney() << std::endl;
    }

    out.close();
    return true;
}

std::vector<Player> FileSys::loadPlayers() {
    std::ifstream in;
    try {
        in.open(_filePath);
    } catch (std::exception & e) {
        std::cerr << "Failed to open players' file." << std::endl;
        exit(-1);
    }

    if (!in) {
        std::cerr << "File error!" << std::endl;
        exit(-1);
    }

    std::vector<Player> players;

    while (!in.eof()) {
        std::string id;
        std::string password;
        std::string name;
        unsigned score;
        unsigned money;

        in >> id >> password >> name >> score >> money;

        Player player(id, password, name, score, money);

        players.emplace_back(player);
    }

    in.close();
    return players;
}