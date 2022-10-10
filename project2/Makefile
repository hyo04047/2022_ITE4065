CC = g++
CXXFLAGS = -g -Wall -std=c++17 -O3 -pthread
SRCS := src/main.cpp
OBJS := $(SRCS:.cpp=.o)
INC = include/
CPPFLAGS += -I$(INC)
TARGET = run
$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -o $(TARGET) $(OBJS)
all: $(TARGET)
clean:
	rm $(TARGET) $(OBJS)