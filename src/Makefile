################################################################
# Makefile variables
################################################################

# Compilation flags
CC=gcc
LDFLAGS=-lncurses
CFLAGS =-std=c99

# List of source files
SRC = \
	server.c \
	$(wildcard header/*.c) \
	$(wildcard strategies/*.c) \

# List of object files
OBJ = $(patsubst %.c, %.o, $(SRC))

# Command for stripping symbols
ifeq  ($(shell uname -s), Darwin)
	OBJCOPY = $(LD) -r -unexported_symbol '*' -o
else
	OBJCOPY = objcopy --strip-unneeded
endif

################################################################
# Makefile rules
################################################################

all: server

server.o: server.c
	$(CC) -c $< $(CFLAGS) -DEXTERN_STRAT= -o $@

strategies/%.o: strategies/%.c
	$(CC) -c $< -I . $(CFLAGS) -o $@
	$(OBJCOPY) $@ $@

header/%.o: header/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

server: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)



clean:
	@rm -f $(OBJ) server
	rm -rf readgame.o readgame


