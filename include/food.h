#pragma once
#include "circular_list.h"

// =====================================================
// food.h — NGƯỜI 1
// =====================================================

class Food {
public:
    int x, y;

    Food();

    // Sinh mồi tại vị trí ngẫu nhiên, tránh thân rắn
    void spawn(int boardW, int boardH, CircularLinkedList& snakeBody);
};
