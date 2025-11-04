#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>
#include "ConsoleHelper.h"

class Board
{
private:
	int boardSize;
	std::vector<std::vector<int>> boardMark;

public:
	Board(int);
	int getSize();
	std::vector<std::vector<int>> getBoardMark();
	int get(int, int);
	char getSymbolAt(int row, int col);
	void draw();
	bool isEmpty(int, int);
	void placeMark(int, int, int);
};
#endif 