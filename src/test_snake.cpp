#include "snake.h"
#include "food.h"
#include <iostream>
#include <cassert>

// 1. Test khởi tạo
void test_initialization() {
    Snake snake(10, 10, 3); // x=10, y=10, len=3
    assert(snake.get_length() == 3);
    
    Node* head = snake.get_head();
    assert(head != nullptr);
    assert(head->x == 10 && head->y == 10);
    
    std::cout << "1. test_initialization: PASS\n";
}

// 2. Test di chuyển cơ bản
void test_basic_movement() {
    Snake snake(10, 10, 3);
    
    snake.set_direction(UP);
    snake.move();
    assert(snake.get_head()->x == 10 && snake.get_head()->y == 9); // y giảm 1
    
    snake.set_direction(LEFT);
    snake.move();
    assert(snake.get_head()->x == 9 && snake.get_head()->y == 9);  // x giảm 1

    assert(snake.get_length() == 3); // Độ dài giữ nguyên
    
    std::cout << "2. test_basic_movement: PASS\n";
}

// 3. Test không cho phép quay ngược 180 độ (Test biên - boundary test)
void test_invalid_turn() {
    Snake snake(10, 10, 3);
    
    snake.set_direction(UP);
    assert(snake.get_direction() == UP);
    
    // Đang đi UP, cố tình đổi thành DOWN -> hướng phải giữ nguyên là UP
    snake.set_direction(DOWN);
    assert(snake.get_direction() == UP);
    
    // Đổi sang RIGHT (Hợp lệ)
    snake.set_direction(RIGHT);
    assert(snake.get_direction() == RIGHT);
    
    // Đang đi RIGHT, cố tình đổi thành LEFT -> hướng giữ nguyên là RIGHT
    snake.set_direction(LEFT);
    assert(snake.get_direction() == RIGHT);
    
    // Test cụm phím nhanh: đang đi UP, bấm ngay lập tức DOWN (không đâm vào cổ)
    Snake snake2(10, 10, 3);
    snake2.set_direction(UP); // bắt đầu đi UP
    snake2.move();
    assert(snake2.get_head()->x == 10 && snake2.get_head()->y == 9);
    
    // Bấm ngay sang DOWN
    snake2.set_direction(DOWN);
    assert(snake2.get_direction() == UP); // Không cho phép quay ngược 180
    snake2.move();
    assert(snake2.get_head()->x == 10 && snake2.get_head()->y == 8); // Tiếp tục đi lên, không đâm cổ

    std::cout << "3. test_invalid_turn & boundary: PASS\n";
}

// 4. Test chức năng dài ra khi ăn mồi
void test_grow() {
    Snake snake(10, 10, 3);
    snake.set_direction(UP);
    
    snake.grow(); // Coi như ăn mồi

    assert(snake.get_head()->x == 10 && snake.get_head()->y == 9);
    assert(snake.get_length() == 4); // Độ dài tăng thêm 1
    
    std::cout << "4. test_grow: PASS\n";
}

// 5. Test va chạm (Tường và tự thân)
void test_collisions() {
    // Tường trái
    Snake snake(1, 1, 3);
    snake.set_direction(UP);
    snake.set_direction(LEFT);
    snake.move(); // x = 0
    snake.move(); // x = -1 -> Đâm tường trái
    assert(snake.is_out_of_bounds(20, 20) == true);
    
    // Tường phải
    Snake snakeRight(18, 1, 3);
    snakeRight.set_direction(RIGHT);
    snakeRight.move(); // x = 19
    snakeRight.move(); // x = 20 -> Đâm tường phải
    assert(snakeRight.is_out_of_bounds(20, 20) == true);

    // Tường trên
    Snake snakeUp(1, 1, 3);
    snakeUp.set_direction(UP);
    snakeUp.move(); // y = 0
    snakeUp.move(); // y = -1 -> Đâm tường trên
    assert(snakeUp.is_out_of_bounds(20, 20) == true);

    // Tường dưới
    Snake snakeDown(1, 18, 3);
    snakeDown.set_direction(DOWN);
    snakeDown.move(); // y = 19
    snakeDown.move(); // y = 20 -> Đâm tường dưới
    assert(snakeDown.is_out_of_bounds(20, 20) == true);

    // Tự cắn thân: Khởi tạo rắn dài 5 để cuộn tròn
    Snake long_snake(10, 10, 5);
    long_snake.set_direction(UP);    long_snake.move(); // (10, 9)
    long_snake.set_direction(RIGHT); long_snake.move(); // (11, 9)
    long_snake.set_direction(DOWN);  long_snake.move(); // (11, 10)
    long_snake.set_direction(LEFT);  long_snake.move(); // (10, 10) -> Cắn vào chính thân gốc
    
    assert(long_snake.is_self_collision() == true);
    
    std::cout << "5. test_collisions (all boundaries): PASS\n";
}

// 6. Test thức ăn (mồi)
void test_food() {
    Snake snake(10, 10, 3);
    Food food;
    food.spawn(20, 20, snake.get_body());
    
    // Kiểm tra mồi nằm trong bản đồ
    assert(food.x >= 0 && food.x < 20);
    assert(food.y >= 0 && food.y < 20);
    
    // Đảm bảo không trùng với thân rắn
    assert(snake.get_body().contains(food.x, food.y) == false);

    std::cout << "6. test_food: PASS\n";
}

int main() {
    std::cout << "--- BAT DAU CHAY TEST --- \n";
    test_initialization();
    test_basic_movement();
    test_invalid_turn();
    test_grow();
    test_collisions();
    test_food();
    std::cout << "--- TAT CA TEST DEU PASS! ---\n";
    return 0;
}