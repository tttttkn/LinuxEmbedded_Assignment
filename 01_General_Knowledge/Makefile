CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/obj
INC_DIR := $(CUR_DIR)/inc
SHARED_LIB_DIR := $(CUR_DIR)/lib/shared
STATIC_LIB_DIR := $(CUR_DIR)/lib/static

CFLAG := -I$(INC_DIR)

all: static_linking dynamic_linking

create_obj:
	gcc -c $(SRC_DIR)/hello.c -o $(OBJ_DIR)/hello_static.o $(CFLAG)
	gcc -c -fPIC $(SRC_DIR)/hello.c -o $(OBJ_DIR)/hello_shared.o $(CFLAG)
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o $(CFLAG)

create_static_lib: create_obj
	ar rcs $(STATIC_LIB_DIR)/libhello_static.a $(OBJ_DIR)/hello_static.o

create_shared_lib: create_obj
	gcc -shared $(OBJ_DIR)/hello_shared.o -o $(SHARED_LIB_DIR)/libhello_shared.so

static_linking: create_static_lib create_obj
	gcc   $(OBJ_DIR)/main.o  -L$(STATIC_LIB_DIR) -lhello_static -o $(BIN_DIR)/use-static-lib

dynamic_linking: create_shared_lib create_obj
	gcc   $(OBJ_DIR)/main.o  -L$(SHARED_LIB_DIR) -lhello_shared -o $(BIN_DIR)/use-shared-lib
	
clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(SHARED_LIB_DIR)/*.so
	rm -rf $(STATIC_LIB_DIR)/*.a
	rm -rf $(BIN_DIR)/*
