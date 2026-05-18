CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = bin/snake_game

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

# Create corresponding object file names
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(OBJ_DIR)\*.o
	del /Q $(BIN_DIR)\snake_game.exe

.PHONY: all clean
