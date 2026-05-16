#pragma once
#include "circular_list.h"

// =====================================================
// snake.h — NGƯỜI 1
// Con rắn sử dụng CircularLinkedList làm thân
// =====================================================

enum Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
private:
    CircularLinkedList body;
    Direction dir;

public:
    Snake(int startX, int startY, int initLen = 3);

    // Di chuyển: thêm đầu mới, xóa đuôi cũ
    void move();

    // Ăn mồi: thêm đầu mới, GIỮ đuôi → rắn dài ra
    void grow();

    // Đổi hướng (không cho quay 180 độ)
    void set_direction(Direction newDir);
    Direction get_direction() const;

    // Va chạm
    bool is_self_collision() const;
    bool is_out_of_bounds(int boardW, int boardH) const;

    // Truy cập thân
    Node* get_head() const;
    CircularLinkedList& get_body();
    int get_length() const;
};
