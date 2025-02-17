CUR_DIR := .
EX1_SRC_DIR := $(CUR_DIR)/Exercise1
EX2_SRC_DIR := $(CUR_DIR)/Exercise2
EX3_SRC_DIR := $(CUR_DIR)/Exercise3
EX4_SRC_DIR := $(CUR_DIR)/Exercise4
EX5_SRC_DIR := $(CUR_DIR)/Exercise5
BIN_DIR := $(CUR_DIR)/bin

all: compile_ex1 compile_ex2 compile_ex3 compile_ex4 compile_ex5

compile_ex1: 
	gcc $(EX1_SRC_DIR)/ex1.c -o $(BIN_DIR)/ex1

compile_ex2: 
	gcc $(EX2_SRC_DIR)/ex2.c -o $(BIN_DIR)/ex2

compile_ex3: 
	gcc $(EX3_SRC_DIR)/ex3.c -o $(BIN_DIR)/ex3

compile_ex4: 
	gcc $(EX4_SRC_DIR)/ex4.c -o $(BIN_DIR)/ex4

compile_ex5: 
	gcc $(EX5_SRC_DIR)/ex5.c -o $(BIN_DIR)/ex5


clean:
	rm -rf  $(BIN_DIR)/**
