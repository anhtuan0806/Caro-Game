#include "Bot.h"

void Bot::makeMove(Board& board, int& a, int& b) {
    srand((unsigned)time(0));
    int n = board.getSize();
    do {
        a = rand() % n;
        b = rand() % n;
    } while (!board.isEmpty(a, b));

    Sleep(500);
}
