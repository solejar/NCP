#define compiler for C++
CC = g++

#compiler flags can go here
CFLAGS = -std=c++11
TARGET = myprog

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
