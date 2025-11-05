#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Board.h"

class Player {
protected:
    int markInFile;
    int mark;
    int colorMark;
    std::string name;
    int point;

public:
    Player(int markInFile, int mark, int colorMark, const std::string& name);
    virtual ~Player() = default;

    // getter
    int getMarkInFile() const;
    int getMark() const;
    int getColorMark() const;
    std::string getName() const;
    int getPoint() const;

    // setter
    void setName(const std::string& newName);
    void setPoint(int p);
    void setColorMark(int color);

    virtual void makeMove(Board& board, int& a, int& b) = 0;
};

#endif
