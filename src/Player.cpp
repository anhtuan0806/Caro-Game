#include "Player.h"

Player::Player(int markInFile, char mark, int colorMark, std::string name) : point(0) , markInFile(markInFile) , mark(mark), colorMark(colorMark), name(name){}

Player Player::get() {
	return *this;
}

int Player::getMarkInFile() {
	return this->markInFile;
}

char Player::getMark() {
	return this->mark;
}
