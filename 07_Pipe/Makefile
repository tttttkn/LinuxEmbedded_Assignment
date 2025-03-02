CUR_DIR := .
EX1_SRC_DIR := $(CUR_DIR)/Exercise1
EX2_SRC_DIR := $(CUR_DIR)/Exercise2
EX3_SRC_DIR := $(CUR_DIR)/Exercise3
BIN_DIR := $(CUR_DIR)/bin

all: compile_ex1 compile_ex2 compile_ex3 compile_ex4 compile_ex5

create_bin_dir:
	mkdir -p -v $(BIN_DIR)

compile_ex1: create_bin_dir
	gcc $(EX1_SRC_DIR)/ex1.c -o $(BIN_DIR)/ex1

compile_ex2: create_bin_dir
	gcc $(EX2_SRC_DIR)/ex2.c -o $(BIN_DIR)/ex2

compile_ex3: create_bin_dir
	gcc $(EX3_SRC_DIR)/ex3.c -o $(BIN_DIR)/ex3


clean:
	rm -rf  $(BIN_DIR)
