#include "ConsoleHelper.h"

void ConsoleHelper::gotoXY(int x, int y) {
    HANDLE hConsoleOutput;
    COORD Cursor_Pos;
    Cursor_Pos.X = x;
    Cursor_Pos.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}

void ConsoleHelper::SetConsoleCursorType(int size, bool visible) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    // Giới hạn kích thước trong khoảng 1–100 (%)
    if (size < 1) size = 1;
    if (size > 100) size = 100;

    cursorInfo.dwSize = size;     // độ dày con trỏ (1 = mảnh, 100 = khối)
    cursorInfo.bVisible = visible; // true = hiện, false = ẩn
    SetConsoleCursorInfo(out, &cursorInfo);
}

void ConsoleHelper::getConsoleSize(int& width, int& height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    else {
        width = height = 0; // lỗi khi không lấy được
    }
}

void ConsoleHelper::setConsoleSize(int width, int height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rect = { 0, 0, (SHORT)(width - 1), (SHORT)(height - 1) };
    COORD coord = { (SHORT)width, (SHORT)height };

    SetConsoleScreenBufferSize(hConsole, coord);
    SetConsoleWindowInfo(hConsole, TRUE, &rect);
}

void ConsoleHelper::clearConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD cellCount;
    DWORD count;
    COORD homeCoords = { 0, 0 };

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
        return;

    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
    SetConsoleCursorPosition(hConsole, homeCoords);
}

char ConsoleHelper::getCharAtXY(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CHAR_INFO ci;
    SMALL_RECT readRect = { (SHORT)x, (SHORT)y, (SHORT)x, (SHORT)y };
    COORD bufferSize = { 1, 1 };
    COORD bufferCoord = { 0, 0 };

    if (ReadConsoleOutputA(hConsole, &ci, bufferSize, bufferCoord, &readRect))
        return ci.Char.AsciiChar;
    else
        return '\0'; // lỗi
}

void ConsoleHelper::setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    COORD home = { 0, 0 };

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
        return;

    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputAttribute(hConsole, color, cellCount, home, &count);
    SetConsoleCursorPosition(hConsole, home);
}

void ConsoleHelper::setTextColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void ConsoleHelper::drawHighlightCell(int x, int y, int cellW, int cellH, bool highlight, char symbol) {
    gotoXY(x + cellW / 2, y + cellH / 2);

    // Màu chữ và nền tuỳ theo ký hiệu
    int colorNormal = (symbol == 'X') ? 0xF4 : 0xF3; // X xanh, O đỏ (tự chỉnh)
    int colorHighlight = (symbol == 'X') ? 0x1C : 0x1B; // Khi được chọn: nền sáng hơn

    if (highlight) {
        setTextColor(colorHighlight);
    }
    else {
        setTextColor(colorNormal);
    }

    std::cout << symbol;

    // Reset lại màu mặc định sau khi vẽ
    setTextColor(0x07);
}
