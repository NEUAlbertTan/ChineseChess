#include "Chess.h"


void Chess::draw() {
    switch (_chessCategory) {
        case KING:
            DrawerHelper::moveCursorTo(_x, _y);
            std::cout << (_playerNumber == 1 ? 'J' : 'j');
            break;
        case GUARD:
            std::cout << (_playerNumber == 1 ? 'S' : 's');
            break;
        case BISHOP:
            std::cout << (_playerNumber == 1 ? 'X' : 'x');
            break;
        case KNIGHT:
            std::cout << (_playerNumber == 1 ? 'M' : 'm');
            break;
        case ROOK:
            std::cout << (_playerNumber == 1 ? 'C' : 'c');
            break;
        case CANNON:
            std::cout << (_playerNumber == 1 ? 'P' : 'p');
            break;
        case PAWN:
            std::cout << (_playerNumber == 1 ? 'B' : 'b');
            break;
    }
}
