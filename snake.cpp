#include "snake.h"

// =====================================================
// snake.cpp — NGƯỜI 1
// =====================================================

Snake::Snake(int startX, int startY, int initLen) : dir(RIGHT) {
    // Khởi tạo rắn nằm ngang, đầu ở (startX, startY)
    for (int i = initLen - 1; i >= 0; i--) {
        body.push_front(startX - i, startY);
    }
}

void Snake::move() {
    Node* h = get_head();
    int nx = h->x, ny = h->y;

    switch (dir) {
        case UP:    ny--; break;
        case DOWN:  ny++; break;
        case LEFT:  nx--; break;
        case RIGHT: nx++; break;
    }

    body.push_front(nx, ny);
    body.pop_back();
}

void Snake::grow() {
    Node* h = get_head();
    int nx = h->x, ny = h->y;

    switch (dir) {
        case UP:    ny--; break;
        case DOWN:  ny++; break;
        case LEFT:  nx--; break;
        case RIGHT: nx++; break;
    }

    body.push_front(nx, ny);
    // Không pop_back → rắn dài thêm 1
}

void Snake::set_direction(Direction newDir) {
    // Không cho phép quay 180 độ
    if (dir == UP    && newDir == DOWN)  return;
    if (dir == DOWN  && newDir == UP)    return;
    if (dir == LEFT  && newDir == RIGHT) return;
    if (dir == RIGHT && newDir == LEFT)  return;
    dir = newDir;
}

Direction Snake::get_direction() const {
    return dir;
}

bool Snake::is_self_collision() const {
    // Rắn không thể tự cắn nếu độ dài nhỏ hơn 4
    if (body.head == nullptr || body.size < 4) {
        return false;
    }

    Node* head = body.head;
    Node* curr = head->next;

    // Duyệt qua các đốt còn lại của thân rắn (bỏ qua đầu).
    // Dùng vòng lặp for với size để tránh lỗi nếu DSLK vòng bị lỗi con trỏ.
    for (int i = 0; i < body.size - 1; ++i) {
        if (curr->x == head->x && curr->y == head->y) return true;
        curr = curr->next;
    }
    return false;
}

bool Snake::is_out_of_bounds(int boardW, int boardH) const {
    Node* h = body.head;
    if (h == nullptr) return false;
    return (h->x < 0 || h->x >= boardW || h->y < 0 || h->y >= boardH);
}

Node* Snake::get_head() const {
    return body.head;
}

CircularLinkedList& Snake::get_body() {
    return body;
}

int Snake::get_length() const {
    return body.size;
}
