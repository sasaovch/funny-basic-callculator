CC        = gcc
CFLAGS    = -Wall -g
#include libm.a
INC_LIB   = -lm

TARGET    = calc

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRC_FILES = $(wildcard $(SRC_DIR)*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_FILES))

all : $(TARGET)

$(TARGET) : $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(TARGET) $(INC_LIB)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

clean :
	rm $(TARGET) $(OBJ_FILES)
