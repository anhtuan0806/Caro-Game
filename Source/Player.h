#pragma once
#include <string>
class Player
{
private:
	int markInFile;
	char mark;
	int colorMark;
	std::string name;
	int point;

public:
	Player(int, char, int, std::string);
	Player get();
	int getMarkInFile();
	char getMark();
	int getColorMark();
	void set();
	void setName();
	void setPoint();
	void setColorMark();
};

