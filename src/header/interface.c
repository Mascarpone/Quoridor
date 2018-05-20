#include "interface.h"



//--------------------- BOARD ---------------------//

// Takes a coordinate between 0 and 8 and returns a coordinate for our table t 17x17.
char toBoardcoor(char x) {
    
    return 2 * x;
    
}


// Initializes the board. The argument should be a valid address for a
// struct board.
struct board* init_board(struct board* b) {
    
    for (int i = 0; i < 2 * N - 1; i++) {
        for (int j = 0; j < 2 * N - 1; j++) {
            b->t[i][j] = 0;
        }
    }
    
    b->A.bar_nb = 10;
    b->B.bar_nb = 10;
    
    b->A.column = N / 2;
    b->A.line = N - 1;
    b->B.column = N / 2;
    b->B.line = 0;
    
    b->current_player = 'A';
    
    return b;
    
}



// Returns the ID of current player : 0 (player A) or 1 (player B).
unsigned int get_current_player(const struct board* b) {

  switch (b->current_player) {
  case 'A':
    return 0;
    break;
  case 'B':
    return 1;
    break;
  default:
    return 42;
    break;
  }

}
 

// graphic.c

// parser.c

//----------------------------------------------------//




//--------------------- BARRIER -----------------------//

// wall.c

//----------------------------------------------------//




//----------------------- MOVE -----------------------//

// move.c

//----------------------------------------------------//




//----------------------- WIN ------------------------//

int win(const struct board* b) {
    
  // player A begins on line N-1 and wins on line 0
  // player B begins on line 0 and wins on line N-1

  if (b->A.line == 0) {
    return -1;
  } else if (b->B.line == N - 1) {
    return 1;
  }

  return 0;

}

//----------------------------------------------------//
