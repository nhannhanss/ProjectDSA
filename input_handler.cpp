#include "input_handler.h"

// =====================================================
// input_handler.cpp — NGƯỜI 2
// Cross-platform: Windows dùng conio.h, Linux dùng termios
// =====================================================

#ifdef _WIN32
#include <conio.h>

Direction InputHandler::get_input(Direction currentDir) {
    if (!_kbhit()) return currentDir;  // không có phím nào → giữ hướng

    int ch = _getch();

    // Xử lý phím mũi tên (trả về 224 trước)
    if (ch == 224) {
        ch = _getch();
        switch (ch) {
            case 72: return UP;
            case 80: return DOWN;
            case 75: return LEFT;
            case 77: return RIGHT;
        }
    }

    // WASD
    switch (ch) {
        case 'w': case 'W': return UP;
        case 's': case 'S': return DOWN;
        case 'a': case 'A': return LEFT;
        case 'd': case 'D': return RIGHT;
    }

    return currentDir;
}

#else
// Linux / macOS — dùng termios để non-blocking input
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

static void set_nonblocking(bool enable) {
    static struct termios oldt;
    if (enable) {
        struct termios newt = oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, 0);
    }
}

Direction InputHandler::get_input(Direction currentDir) {
    set_nonblocking(true);
    char ch = 0;
    read(STDIN_FILENO, &ch, 1);
    set_nonblocking(false);

    switch (ch) {
        case 'w': case 'W': return UP;
        case 's': case 'S': return DOWN;
        case 'a': case 'A': return LEFT;
        case 'd': case 'D': return RIGHT;
    }
    return currentDir;
}
#endif
