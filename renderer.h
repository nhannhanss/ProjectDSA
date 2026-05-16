#pragma once
#include "snake.h"
#include "food.h"

// =====================================================
// renderer.h — NGƯỜI 2
// Vẽ toàn bộ game ra console
// =====================================================

class Renderer {
private:
    int width, height;

public:
    Renderer(int w, int h);

    void draw(Snake& snake, Food& food, int score);
    void draw_game_over(int score);
    void draw_start_screen();

private:
    void clear_screen();
    void go_to_top();    // đưa cursor về đầu, tránh nhấp nháy
};
