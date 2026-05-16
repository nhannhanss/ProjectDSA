#pragma once

// =====================================================
// circular_list.h — NGƯỜI 1
// Danh sách liên kết vòng đơn
// Dùng để lưu thân con rắn
// =====================================================

struct Node {
    int x, y;
    Node* next;

    Node(int x, int y) : x(x), y(y), next(nullptr) {}
};

class CircularLinkedList {
public:
    Node* head;
    int size;

    CircularLinkedList();
    ~CircularLinkedList();

    // Thêm node vào đầu (đầu rắn mới sau khi di chuyển)
    void push_front(int x, int y);

    // Xóa node cuối (đuôi rắn khi di chuyển)
    void pop_back();

    // Lấy node cuối (đuôi rắn)
    Node* get_tail();

    // Kiểm tra tọa độ (x,y) có nằm trong danh sách không
    bool contains(int x, int y) const;

    // Xóa toàn bộ danh sách
    void clear();

    // In ra để debug
    void print_all() const;
};
