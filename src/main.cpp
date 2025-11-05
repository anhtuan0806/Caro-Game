#include "Screen.h"
#include "MenuScreen.h"

int main() {
	Screen* screen = new MenuScreen;
	screen->show();
	screen->handleInput();
	delete screen;
	return 0;
}