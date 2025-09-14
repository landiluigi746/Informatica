TARGET = Biblioteca

CC := g++
CFLAGS := -I. -std=c++11 -o$(TARGET)
SRCS := ./*.cpp

.PHONY: all

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS)
