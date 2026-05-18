#include "food.h"
#include <cstdlib>
#include <ctime>

// =====================================================
// food.cpp — NGƯỜI 1
// =====================================================

Food::Food() : x(0), y(0) {
    srand((unsigned)time(nullptr));
}

void Food::spawn(int boardW, int boardH, CircularLinkedList& snakeBody) {
    do {
        x = rand() % boardW;
        y = rand() % boardH;
    } while (snakeBody.contains(x, y));
    // Đảm bảo mồi không xuất hiện trên thân rắn
}
