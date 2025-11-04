#include "Game.h"

int main() {
	ConsoleHelper::setConsoleColor(0xF0); 
	Game* game = new Game(5, 15, Mode::PVP);
	game->start();
	delete game;
	return 0;
}