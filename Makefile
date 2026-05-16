CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = snake_game

SRCS = main.cpp \
       circular_list.cpp \
       snake.cpp \
       food.cpp \
       renderer.cpp \
       input_handler.cpp \
       game.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
