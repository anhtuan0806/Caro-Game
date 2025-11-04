#include "Game.h"

Game::Game(int condition, int boardSize, Mode modeGame) : turn(1), condition(condition), board(Board(boardSize)) {
    player1 = new Player(1, 'X', 7, " ");
    player2 = new Player(-1, 'O', 7, " ");
}

void Game::start() {
    this->board.draw();
    ConsoleHelper::SetConsoleCursorType(2, false);

    const int cellWidth = 4;
    const int cellHeight = 2;

    int a = 0, b = 0;
    int boardSize = this->board.getSize();

    // Lấy tọa độ góc trên trái của bàn cờ
    int consoleW, consoleH;
    ConsoleHelper::getConsoleSize(consoleW, consoleH);
    int boardWidth = boardSize * cellWidth + 1;
    int boardHeight = boardSize * cellHeight + 1;
    int startX = (consoleW - boardWidth) / 2;
    int startY = (consoleH - boardHeight) / 2;

    // Tọa độ ô hiện tại
    int curX = startX + b * cellWidth;
    int curY = startY + a * cellHeight;

    char symbol = board.getSymbolAt(a, b);
    ConsoleHelper::drawHighlightCell(curX, curY, cellWidth, cellHeight, true, symbol);

    bool highlightOn = true;
    ULONGLONG lastBlink = GetTickCount64();

    while (true) {
        // Hiệu ứng nhấp nháy mỗi 300 ms
        if (GetTickCount64() - lastBlink > 300) {
            highlightOn = !highlightOn;
            symbol = board.getSymbolAt(a, b);
            ConsoleHelper::drawHighlightCell(curX, curY, cellWidth, cellHeight, highlightOn, symbol);
            lastBlink = GetTickCount64();
        }

        // Nếu có phím nhấn thì xử lý
        if (_kbhit()) {
            int ch = _getch();

            // Xóa highlight hiện tại
            symbol = board.getSymbolAt(a, b);
            ConsoleHelper::drawHighlightCell(curX, curY, cellWidth, cellHeight, false, symbol);

            if (ch == 224 || ch == 0) {  // phím mũi tên
                ch = _getch();
                if (ch == 72 && a > 0) a--; // Up
                else if (ch == 80 && a < boardSize - 1) a++; // Down
                else if (ch == 75 && b > 0) b--; // Left
                else if (ch == 77 && b < boardSize - 1) b++; // Right
            }
            else if (ch == 13 && this->board.isEmpty(a, b)) { // Enter
                this->board.placeMark(a, b, this->turn);
                this->board.draw(); // vẽ lại bàn cờ

                if (checkWin()) {
                    printf("%d da thang", turn);
                    break;
                }
                switchTurn();
            }
            else if (ch == 'x') break;

            // Cập nhật tọa độ mới
            curX = startX + b * cellWidth;
            curY = startY + a * cellHeight;
            symbol = board.getSymbolAt(a, b);

            // Hiển thị ô mới
            ConsoleHelper::drawHighlightCell(curX, curY, cellWidth, cellHeight, true, symbol);

            // Reset thời gian nhấp nháy để không bị lệch
            lastBlink = GetTickCount64();
        }

        Sleep(30); // nghỉ nhẹ để CPU không 100%
    }

    symbol = board.getSymbolAt(a, b);
    ConsoleHelper::drawHighlightCell(curX, curY, cellWidth, cellHeight, true, symbol);
}

void Game::switchTurn() {
	this->turn = (this->turn == player1->getMarkInFile() ? player2->getMarkInFile() : player1->getMarkInFile());
}

bool Game::checkWin() {
    int n = board.getSize();

    int dX[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dY[8] = {0, 0, -1, 1, -1, 1, -1, 1};

    int cnt = 0;


    for (int x : boardMark) {

    }

        // Duyet ngang
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n - this->condition; j++) {
            bool flag = true;
            for (int k = 0; k < this->condition; k++) {
                if (board.get(i, j + k) != this->turn) {
                    flag = false;
                    break;
                }
            }
            if (flag) return true;
        }
    }

    // Duyet doc
    for (int i = 0; i <= n - this->condition; i++) {
        for (int j = 0; j < n; j++) {
            bool flag = true;
            for (int k = 0; k < this->condition; k++) {
                if (board.get(i + k, j) != this->turn) {
                    flag = false;
                    break;
                }
            }
            if (flag) return true;
        }
    }

    // Duyet cheo phai (\)
    for (int i = 0; i <= n - this->condition; i++) {
        for (int j = 0; j <= n - this->condition; j++) {
            bool flag = true;
            for (int k = 0; k < this->condition; k++) {
                if (board.get(i + k, j + k) != this->turn) {
                    flag = false;
                    break;
                }
            }
            if (flag) return true;
        }
    }

    // Duyet cheo trai (/)
    for (int i = 0; i <= n - this->condition; i++) {
        for (int j = this->condition - 1; j < n; j++) {
            bool flag = true;
            for (int k = 0; k < this->condition; k++) {
                if (board.get(i + k, j - k) != this->turn) {
                    flag = false;
                    break;
                }
            }
            if (flag) return true;
        }
    }

    return false;


}