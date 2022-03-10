#ifndef CHINESECHESS_PLAYER_H
#define CHINESECHESS_PLAYER_H

#include "string"


class Player {
private:
    std::string _id;
    std::string _password;
    std::string _name;
    unsigned _score;
    unsigned _money;

public:
    std::string getId();
    void setId(std::string id);

    std::string getPassword();
    void setPassword(std::string password);

    std::string getName();
    void setName(std::string name);

    unsigned getMoney();
    void setMoney(unsigned money);
    void addMoney(unsigned n);
    void decMoney(unsigned n);

    unsigned getScore();
    void addScore(unsigned n);
    void decScore(unsigned n);


};


#endif //CHINESECHESS_PLAYER_H
