#include "renderer.h"
#include <iostream>
#include <string>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// =====================================================
// renderer.cpp — NGƯỜI 2
// =====================================================

Renderer::Renderer(int w, int h) : width(w), height(h) {}

void Renderer::clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Renderer::go_to_top() {
    // Di chuyển cursor về (0,0) thay vì clear toàn màn hình → mượt hơn
#ifdef _WIN32
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    std::cout << "\033[H";
#endif
}

void Renderer::draw(Snake& snake, Food& food, int score) {
    go_to_top();

    // Tạo buffer 2D
    std::vector<std::string> grid(height, std::string(width, ' '));

    // Vẽ thân rắn
    CircularLinkedList& body = snake.get_body();
    if (body.head != nullptr) {
        Node* curr = body.head;
        bool isHead = true;
        do {
            if (curr->x >= 0 && curr->x < width && curr->y >= 0 && curr->y < height) {
                grid[curr->y][curr->x] = isHead ? '@' : 'o';
            }
            isHead = false;
            curr = curr->next;
        } while (curr != body.head);
    }

    // Vẽ mồi
    if (food.x >= 0 && food.x < width && food.y >= 0 && food.y < height)
        grid[food.y][food.x] = '*';

    // In viền trên
    std::cout << '+' << std::string(width, '-') << "+\n";

    // In từng hàng
    for (int y = 0; y < height; y++) {
        std::cout << '|' << grid[y] << "|\n";
    }

    // In viền dưới
    std::cout << '+' << std::string(width, '-') << "+\n";
    std::cout << " Score: " << score
              << "  Length: " << snake.get_length()
              << "  [W/A/S/D to move, Q to quit]\n";
}

void Renderer::draw_game_over(int score) {
    clear_screen();
    std::cout << "\n\n";
    std::cout << "  ================================\n";
    std::cout << "          GAME OVER!\n";
    std::cout << "  ================================\n";
    std::cout << "    Final Score  : " << score << "\n";
    std::cout << "\n  Press Enter to exit...\n";
}

void Renderer::draw_start_screen() {
    clear_screen();
    std::cout << "\n\n";
    std::cout << "   ___              _         \n";
    std::cout << "  / __| _ _  __ _ | |__ ___  \n";
    std::cout << "  \\__ \\| ' \\/ _` || / // -_) \n";
    std::cout << "  |___/|_||_\\__,_||_\\_\\\\___|  \n";
    std::cout << "\n  DSA Project — Circular Linked List\n";
    std::cout << "\n  Press Enter to start...\n";
    std::cin.get();
}
