#include "game.h"
#include "data_manager.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// =====================================================
// game.cpp — NGƯỜI 2
// =====================================================

Game::Game(int w, int h)
    : boardW(w), boardH(h),
      snake(w / 2, h / 2, 3),   // rắn bắt đầu ở giữa bảng
      food(),
      renderer(w, h),
      score(0), delayMs(200), running(true)
{
    food.spawn(boardW, boardH, snake.get_body());
}

void Game::run() {
    renderer.draw_start_screen();

    while (running) {
        // 1. Nhận input
        Direction newDir = InputHandler::get_input(snake.get_direction());
        snake.set_direction(newDir);

        // 2. Cập nhật logic
        update();

        // 3. Vẽ
        renderer.draw(snake, food, score);

        // 4. Tạm dừng
        sleep_ms(delayMs);
    }

    renderer.draw_game_over(score);
    
    // Clear the input buffer if there are any leftover characters
    while (std::cin.rdbuf()->in_avail() > 0) {
        std::cin.get();
    }
    
    std::cout << "\nGame Over! Your score: " << score << "\n";
    std::cout << "Enter your name for the leaderboard: ";
    std::string playerName;
    std::getline(std::cin, playerName);
    if (playerName.empty()) {
        playerName = "Anonymous";
    }

    DataManager dm;
    dm.loadData();
    dm.addData(playerName, score);
    dm.sortLeaderboard();
    dm.saveData();

    std::cout << "\n--- TOP HIGHSCORES ---\n";
    const auto& leaderboard = dm.getLeaderboard();
    for(size_t i = 0; i < 5 && i < leaderboard.size(); ++i) {
        std::cout << i + 1 << ". " << leaderboard[i].name << " - " << leaderboard[i].score << "\n";
    }
    std::cout << "----------------------\n";
    std::cout << "Press Enter to exit...";
    std::cin.get();
}

void Game::update() {
    Node* head = snake.get_head();
    int nx = head->x, ny = head->y;

    // Tính vị trí đầu rắn sau khi di chuyển
    Direction d = snake.get_direction();
    if (d == UP)    ny--;
    if (d == DOWN)  ny++;
    if (d == LEFT)  nx--;
    if (d == RIGHT) nx++;

    // Kiểm tra ăn mồi TRƯỚC khi move
    bool ate = (nx == food.x && ny == food.y);

    if (ate) {
        snake.grow();
        score += 10;
        food.spawn(boardW, boardH, snake.get_body());
        increase_difficulty();
    } else {
        snake.move();
    }

    check_collisions();
}

void Game::check_collisions() {
    if (snake.is_out_of_bounds(boardW, boardH) || snake.is_self_collision()) {
        running = false;
    }
}

void Game::increase_difficulty() {
    // Tăng tốc sau mỗi 50 điểm, tối thiểu 80ms
    if (score % 50 == 0 && delayMs > 80) {
        delayMs -= 20;
    }
}

void Game::sleep_ms(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}
