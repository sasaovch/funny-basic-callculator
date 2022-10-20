CC        = clang
CFLAGS    = -Wall -g

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
	rm -r $(TARGET) $(OBJ_DIR)
