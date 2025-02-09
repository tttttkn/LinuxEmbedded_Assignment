CUR_DIR := .
EX1_SRC_DIR := $(CUR_DIR)/Exercise1
EX3_SRC_DIR := $(CUR_DIR)/Exercise3
EX4_SRC_DIR := $(CUR_DIR)/Exercise4
BIN_DIR := $(CUR_DIR)/bin

all: compile_ex1 compile_ex3 compile_ex4

compile_ex1: 
	gcc $(EX1_SRC_DIR)/ex1.c -o $(BIN_DIR)/ex1

compile_ex3: 
	gcc $(EX3_SRC_DIR)/ex3.c -o $(BIN_DIR)/ex3

compile_ex4: 
	gcc $(EX4_SRC_DIR)/ex4.c -o $(BIN_DIR)/ex4


clean:
	rm -rf  $(BIN_DIR)/**
