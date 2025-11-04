#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
protected:
    int markInFile;
    char mark;
    int colorMark;
    std::string name;
    int point;

public:
    Player(int markInFile, char mark, int colorMark, const std::string& name);
    virtual ~Player() = default;

    // getter
    int getMarkInFile() const;
    char getMark() const;
    int getColorMark() const;
    std::string getName() const;
    int getPoint() const;

    // setter
    void setName(const std::string& newName);
    void setPoint(int p);
    void setColorMark(int color);

    virtual void makeMove(int& x, int& y) = 0; 
};

#endif
