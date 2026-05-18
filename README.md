# 🐍 Snake Game - DSA Project

**Đồ án môn học Cấu trúc Dữ liệu & Giải thuật**
Trò chơi "Rắn săn mồi" xây dựng trên môi trường Console, ứng dụng cấu trúc dữ liệu **Danh sách liên kết vòng (Circular Linked List)**. Dự án được thiết kế theo kiến trúc module hóa phục vụ làm việc nhóm (2 người).

---

## 🚀 Hướng Dẫn Sử Dụng (How to Use)

### 1. Yêu Cầu Hệ Thống
- Trình biên dịch C++ (Hỗ trợ chuẩn C++17 trở lên, ví dụ: GCC/MinGW)
- Make (GNU Make) để chạy tự động quy trình build.
- Hệ điều hành Windows (game sử dụng `_kbhit` và `getch` để bắt phím).

---

### 2. Cách Biên Dịch & Chạy Game
Clone git hoặc tải toàn bộ mã nguồn về máy, mở Terminal/Command Prompt và di chuyển (cd) tới thư mục gốc của dự án.

Cách 1: Sử dụng `Makefile` đã được cấu hình sẵn để biên dịch:
```bash
# Biên dịch trò chơi
make game

# Chạy trò chơi
.\bin\snake_game.exe
```
Cách 2: Nếu không muốn dùng MAKEFILE có thể build bằng g++ truyền thống
```bash
# Biên dịch
g++ -std=c++17 main.cpp circular_list.cpp snake.cpp food.cpp renderer.cpp input_handler.cpp game.cpp -o snake_game.exe

# Chạy trò chơi
.\bin\snake_game.exe
```

---

### Các Lệnh Build Bổ Trợ Khác
- **Biên dịch toàn bộ (Game + Tests + Performance):** `make all`
- **Biên dịch Unit Tests:** `make tests` (sau đó chạy thử nghiệm bằng `.\bin\run_tests.exe`)
- **Dọn dẹp file biên dịch (Object files & Binaries):** `make clean`

---

### 3. Cách Chơi
- Dùng các phím **W, A, S, D** hoặc **Phím mũi tên** để điều khiển hướng đi của rắn.
- Ăn mồi để tăng điểm và độ dài. Trò chơi kết thúc nếu đâm vào tường hoặc tự cắn vào mình.

---

## 📁 Cây Thư Mục Dự Án (Folder Tree)

Kiến trúc thư mục được quy hoạch theo chuẩn C/C++ chuyên nghiệp, phân tách rõ ràng mã nguồn (Source), khai báo (Header), file trung gian (Object) và file chạy (Binary).

```text
ProjectDSA/
├── Makefile                ← Script cấu hình tự động biên dịch toàn bộ dự án
├── README.md               ← Tài liệu hướng dẫn chung (File này)
├── bin/                    ← (Generated) Chứa các file thực thi (.exe) sau khi build
│   ├── run_perf.exe        ← File đánh giá hiệu năng thuật toán
│   ├── run_tests.exe       ← File chạy Unit tests
│   └── snake_game.exe      ← File thực thi chính của trò chơi
├── data/                   ← Thư mục lưu trữ dữ liệu trò chơi
│   ├── leaderboard.txt     ← Bảng xếp hạng điểm số cao
│   └── test_leaderboard.csv
├── docs/                   ← Tài liệu liên quan đến dự án (Quy chuẩn báo cáo, v.v.)
│   └── TEST_REPORT_GUIDE.md
├── include/                ← Chứa toàn bộ Header files (.h) định nghĩa các class/struct
│   ├── circular_list.h     ← Cấu trúc dữ liệu Circular Linked List
│   ├── data_manager.h
│   ├── food.h              ← Khởi tạo và quản lý mồi
│   ├── game.h              ← Vòng lặp và logic chính của game
│   ├── input_handler.h     ← Xử lý tín hiệu bàn phím (Non-blocking)
│   ├── renderer.h          ← Engine vẽ đồ họa trên console
│   ├── score_manager.h     ← Quản lý và lưu trữ điểm số
│   └── snake.h             ← Logic con rắn (di chuyển, va chạm, thay đổi kích thước)
├── obj/                    ← (Generated) Chứa các Object files (.o) sau khi biên dịch source
└── src/                    ← Chứa các Source code files (.cpp)
    ├── circular_list.cpp   ← Cài đặt cấu trúc dữ liệu chính
    ├── food.cpp
    ├── game.cpp
    ├── input_handler.cpp
    ├── main.cpp            ← Điểm khởi động game (Entry point)
    ├── performance_test.cpp← Script kiểm thử hiệu suất thực tế của DSLK
    ├── renderer.cpp
    ├── snake.cpp
    └── test_snake.cpp      ← Các kịch bản Unit test cho phần logic rắn
```

---

## 👥 Cấu Trúc Module (Phân Công 2 Người)

Dự án được chia làm hai mảng chính để hai thành viên có thể code song song.

### 👤 NGƯỜI 1 — Data Structure & Logic

Trọng tâm xử lý Cấu trúc Dữ liệu và logic của game.

#### `circular_list.h / .cpp`
Cài đặt **danh sách liên kết vòng** (yêu cầu môn học).
```cpp
struct Node {
    int x, y;       // Tọa độ mỗi đốt rắn
    Node* next;
};

class CircularLinkedList {
public:
    Node* head;
    int size;

    CircularLinkedList();
    void push_front(int x, int y);   // Thêm đầu (đầu rắn di chuyển tới)
    void pop_back();                  // Xóa đuôi (rắn trườn đi)
    void clear();
    Node* get_tail();                 // Lấy đốt cuối
    bool contains(int x, int y);     // Kiểm tra rắn tự cắn
    void print_all();                 // Dùng để debug
};
```

#### `snake.h / .cpp`
Sử dụng `CircularLinkedList` để quản lý cơ thể con rắn.
```cpp
enum Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
private:
    CircularLinkedList body;
    Direction dir;

public:
    Snake(int startX, int startY, int initLen);

    void set_direction(Direction newDir);
    Direction get_direction();

    void move();                      // Di chuyển: push_front + pop_back
    void grow();                      // Ăn mồi: push_front, KHÔNG pop_back
    bool is_self_collision();         // Tự cắn?
    bool is_out_of_bounds(int w, int h); // Đâm tường?

    Node* get_head();
    CircularLinkedList& get_body();
    int get_length();
};
```

#### `food.h / .cpp`
Quản lý vị trí và việc sinh mồi ăn.
```cpp
class Food {
public:
    int x, y;

    Food();
    void spawn(int boardW, int boardH, CircularLinkedList& snakeBody);
    // Sinh mồi ngẫu nhiên, đảm bảo không đè lên thân rắn
};
```

---

### 👤 NGƯỜI 2 — Game Engine & Rendering

Trọng tâm về vòng lặp game, xử lý I/O và đồ họa Console.

#### `renderer.h / .cpp`
Chịu trách nhiệm vẽ toàn bộ màn hình Console.
```cpp
class Renderer {
private:
    int width, height;

public:
    Renderer(int w, int h);
    void draw(Snake& snake, Food& food, int score);
    void draw_game_over(int score);
    void draw_start_screen();
    void clear_screen();

private:
    void draw_border();
    void draw_cell(int x, int y, char symbol);
};
```

#### `input_handler.h / .cpp`
Nhận tín hiệu phím bấm dạng non-blocking.
```cpp
class InputHandler {
public:
    static Direction get_input(Direction currentDir);
    // Nhận WASD hoặc phím mũi tên
    // Trả về hướng mới, hoặc giữ nguyên nếu không bấm
};
```

#### `game.h / .cpp`
Vòng lặp game chính — kết nối tất cả các module.
```cpp
class Game {
private:
    Snake snake;
    Food food;
    Renderer renderer;
    InputHandler input;

    int score;
    int speed;       // Delay giữa mỗi frame (ms)
    bool running;

public:
    Game(int boardW, int boardH);
    void run();          // Vòng lặp chính

private:
    void update();       // Xử lý logic mỗi tick
    void handle_input();
    void check_collisions();
    void increase_difficulty();
};
```

---

## 🔗 `main.cpp` — Điểm Ghép Nối Cuối

Được viết chung sau khi cả hai người đã hoàn thiện module của mình.
```cpp
#include "game.h"

int main() {
    Game game(20, 20);  // Khởi tạo bảng kích thước 20x20
    game.run();
    return 0;
}
```

---

## 📋 Bảng Phân Công Chi Tiết

| File | Người Đảm Nhận | Độ Khó | Ghi Chú |
|------|-------|--------|---------|
| `circular_list` | **Người 1** | ⭐⭐⭐ | Trọng tâm DSA |
| `snake` | **Người 1** | ⭐⭐⭐ | Ứng dụng DSLK vòng |
| `food` | **Người 1** | ⭐ | Logic đơn giản |
| `renderer` | **Người 2** | ⭐⭐⭐ | Đồ họa Console |
| `input_handler` | **Người 2** | ⭐⭐ | Xử lý phím Non-blocking |
| `game` | **Người 2** | ⭐⭐⭐ | Vòng lặp chính & Trạng thái game |
| `main.cpp` | **Cả hai** | ⭐ | Ghép code cuối cùng |

---

## ⚙️ Giao Diện Tương Tác Giữa 2 Người (Interface)

Để có thể code song song, **Người 1 cần hoàn thiện các file header (`.h`) trước**. 
Người 2 sẽ gọi các phương thức sau từ module của Người 1 để kết nối logic:

```cpp
// --- Tương tác với Snake ---
snake.move();
snake.grow();
snake.set_direction(dir);
snake.get_head()->x, ->y;
snake.get_length();
snake.is_self_collision();
snake.is_out_of_bounds(w, h);
snake.get_body();         // Cung cấp dữ liệu để Renderer vẽ thân rắn

// --- Tương tác với Food ---
food.x, food.y;
food.spawn(w, h, snake.get_body());
```
