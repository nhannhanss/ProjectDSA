CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = bin/snake_game
TEST_TARGET = bin/run_tests
PERF_TARGET = bin/run_perf

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/circular_list.cpp \
       $(SRC_DIR)/snake.cpp \
       $(SRC_DIR)/food.cpp \
       $(SRC_DIR)/renderer.cpp \
       $(SRC_DIR)/input_handler.cpp \
       $(SRC_DIR)/game.cpp

TEST_SRCS = $(SRC_DIR)/test_snake.cpp \
            $(SRC_DIR)/circular_list.cpp \
            $(SRC_DIR)/snake.cpp \
            $(SRC_DIR)/food.cpp

PERF_SRCS = $(SRC_DIR)/performance_test.cpp \
            $(SRC_DIR)/circular_list.cpp

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
TEST_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRCS))
PERF_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(PERF_SRCS))

all: $(TARGET) $(TEST_TARGET) $(PERF_TARGET)

game: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(PERF_TARGET): $(PERF_OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(BIN_DIR)/*.exe

.PHONY: all clean game tests perf

tests: $(TEST_TARGET)

perf: $(PERF_TARGET)

.PHONY: all clean
