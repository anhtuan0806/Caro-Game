#include "Player.h"

Player::Player(int markInFile, char mark, int colorMark, const std::string& name)
    : markInFile(markInFile), mark(mark), colorMark(colorMark), name(name), point(0) {}

int Player::getMarkInFile() const { 
	return markInFile; 
}
char Player::getMark() const { 
	return mark; 
}
int Player::getColorMark() const { 
	return colorMark; 
}
std::string Player::getName() const { 
	return name; 
}
int Player::getPoint() const { 
	return point; 
}

void Player::setName(const std::string& newName) { 
	name = newName; 
}
void Player::setPoint(int p) { 
	point = p; 
}
void Player::setColorMark(int color) { 
	colorMark = color; 
}