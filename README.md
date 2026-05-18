# 🐍 Snake Game - DSA Project

**ProjectDSA** là một dự án đồ án môn học Cấu trúc Dữ liệu & Giải thuật (CTDL&GT). Trò chơi "Rắn săn mồi" kinh điển được lập trình bằng C++ trong môi trường Console, minh họa việc áp dụng cấu trúc dữ liệu **Danh sách liên kết vòng (Circular Linked List)** vào thực tiễn quản lý đối tượng trong game.

---

## 🌟 Tính Năng Nổi Bật

- **Cấu Trúc Dữ Liệu Chuyên Sâu:** Sử dụng *Circular Linked List* để đại diện cho cơ thể của con rắn, tối ưu hóa việc rắn di chuyển và ăn mồi (O(1) cho các thao tác mấu chốt).
- **Kiến Trúc Module Hóa:** Code được phân tách rõ ràng (Logic Rắn, Sinh Mồi, Đồ Họa Console, Xử Lý Input, Quản Lý Điểm Số), dễ dàng bảo trì, mở rộng và làm việc nhóm.
- **Hệ Thống Bảng Xếp Hạng (Leaderboard):** Tích hợp việc đọc/ghi file (`leaderboard.txt`) để lưu trữ và quản lý kỷ lục người chơi một cách bền vững.
- **Input Không Chờ (Non-blocking):** Nhận tương tác phím mượt mà không làm trì hoãn vòng lặp game (sử dụng thư viện hệ thống Windows).
- **Quản Lý Build Chuyên Nghiệp:** Cung cấp `Makefile` chuẩn hóa quy trình biên dịch game, test hiệu năng và unit test.

---

## 🛠 Hướng Dẫn Cài Đặt và Sử Dụng

### Yêu Cầu Hệ Thống
- Trình biên dịch C++ (Hỗ trợ chuẩn C++17 trở lên, ví dụ: GCC/MinGW)
- Make (GNU Make) để chạy tự động quy trình build qua `Makefile`.
- Nền tảng: Hệ điều hành Windows (game hiện sử dụng `_kbhit` và `getch`).

### Cách Biên Dịch & Chạy Game
Bạn có thể sử dụng `Makefile` được cung cấp sẵn để tự động hóa quá trình biên dịch.

1. **Mở Terminal/Command Prompt** và di chuyển tới thư mục gốc của dự án:
   ```bash
   cd du_ong_dan_den_ProjectDSA
   ```

2. **Biên dịch trò chơi:**
   ```bash
   make game
   ```
   *Lệnh này sẽ biên dịch tất cả file source và tạo ra file thực thi `snake_game.exe` trong thư mục `bin/`.*

3. **Chạy trò chơi:**
   ```bash
   .\bin\snake_game.exe
   ```

### Các Lệnh Build Bổ Trợ Khác
- **Biên dịch toàn bộ (Game + Tests + Performance):** `make all`
- **Biên dịch Unit Tests:** `make tests` (sau đó chạy thử nghiệm bằng `.\bin\run_tests.exe`)
- **Dọn dẹp file biên dịch (Object files & Binaries):** `make clean`

---

## 🎮 Cách Chơi

- Sử dụng các phím **W, A, S, D** hoặc **Phím mũi tên** để điều hướng đầu rắn.
- Điều khiển rắn ăn mồi (ký tự đặc biệt trên bản đồ) để ghi điểm và gia tăng chiều dài.
- Trò chơi kết thúc nếu rắn đâm vào tường biên hoặc tự cắn vào chính thân mình.

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
*Đồ án thể hiện việc áp dụng trực tiếp lý thuyết Cấu trúc Dữ liệu vào xây dựng một ứng dụng thời gian thực (Real-time application) có tương tác trọn vẹn.*
