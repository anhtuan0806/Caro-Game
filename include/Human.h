#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include "ConsoleHelper.h"
#include <conio.h>
#include <windows.h>

class Human : public Player {
public:
    using Player::Player; // kế thừa constructor

    void makeMove(Board& board, int& a, int& b);
};

#endif
