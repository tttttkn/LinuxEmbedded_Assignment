CC = gcc
CFLAGS = -Wall
SRC_DIR = src
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
TARGET = $(BIN_DIR)/chat_app

all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BIN_DIR) valgrind-out.txt

memcheck: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(TARGET) 5000

.PHONY: all clean memcheck