#ifndef SETTING_SCREEN_H
#define SETTING_SCREEN_H
#include <windows.h>
#include <iostream>
#include "Screen.h"

class SettingScreen : public Screen {
public:
    void show() override {
        system("cls");
        std::cout << "=== SETTINGS ===\n";
        std::cout << "1. Change color\n";
        std::cout << "2. Sound: ON/OFF\n";
    }

    void handleInput() override {
        int c;
        std::cin >> c;
        // xử lý cài đặt
    }
};
#endif 