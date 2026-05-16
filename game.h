#pragma once
#include "snake.h"
#include "food.h"
#include "renderer.h"
#include "input_handler.h"

// =====================================================
// game.h — NGƯỜI 2
// Vòng lặp game chính, kết nối tất cả module
// =====================================================

class Game {
private:
    int boardW, boardH;
    Snake snake;
    Food food;
    Renderer renderer;

    int score;
    int delayMs;    // tốc độ game (ms/frame)
    bool running;

public:
    Game(int w = 20, int h = 20);
    void run();

private:
    void update();
    void check_collisions();
    void increase_difficulty();
    void sleep_ms(int ms);
};
