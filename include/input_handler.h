#pragma once
#include "snake.h"

// =====================================================
// input_handler.h — NGƯỜI 2
// Nhận phím bấm không blocking
// =====================================================

class InputHandler {
public:
    // Trả về Direction mới dựa trên phím bấm
    // Nếu không bấm gì → trả về currentDir
    static Direction get_input(Direction currentDir);
};
