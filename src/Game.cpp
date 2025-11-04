#include "Game.h"

Game::Game(int condition, int boardSize, Mode modeGame) : turn(1), condition(condition), board(Board(boardSize)) {
    player1 = new Human(1, 'X', 7, " ");
    player2 = new Human(-1, 'O', 7, " ");
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

                if (checkWin(a, b)) {
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

bool Game::checkWin(int lastX, int lastY) {
    char symbol = board.get(lastX, lastY);
    if (symbol == ' ') return false;

    int n = board.getSize();
    int cond = this->condition; // số quân liên tiếp cần để thắng

    // 4 hướng chính 
    int dx[4] = {1, 0, 1, 1};
    int dy[4] = {0, 1, 1, -1};

    auto inBoard = [&](int x, int y) {
        return (x >= 0 && y >= 0 && x < n && y < n);
    };

    for (int dir = 0; dir < 4; dir++) {
        int count = 1; // đếm quân liên tiếp (bắt đầu từ quân vừa đánh)

        // Duyệt tiến
        int x = lastX + dx[dir];
        int y = lastY + dy[dir];
        while (inBoard(x, y) && board.get(x, y) == symbol) {
            count++;
            x += dx[dir];
            y += dy[dir];
        }

        // Duyệt lùi (ngược hướng)
        x = lastX - dx[dir];
        y = lastY - dy[dir];
        while (inBoard(x, y) && board.get(x, y) == symbol) {
            count++;
            x -= dx[dir];
            y -= dy[dir];
        }

        if (count >= cond)
            return true;
    }

    return false;
}