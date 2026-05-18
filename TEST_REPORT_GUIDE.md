# Hướng dẫn chạy Test và Viết Báo Cáo (Report)

Tài liệu này hướng dẫn cách biên dịch, chạy các bài kiểm thử (Unit Test, Boundary Test, Performance Test) và tổng hợp các thông tin cần thiết để đưa vào báo cáo bài tập lớn.

---

## 1. Hướng Dẫn Chạy Test Logic & Test Biên (Unit Test & Boundary Test)

Bài test này kiểm tra toàn bộ logic cốt lõi của Game (rắn di chuyển, va chạm, ăn mồi) mà không cần mở giao diện đồ họa.

**Cách biên dịch và chạy:**
Mở terminal (PowerShell hoặc CMD) tại thư mục `ProjectDSA` và chạy lệnh:
```bash
g++ -std=c++17 circular_list.cpp snake.cpp food.cpp test_snake.cpp -o run_tests.exe
.\run_tests.exe
```

**Các Test Case được thực thi:**
1. `test_initialization`: Kiểm tra rắn khởi tạo đúng tọa độ và độ dài.
2. `test_basic_movement`: Rắn đi đúng hướng (trái/phải/lên/xuống).
3. `test_invalid_turn`: (Boundary Test) Kiểm tra việc ngăn rắn quay ngoắt 180 độ (ví dụ đang đi LÊN mà bấm XUỐNG) và xử lý lỗi cụm phím nhanh.
4. `test_grow`: Rắn tăng độ dài chính xác sau khi ăn mồi.
5. `test_collisions`: (Quan trọng nhất) Kiểm tra rắn đâm vào 4 bức tường và tự cắn vào thân (khi độ dài >= 5).
6. `test_food`: Thức ăn sinh ra ngẫu nhiên nhưng phải nằm trong màn hình và tuyệt đối **không** đè lên thân rắn.

---

## 2. Hướng Dẫn Chạy Performance Test (Đo thời gian 10.000 dữ liệu)

Bài test này giả lập 10.000 lượt chơi (Mock Data) để kiểm tra tốc độ xử lý của mảng/danh sách khi thực hiện các tác vụ File I/O, Tìm kiếm và Sắp xếp.

**Cách biên dịch và chạy:**
```bash
g++ -std=c++17 performance_test.cpp -o run_perf.exe
.\run_perf.exe
```

**Các bước đo lường trong test:**
- Sinh 10.000 bản ghi ngẫu nhiên trên RAM.
- Lưu 10.000 bản ghi xuống file CSV (`test_leaderboard.csv`).
- Đọc 10.000 bản ghi từ file CSV lên lại bộ nhớ.
- Tìm kiếm một người chơi cụ thể (Ví dụ: `Player9999`).
- Sắp xếp toàn bộ dữ liệu để lấy ra Top 10 Highscore.

---

## 3. Hướng Dẫn Chạy Game Chính (Manual Test Save/Load)

Để tự mình chơi thử và xác nhận luồng lưu điểm số cuối game hoạt động trơn tru:

**Cách biên dịch và chạy:**
```bash
make
.\snake_game.exe
```

**Kịch bản test bằng tay:**
- Chơi game và cố tình đâm vào tường để Game Over.
- Hệ thống sẽ yêu cầu: `Enter your name for the leaderboard:`
- Nhập tên của bạn (Ví dụ: `NguyenVanA`).
- Game sẽ tự động lưu vào file và in ra bảng `--- TOP HIGHSCORES ---` ngay lập tức.

---

## 4. Các Nội Dung Bắt Buộc Cần Đưa Vào Báo Cáo (Report)

Để đạt điểm tối đa, phần báo cáo của bạn cần có các mục sau (Kèm theo ảnh chụp màn hình terminal để làm bằng chứng):

### A. Kết quả kiểm thử Logic & Biên (Boundary Test)
- Trình bày rằng nhóm đã sử dụng phương pháp Unit Test tự động (sử dụng `assert` trong C++) thay vì chỉ test bằng tay.
- Liệt kê các test case quan trọng, đặc biệt nhấn mạnh vào **Lỗi xử lý hệ thống phím bấm**: "Nếu người chơi bấm 2 phím điều hướng quá nhanh, rắn có đâm vào cổ không?". Kèm ảnh chụp màn hình terminal khi tất cả các test báo `PASS`.
- Đề cập đến việc xử lý va chạm chính xác tại các tọa độ mép màn hình.

### B. Kết luận Performance Test (Xử lý 10.000 dữ liệu)
Đây là phần cốt lõi của cấu trúc dữ liệu và giải thuật. 
- **Môi trường Test**: Nêu rõ ngôn ngữ sử dụng là C++ và thư viện đo thời gian là `std::chrono::high_resolution_clock`.
- **Cấu trúc dữ liệu**: Lưu trữ bảng xếp hạng bằng `std::vector` và thuật toán sắp xếp (sử dụng `std::sort` - thuật toán IntroSort với độ phức tạp $O(N \log N)$).
- **Kết quả đo lường thực tế (Ví dụ tham khảo từ máy của bạn)**:
  - Sinh 10.000 mock data: ~ **3 ms**
  - Ghi toàn bộ dữ liệu ra File (Save): ~ **1 ms**
  - Đọc dữ liệu từ File vào RAM (Load): ~ **16 ms**
  - Thời gian tìm kiếm 1 người chơi (`Player9999`): ~ **258 Micro-seconds (µs)** (Tốc độ cực kỳ nhanh).
  - Thời gian Sắp xếp (Sort) lấy Top 10: ~ **8 ms**
- **Nhận xét kết luận**: Cấu trúc dữ liệu và thuật toán hiện tại hoàn toàn đáp ứng tốt cho bài toán có số lượng dữ liệu lớn. Tốc độ tìm kiếm và cập nhật điểm số xảy ra gần như tức thời (tính bằng micro-giây và mili-giây), không gây giật lag cho người chơi.

*(Lưu ý: Bạn hãy tự chạy lệnh `.\run_perf.exe` và chụp lại chính xác thời gian hiển thị trên màn hình máy tính của bạn để dán vào file Word báo cáo).*