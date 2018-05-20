#include "../header/interface.h"
#include "../registry.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct board PB; //previous board
struct board* pb = &PB;
unsigned int turn = 0;

struct pos {
    
    char c, l, d;
    
};

struct pos compare(struct board* b, struct board* pb) {
    
    struct pos move;
    
    // check position
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if ((get_position(pb, j, i) == -1)
                && (get_position(b, j, i) == ((get_current_player(b) == 1) ? 0 : 1))) {
                move.c = j;
                move.l = i;
                move.d = -1;
                return move;
            }
        }
    }
    
    
    // check walls
    
    struct pos vert = {.c = 0, .l = 0, .d = 1};
    struct pos hor = {.c = 0, .l = 0, .d = 0};

    // check by placing vertical walls
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (is_blockable(pb, j, i, 1) && (is_blockable(b, j, i, 1) == 0)) {
                vert.c = j;
                vert.l = i;
            }
        }
    }
    // check by placing horizontal walls
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (is_blockable(pb, j, i, 0) && (is_blockable(b, j, i, 0) == 0)) {
                hor.c = j;
                hor.l = i;
            }
        }
    }
    
    // find the move
    
    if ((vert.l == hor.l - 1) && (vert.c = hor.c + 2)) { // horizontal
        move.c = hor.c + 1;
        move.l = hor.l;
        move.d = 0;
        return move;
    } else if ((vert.l == hor.l - 2) && (vert.c == hor.c + 1)) { // vertical
        move.c = vert.c;
        move.l = vert.l + 1;
        move.d = 1;
        return move;
    }
        
    
    
    fprintf(stderr, "Miroir couldn't find where its enemy played\n");
    exit(EXIT_FAILURE);
    
}


// this bot can't play first
void miroir__play(struct board *b) {
    
    // initialize the "previous board" the first time it plays
    if (turn == 0)
        pb = init_board(pb);
    
    struct pos e_move = compare(b, pb);
    printf("Enemy played in %d%d%d\n", e_move.c, e_move.l, e_move.d);
    
    // do the same move your enemy has done
    if (e_move.d == 0) {
        place_wall(b, N - 1 - e_move.c, N - e_move.l, e_move.d);
    } else if (e_move.d == 1) {
        place_wall(b, N - e_move.c, N - 2 - e_move.l, e_move.d);
    } else if (e_move.d == -1) {
        move_pawn(b, N - 1 - e_move.c, N - 1 - e_move.l);
    }
    
    // actualize the "previous board"
    PB = *b;
    
    turn++;
    
}


REGISTER_STRATEGY("Miroir", miroir__play);
