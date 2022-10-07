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

$(TARGET) : $(OBJ_FILES) FLEX BISON
	$(CC) $(OBJ_FILES) -o $(TARGET) $(INC_LIB) $(OBJ_DIR)bison.tab.c $(OBJ_DIR)lex.yy.c

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

FLEX :
	flex -o $(OBJ_DIR)lex.yy.c $(SRC_DIR)lex.lex

BISON :
	bison -t -o $(OBJ_DIR)bison.tab.c --header=$(OBJ_DIR)bison.tab.h $(SRC_DIR)bison.y

clean :
	rm -r $(TARGET) $(OBJ_DIR)
