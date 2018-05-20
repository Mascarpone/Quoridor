################################################################
# Makefile variables
################################################################

# Compilation flags
CC=gcc
LDFLAGS=-lncurses
CFLAGS =-std=c99

# List of source files
SRC = $(wildcard ../src/header/*.c)

# List of object files
OBJ= $(SRC:.c=.o)

################################################################
# Makefile rules
################################################################

all: test

readgame.o: readgame.c
	$(CC) -o $@ -c $< $(CFLAGS)

../src/header/%.o: ../src/header/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

test: $(OBJ) readgame.o
	$(CC) -o $@ $^ $(LDFLAGS)


clean:
	rm -rf readgame.o test


