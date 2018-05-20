#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define N 9 // size of the board


//--------------------- STRUCTS ----------------------//

struct player {
    
  // remaining bridges
  unsigned int bar_nb;
    
  // position //
  char column; // numbers 0 to N-1
  char line; // numbers 0 to N-1
    
};

struct move {

  // indicates the movement asked by the player
  // c in 0 .. N-1
  // l in 0 .. N-1
  // d in {-1 (not a wall movement), 0 (horizontal), 1 (vertical)}
  char c, l, d;

};

struct board {
  
  // The board is a table with 2 dimensions.
  // Barriers spots are written in it {0, 1}
  int t[2 * N - 1][2 * N - 1]; // t[line][column]

  struct player A;
  struct player B;
  char current_player; // 'A' or 'B'

};

//----------------------------------------------------//



//-------------------- REAL BOARD --------------------//

struct board BOARD;

//----------------------------------------------------//



//-------------------- FUNCTIONS ---------------------//

// header.c

// Takes a coordinate between 0 and N-1 and returns a coordinate for our table t[2 * N - 1][2 * N - 1].
char toBoardcoor(char x);

// Initializes the board. The argument should be a valid address for a
// struct board.
struct board* init_board(struct board* b);

// Returns the ID of current player : 0 (player A) or 1 (player B).
unsigned int get_current_player(const struct board * b);

// Returns an integer indicating whether a player has won
// -1 (player A), 1 (player B), 0 (none).
int win(const struct board* b);



// move.c

// Returns an integer describing what is at position (column,line)
// on the board b. The result is either -1 (empty), 0 (player A) or 1 (player B).
int get_position(const struct board* b, char column, char line);

// Returns an integer indicating whether there is a wall on the board b (1 if you can pass or else 0)
// at position starting from (column,line), in a direction that is either 
// towards smaller cols (0), smaller lines (1), larger cols (2) or larger lines (3).
int is_passable(const struct board* b, char column, char line, char direction);

// Moves a pawn on the position (column, line)
// Columns and lines are numbered from 0 to N-1.
void move_pawn(struct board* b, char column, char line);



// wall.c

// Returns the number of available bridges for the player 0 (player A) or 1 (player B).
unsigned int remaining_bridges(const struct board* b, unsigned int player);

// Returns an integer indicating if each player has still a path to win.
int may_end(const struct board* b, int t[N][N], char col, char row, char end_row);

// Returns an integer indicating whether it is possible to place a wall
// on the corresponding column, line and direction.
// Directions are either 0 (horizontal) or 1 (vertical).
int is_blockable(struct board* b, char column, char line, char direction);

// Places a wall on the corresponding column, line and direction
// Directions are either 0 (horizontal) or 1 (vertical).
void place_wall(struct board* b, char column, char line, char direction);



// graphic.c

void print_board(const struct board* b);



// parser.c

void parser(struct move move[2], FILE* file, int num_line);

void write_in_file(struct move move, FILE* write_file, int p);

//----------------------------------------------------//
