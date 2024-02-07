# specify the compiler
CC=g++

# specify compiler flags
CFLAGS=-std=c++11 -Wall

# specify the target
TARGET=gatorLibrary

all: $(TARGET)

$(TARGET): gatorLibrary.cpp
	$(CC) $(CFLAGS) -o $(TARGET) gatorLibrary.cpp

run: $(TARGET)
    ./$(TARGET) $(FILE)

clean:
    rm $(TARGET)
