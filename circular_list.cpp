#include "circular_list.h"
#include <iostream>

// =====================================================
// circular_list.cpp — NGƯỜI 1
// =====================================================

CircularLinkedList::CircularLinkedList() : head(nullptr), size(0) {}

CircularLinkedList::~CircularLinkedList() {
    clear();
}

void CircularLinkedList::push_front(int x, int y) {
    Node* newNode = new Node(x, y);
    if (head == nullptr) {
        // Danh sách rỗng: node tự trỏ vào chính nó (tính chất vòng)
        newNode->next = newNode;
        head = newNode;
    } else {
        // Tìm đuôi (node trỏ về head)
        Node* tail = get_tail();
        newNode->next = head;
        tail->next = newNode;
        head = newNode;
    }
    size++;
}

void CircularLinkedList::pop_back() {
    if (head == nullptr) return;

    if (size == 1) {
        delete head;
        head = nullptr;
        size = 0;
        return;
    }

    // Tìm node đứng trước đuôi
    Node* curr = head;
    while (curr->next->next != head) {
        curr = curr->next;
    }
    // curr->next là tail
    delete curr->next;
    curr->next = head;
    size--;
}

Node* CircularLinkedList::get_tail() {
    if (head == nullptr) return nullptr;
    Node* curr = head;
    while (curr->next != head) {
        curr = curr->next;
    }
    return curr;
}

bool CircularLinkedList::contains(int x, int y) const {
    if (head == nullptr) return false;
    Node* curr = head;
    do {
        if (curr->x == x && curr->y == y) return true;
        curr = curr->next;
    } while (curr != head);
    return false;
}

void CircularLinkedList::clear() {
    if (head == nullptr) return;
    Node* curr = head->next;
    while (curr != head) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    delete head;
    head = nullptr;
    size = 0;
}

void CircularLinkedList::print_all() const {
    if (head == nullptr) {
        std::cout << "(empty)\n";
        return;
    }
    Node* curr = head;
    do {
        std::cout << "(" << curr->x << "," << curr->y << ") -> ";
        curr = curr->next;
    } while (curr != head);
    std::cout << "(head)\n";
}
