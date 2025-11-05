#ifndef SCREEN_H
#define SCREEN_H

class Screen {
public:
    virtual ~Screen() = default;
    virtual void show() = 0;   // hiển thị giao diện
    virtual void handleInput() = 0; // xử lý phím người dùng
};

#endif