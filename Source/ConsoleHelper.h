#pragma once
#include <windows.h> // để dùng HANDLE và COORD
#include <iostream>

class ConsoleHelper
{
public:
    static void gotoXY(int x, int y);
    static void SetConsoleCursorType(int size, bool visible);
    static void getConsoleSize(int& width, int& height);
    static void setConsoleSize(int width, int height);
    static void clearConsole();
    static char getCharAtXY(int x, int y);
    static void setConsoleColor(WORD color);
    static void setTextColor(WORD color);
    static void drawHighlightCell(int x, int y, int cellW, int cellH, bool highlight, char symbol);
};

