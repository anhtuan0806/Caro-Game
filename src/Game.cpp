#include "Game.h"

Game::Game(int condition, int boardSize, Mode modeGame) : turn(1), condition(condition), board(Board(boardSize)) {
    player1 = new Human(1, 1, 3, " ");
    player2 = new Bot(-1, -1, 4, " ");
}

void Game::start() {
    board.draw();
    ConsoleHelper::SetConsoleCursorType(2, false);

    Player* current = player1;
    int a = 0, b = 0;

    while (true) {
        current->makeMove(board, a, b);
        if (a == -1 && b == -1) break;

        board.placeMark(a, b, current->getMarkInFile());
        board.drawCell(a, b); 

        if (checkWin(a, b)) {
            std::cout << "\n" << current->getMark() << " thắng!\n";
            break;
        }

        current = (current == player1) ? player2 : player1;
    }
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