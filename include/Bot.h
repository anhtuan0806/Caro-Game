#ifndef BOT_H
#define BOT_H

#include "Player.h"
#include <cstdlib>
#include <ctime>


class Bot : public Player {
public:
    using Player::Player;

    void makeMove(int& x, int& y);
};

#endif
