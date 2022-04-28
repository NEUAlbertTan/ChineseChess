#include "Player.h"


bool Player::setPassword(std::string & password) {
    if (password.size() < 6 || password.size() > 16) {
        return false;
    }

    _password = password;
    return true;
}


bool Player::decMoney(unsigned int n) {
    if (n > _money) {
        return false;
    }

    _money -= n;
    return true;
}


void Player::decScore(unsigned int n) {
    if (_score <= n) {
        _score = 0;
    } else {
        _score -= n;
    }

}
