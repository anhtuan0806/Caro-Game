#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include "Screen.h"
#include <iostream>
#include "Game.h"

class MenuScreen : public Screen {
public:
    void show() override {
        system("cls");
        ConsoleHelper::setConsoleColor(0xF0); 
        std::cout << "=== CARO ===\n";
        std::cout << "1. Play Game\n";
        std::cout << "2. Settings\n";
        std::cout << "3. Help\n";
        std::cout << "4. Exit\n";
    }

    void handleInput() override {
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            Game* game = new Game(3, 3, Mode::PVP);
            game->start();
            delete game;   
        }
        else {

        }
    }
};
#endif 