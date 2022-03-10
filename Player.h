#ifndef CHINESECHESS_PLAYER_H
#define CHINESECHESS_PLAYER_H

#include "string"


class Player {
private:
    std::string _id;
    std::string _password;
    std::string _name;
    unsigned _score{};
    unsigned _money{};

public:

    Player(std::string & id, std::string & password, std::string & name, unsigned score = 100, unsigned money = 100) {
        _id = id;
        _password = password;
        _name = name;
        _score = score;
        _money = money;
    }

    Player() = default;

    std::string getId() {return _id;}
    void setId(std::string & id) {_id = id;}

    std::string getPassword() {return _password;};
    bool setPassword(std::string & password);

    std::string getName() {return _name;};
    void setName(std::string & name) {_name = name;}

    unsigned getMoney() const {return _money;};
    void addMoney(unsigned n) {_money += n;}
    bool decMoney(unsigned n);

    unsigned getScore() const {return _score;}
    void addScore(unsigned n) {_score += n;}
    void decScore(unsigned n);

};


#endif //CHINESECHESS_PLAYER_H
