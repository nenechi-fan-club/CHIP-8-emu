CC = g++
CFLAGS = -g

SRC_DIR = src
BUILD_DIR = build

TARGET = bin/chip8.exe

$(TARGET): $(BUILD_DIR)/chip8.o $(BUILD_DIR)/main.o
	@echo "Linking..."
	$(CC) $^ -o $@

$(BUILD_DIR)/chip8.o: $(SRC_DIR)/chip8.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

$(BUILD_DIR)/main.o: main.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
