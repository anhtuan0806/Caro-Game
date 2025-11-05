#ifndef BOT_H
#define BOT_H

#include "Player.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

class Bot : public Player {
public:
    using Player::Player;

    void makeMove(Board& board, int& a, int& b);
};

#endif
