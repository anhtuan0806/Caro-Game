#include "Game.h"

int main() {
	ConsoleHelper::setConsoleColor(0xF0); // nền trắng, chữ đen
	Game game(3, 3, Mode::PVP);
	game.start();

	return 0;
}