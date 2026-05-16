# 🐍 Snake Game - DSA Projectx
## Cấu trúc module (2 người)
### HOW TO USE
#### CHẠY TRONG TERMINAL: 
g++ -std=c++17 -o snake_game main.cpp circular_list.cpp snake.cpp food.cpp renderer.cpp input_handler.cpp game.cpp
   snake_game.exe
##### Lưu ý: Phải cd về chỗ chứa thư mục trước: vd: cd E:   
---

## 📁 Cây thư mục

```
snake_game/
├── README.md
├── main.cpp              ← điểm khởi động (viết chung cuối cùng)
│
├── [NGƯỜI 1] — Data Structure & Game Logic
│   ├── circular_list.h       ← cấu trúc danh sách liên kết vòng
│   ├── circular_list.cpp
│   ├── snake.h               ← con rắn (dùng DSLK vòng)
│   ├── snake.cpp
│   ├── food.h                ← sinh mồi
│   └── food.cpp
│
└── [NGƯỜI 2] — Game Engine & Rendering
    ├── renderer.h            ← vẽ bản đồ ra console
    ├── renderer.cpp
    ├── input_handler.h       ← nhận phím bấm
    ├── input_handler.cpp
    ├── game.h                ← vòng lặp game chính
    └── game.cpp
```

---

## 👤 NGƯỜI 1 — Data Structure & Logic

### `circular_list.h / .cpp`
Cài đặt **danh sách liên kết vòng** (yêu cầu môn học).

```cpp
struct Node {
    int x, y;       // tọa độ mỗi đốt rắn
    Node* next;
};

class CircularLinkedList {
public:
    Node* head;
    int size;

    CircularLinkedList();
    void push_front(int x, int y);   // thêm đầu (đầu rắn mới)
    void pop_back();                  // xóa đuôi (rắn di chuyển)
    void clear();
    Node* get_tail();                 // lấy đốt cuối
    bool contains(int x, int y);     // kiểm tra rắn tự cắn
    void print_all();                 // debug
};
```

### `snake.h / .cpp`
Dùng `CircularLinkedList` để đại diện con rắn.

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

    void move();                      // di chuyển: push_front + pop_back
    void grow();                      // ăn mồi: push_front, KHÔNG pop_back
    bool is_self_collision();         // tự cắn?
    bool is_out_of_bounds(int w, int h); // ra ngoài?

    Node* get_head();
    CircularLinkedList& get_body();
    int get_length();
};
```

### `food.h / .cpp`
Quản lý mồi ăn.

```cpp
class Food {
public:
    int x, y;

    Food();
    void spawn(int boardW, int boardH, CircularLinkedList& snakeBody);
    // sinh mồi ngẫu nhiên, tránh đè lên thân rắn
};
```

---

## 👤 NGƯỜI 2 — Game Engine & Rendering

### `renderer.h / .cpp`
Vẽ toàn bộ màn hình console.

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

### `input_handler.h / .cpp`
Nhận phím bấm không blocking (dùng `_kbhit` / `getch` trên Windows hoặc termios trên Linux).

```cpp
class InputHandler {
public:
    static Direction get_input(Direction currentDir);
    // W/A/S/D hoặc phím mũi tên
    // trả về direction mới, hoặc giữ nguyên nếu không bấm
};
```

### `game.h / .cpp`
Vòng lặp game chính — kết nối tất cả module.

```cpp
class Game {
private:
    Snake snake;
    Food food;
    Renderer renderer;
    InputHandler input;

    int score;
    int speed;       // delay giữa mỗi frame (ms)
    bool running;

public:
    Game(int boardW, int boardH);
    void run();          // vòng lặp chính

private:
    void update();       // xử lý logic mỗi tick
    void handle_input();
    void check_collisions();
    void increase_difficulty();
};
```

---

## 🔗 `main.cpp` — Viết chung khi ghép

```cpp
#include "game.h"

int main() {
    Game game(20, 20);  // bảng 20x20
    game.run();
    return 0;
}
```

---

## 📋 Phân công chi tiết

| File | Người | Độ khó | Ghi chú |
|------|-------|--------|---------|
| `circular_list.h/cpp` | **Người 1** | ⭐⭐⭐ | Trọng tâm DSA |
| `snake.h/cpp` | **Người 1** | ⭐⭐⭐ | Dùng DSLK vòng |
| `food.h/cpp` | **Người 1** | ⭐ | Đơn giản |
| `renderer.h/cpp` | **Người 2** | ⭐⭐⭐ | Vẽ console |
| `input_handler.h/cpp` | **Người 2** | ⭐⭐ | Xử lý phím |
| `game.h/cpp` | **Người 2** | ⭐⭐⭐ | Vòng lặp chính |
| `main.cpp` | **Cả hai** | ⭐ | Ghép cuối cùng |

---

## ⚙️ Giao diện giữa 2 người (Interface)

Người 2 cần dùng các method sau từ Người 1:

```cpp
// Từ Snake:
snake.move();
snake.grow();
snake.set_direction(dir);
snake.get_head()->x, ->y
snake.get_length()
snake.is_self_collision()
snake.is_out_of_bounds(w, h)
snake.get_body()         // để Renderer vẽ thân rắn

// Từ Food:
food.x, food.y
food.spawn(w, h, snake.get_body())
```

> **Quan trọng:** Người 1 cần hoàn thiện header (`.h`) trước để Người 2 có thể code song song mà không cần chờ implementation xong.

---

## 🚀 Thứ tự làm

```
Tuần 1:
  Người 1: circular_list → snake (draft)
  Người 2: renderer → input_handler (draft)

Tuần 2:
  Người 1: food + hoàn thiện snake
  Người 2: game.cpp + ghép

Tuần 3: Test, fix bug, viết báo cáo
```
