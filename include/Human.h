#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include <iostream>

class Human : public Player {
public:
    using Player::Player; 

    void makeMove(int& x, int& y);
};

#endif
