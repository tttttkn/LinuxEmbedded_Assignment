CUR_DIR := .
EX1_SRC_DIR := $(CUR_DIR)/Exercise1
EX3_SRC_DIR := $(CUR_DIR)/Exercise3
EX4_SRC_DIR := $(CUR_DIR)/Exercise4
BIN_DIR := $(CUR_DIR)/bin

all: create_bin_dir compile_ex1 compile_ex3 compile_ex4

create_bin_dir:
	mkdir -p -v $(BIN_DIR)

compile_ex1: create_bin_dir
	gcc $(EX1_SRC_DIR)/ex1.c -o $(BIN_DIR)/ex1

compile_ex3: create_bin_dir
	gcc $(EX3_SRC_DIR)/ex3.c -o $(BIN_DIR)/ex3

compile_ex4: create_bin_dir
	gcc $(EX4_SRC_DIR)/ex4.c -o $(BIN_DIR)/ex4

clean:
	rm -rf $(BIN_DIR)