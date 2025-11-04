#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include "Player.h"
#include <conio.h>
#include <iostream>

enum class Mode {
	PVP,
	PVE
};

class Game
{
private:
	int turn;
	int condition;
	Board board;
	Player* player1;
	Player* player2;
	Mode modeGame;

public:
	Game(int, int, Mode);
	void start();
	void switchTurn();
	bool checkWin(int lastX = 0, int lastY = 0);
	Player getPlayer1();
	Player getPlayer2();
};
#endif