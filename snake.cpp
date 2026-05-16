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
    if (body.head == nullptr || body.size < 2) return false;
    Node* head = body.head;
    // Kiểm tra đầu rắn có trùng với bất kỳ đốt nào từ đốt thứ 2 trở đi
    Node* curr = head->next;
    while (curr != head) {
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
