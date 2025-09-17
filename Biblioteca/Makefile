TARGET = Biblioteca

CC := g++
CFLAGS := -I. -std=c++11 -o$(TARGET) -Wall -Wextra
SRCS := ./*.cpp
HEADERS := ./*.hpp

.PHONY: all

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(SRCS) $(CFLAGS)
