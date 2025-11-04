#include "Board.h"

Board::Board(int boardSize) 
	: boardSize(boardSize), boardMark(boardSize, std::vector<int>(boardSize, 0)){}

int Board::getSize() {
	return this->boardSize;
}

int Board::get(int a, int b) {
	return this->boardMark[a][b];
}

char Board::getSymbolAt(int row, int col) {
    int mark = boardMark[row][col];
    if (mark == 1) return 'X';
    if (mark == -1) return 'O';
    return ' ';
}

void Board::draw() {
    ConsoleHelper::setTextColor(0xF0);
    int consoleW, consoleH;
    ConsoleHelper::getConsoleSize(consoleW, consoleH);

    const int cellWidth = 4;
    const int cellHeight = 2;

    int boardWidth = boardSize * cellWidth + 1;
    int boardHeight = boardSize * cellHeight + 1;

    int startX = (consoleW - boardWidth) / 2;
    int startY = (consoleH - boardHeight) / 2;

    // Vẽ khung
    for (int i = 0; i <= boardSize; i++) {
        for (int j = 0; j <= boardSize; j++) {
            int x = startX + j * cellWidth;
            int y = startY + i * cellHeight;

            ConsoleHelper::gotoXY(x, y);

            // Góc
            if (i == 0 && j == 0) std::cout << char(218);           // ┌
            else if (i == 0 && j == boardSize) std::cout << char(191); // ┐
            else if (i == boardSize && j == 0) std::cout << char(192); // └
            else if (i == boardSize && j == boardSize) std::cout << char(217); // ┘
            // Đường nối
            else if (i == 0) std::cout << char(194);       // ┬
            else if (i == boardSize) std::cout << char(193); // ┴
            else if (j == 0) std::cout << char(195);       // ├
            else if (j == boardSize) std::cout << char(180); // ┤
            else std::cout << char(197);                   // ┼

            // Vẽ ngang
            if (j < boardSize) {
                for (int k = 1; k < cellWidth; k++) std::cout << char(196); // ─
            }
        }

        // Vẽ dọc
        if (i < boardSize) {
            for (int k = 1; k < cellHeight; k++) {
                for (int j = 0; j <= boardSize; j++) {
                    ConsoleHelper::gotoXY(startX + j * cellWidth, startY + i * cellHeight + k);
                    std::cout << char(179); // │
                }
            }
        }
    }
}

bool Board::isEmpty(int a, int b) {
    // First check bounds, then check mark value
    if (a < 0 || a >= this->boardSize || b < 0 || b >= this->boardSize)
        return false;
    return boardMark[a][b] == 0;
}

void Board::placeMark(int a, int b, int mark) {
	boardMark[a][b] = mark;
}