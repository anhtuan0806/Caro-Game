#include "Human.h"

void Human::makeMove(Board& board, int& a, int& b) {
    const int cellWidth = 4;
    const int cellHeight = 2;
    int n = board.getSize();

    int consoleW, consoleH;
    ConsoleHelper::getConsoleSize(consoleW, consoleH);
    int boardWidth = n * cellWidth + 1;
    int boardHeight = n * cellHeight + 1;
    int startX = (consoleW - boardWidth) / 2;
    int startY = (consoleH - boardHeight) / 2;

    // Bắt đầu từ vị trí hiện tại (a, b)
    int curX = startX + b * cellWidth;
    int curY = startY + a * cellHeight;
    char symbol = board.getSymbolAt(a, b);

    ConsoleHelper::drawHighlightCell(curX, curY, cellWidth, cellHeight, true, symbol);
    bool highlightOn = true;
    ULONGLONG lastBlink = GetTickCount64();

    while (true) {
        // Hiệu ứng nhấp nháy
        if (GetTickCount64() - lastBlink > 300) {
            highlightOn = !highlightOn;
            symbol = board.getSymbolAt(a, b);
            ConsoleHelper::drawHighlightCell(curX, curY, cellWidth, cellHeight, highlightOn, symbol);
            lastBlink = GetTickCount64();
        }

        // Bắt phím
        if (_kbhit()) {
            int ch = _getch();

            // Xóa highlight
            symbol = board.getSymbolAt(a, b);
            ConsoleHelper::drawHighlightCell(curX, curY, cellWidth, cellHeight, false, symbol);

            if (ch == 224 || ch == 0) {
                ch = _getch();
                if (ch == 72 && a > 0) a--; // Up
                else if (ch == 80 && a < n - 1) a++; // Down
                else if (ch == 75 && b > 0) b--; // Left
                else if (ch == 77 && b < n - 1) b++; // Right
            } 
            else if (ch == 13 && board.isEmpty(a, b)) {
                // Enter → chọn ô
                break;
            }
            else if (ch == 'x') {
                a = b = -1; // báo hiệu thoát
                break;
            }

            // cập nhật ô mới
            curX = startX + b * cellWidth;
            curY = startY + a * cellHeight;
            symbol = board.getSymbolAt(a, b);
            ConsoleHelper::drawHighlightCell(curX, curY, cellWidth, cellHeight, true, symbol);
            lastBlink = GetTickCount64();
        }

        Sleep(30);
    }
}
