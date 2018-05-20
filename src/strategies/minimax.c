#include "../header/interface.h"
#include "../registry.h"

#include <stdio.h>
#include <stdlib.h>



struct pos {
    char c, l, d; // c and l in 0..N-1 and d in {-1, 0, 1}.
};



// ----- USE AN OTHER STRUCTURE TO DO TESTS ----- //
// we need to make the enemy pawn move

struct strat_board {
    struct board board;
    struct pos players[2];
    int mark;
};



// Modifies the strat_board to move player p
void move_pawn_strat(struct strat_board *b, char column, char line, int p) {
    
    b->players[p].c = column;
    b->players[p].l = line;
    b->players[p].d = -1;
    
}

// --------------------------------------------- //


// Returns the position of player p in {0, 1}.
struct pos whereisp(struct board *b, int p) {
    
    struct pos position;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (get_position(b, j, i) == p) {
                position.c = j;
                position.l = i;
                position.d = -1;
                return position;
            }
        }
    }
    
    printf("Couldn't find this player !\n");
    exit(EXIT_FAILURE);
    
}



// Writes in a table NxN initialized with zeros all the paths from the position indicated.
int paths(struct strat_board *b, int t[N][N], char column, char line, int n, int p) {
    
    if ((b->players[(p + 1) % 2].c == column) && (b->players[(p + 1) % 2].l == line)) {
        t[line][column] = -1;
        if (is_passable(&b->board, column, line, 0)
            && ((t[line][column - 1] > n) || (t[line][column] == 0))) {
            t[line][column - 1] = n;
        }
        if (is_passable(&b->board, column, line, 1)
            && ((t[line - 1][column] > n) || (t[line][column] == 0))) {
            t[line - 1][column] = n;
        }
        if (is_passable(&b->board, column, line, 2)
            && ((t[line][column + 1] > n) || (t[line][column] == 0))) {
            t[line][column + 1] = n;
        }
        if (is_passable(&b->board, column, line, 3)
            && ((t[line + 1][column] > n) || (t[line][column] == 0))) {
            t[line + 1][column] = n;
        }
    } else if (t[line][column] && (t[line][column] < n)) {
        return 0;
    } else {
        t[line][column] = n;
    }
    
    return (   (is_passable(&b->board, column, line, 0)
                && paths(b, t, column - 1, line, n + 1, p))
            || (is_passable(&b->board, column, line, 1)
                && paths(b, t, column, line - 1, n + 1, p))
            || (is_passable(&b->board, column, line, 2)
                && paths(b, t, column + 1, line, n + 1, p))
            || (is_passable(&b->board, column, line, 3)
                && paths(b, t, column, line + 1, n + 1, p))
            );
    
}



// Returns the length of the shortest path from the position (line, column).
int shortest_path(struct strat_board *b, int p) {
    
    int t[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            t[i][j] = 0;
        }
    }
    
    paths(b, t, b->players[p].c, b->players[p].l, 0, p);
    t[b->players[p].l][b->players[p].c] = -1;
    
    /*
     // TEST //
     for (int i = 0; i < N; i++) {
     for (int j = 0; j < N; j++) {
     printf("%d\t", t[i][j]);
     }
     printf("\n");
     }
     // ---- //
     */
    
    int end_row = (p == 0) ? 0 : (N - 1);
    int min = 81;
    for (int j = 0; j < N; j++) {
        if ((t[end_row][j] > 0) && (t[end_row][j] < min)) {
            min = t[end_row][j];
        }
    }
    
    return min;
    
}



// Returns a mark indicating wether the board is in our favor.
int board_value(struct strat_board *b, int p) {
    
    if (b->players[p].l == ((p == 0) ? 0 : (N - 1))) {
        
        if (p == get_current_player(&b->board)) {
            return 200;
        } else {
            return -200;
        }
        
    } else {
        
        int path_value = shortest_path(b, (p + 1) % 2) - shortest_path(b, p);
        
        if (p == get_current_player(&b->board))
            return path_value;
        else
            return -path_value;
        
    }

    
}



// Writes in the table successors all the board states that can occured after a move on the board b
// and returns the number of these successors.
int find_successors(struct strat_board *b, struct strat_board **successors, int p) {
    
    int n = 0;
    
    // moves
    int t[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            t[i][j] = 0;
        }
    }
    
    paths(b, t, b->players[p].c, b->players[p].l, 0, p);
    t[b->players[p].l][b->players[p].c] = -1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (t[i][j] == 1) {
                (*successors)[n] = *b;
                move_pawn_strat(&(*successors)[n], j, i, p);
                n++;
                *successors = realloc(*successors, sizeof(struct strat_board) * (n + 1));
            }
        }
    }
    

    
    // bridges
    b->mark = board_value(b, p);
    if (((p == get_current_player(&b->board)) && (b->mark < 0))
        || ((p == (get_current_player(&b->board) + 1) % 2) && (b->mark > 0))) {
        
        if (remaining_bridges(&b->board, p) > 0) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    // vertical
                    if (is_blockable(&(b->board), j, i, 1)) {
                        (*successors)[n] = *b;
                        place_wall(&((*successors)[n].board), j, i, 1);
                        (*successors)[n].players[p].c = j;
                        (*successors)[n].players[p].l = i;
                        (*successors)[n].players[p].d = 1;
                        n++;
                        *successors = realloc(*successors, sizeof(struct strat_board) * (n + 1));
                    }
                    //horizontal
                    if (is_blockable(&(b->board), j, i, 0)) {
                        (*successors)[n] = *b;
                        place_wall(&((*successors)[n].board), j, i, 0);
                        (*successors)[n].players[p].c = j;
                        (*successors)[n].players[p].l = i;
                        (*successors)[n].players[p].d = 0;
                        n++;
                        *successors = realloc(*successors, sizeof(struct strat_board) * (n + 1));
                    }
                }
            }
        }
        
    }
    
    return n;
    
}



// Returns and integer indicating the best mark you can get with a specific board state
// by testing the next n turns.
// This AI maximize and its enemy minimize.
struct strat_board minimaxAB(struct strat_board *b, int p, int alpha, int beta, int n) {
    
    if (n == 0) {
        
        b->mark = board_value(b, p);
        return *b;
        
    } else {
        
        // find all the possible moves from this state of the board.
        struct strat_board *successors = malloc(sizeof(struct strat_board));
        int successors_nb = find_successors(b, &successors, p);
        
        // printf("Successors number : %d\n", successors_nb);
        
        if (p == get_current_player(&b->board)) {
            
            int max = alpha;
            int best_board_id = 0;
            struct strat_board tested_board;
            int end = 0;
            int i = 0;
            int v;
            
            while ((i < successors_nb) && (end == 0)) {
                tested_board = minimaxAB(&successors[i], (p + 1) % 2, max, beta, n - 1);
                v = tested_board.mark;
                if (v > max) {
                    max = v;
                    best_board_id = i;
                }
                if (max >= beta) {
                    end = 1;
                }
                i++;
            }
            
            tested_board = successors[best_board_id];
            free(successors);
            return tested_board;
            
        } else {
            
            int min = beta;
            int best_board_id = 0;
            struct strat_board tested_board;
            int end = 0;
            int i = 0;
            int v;
            
            while ((i < successors_nb) && (end == 0)) {
                tested_board = minimaxAB(&successors[i], (p + 1) % 2, alpha, min, n - 1);
                v = tested_board.mark;
                if (v < min) {
                    min = v;
                    best_board_id = i;
                }
                if (min <= alpha) {
                    end = 1;
                }
                i++;
            }
            
            tested_board = successors[best_board_id];
            free(successors);
            return tested_board;
            
        }
        
    }
    
}



void minimax__play(struct board *b) {
    
    struct strat_board sb;
    sb.board = *b;
    sb.players[get_current_player(b)] = whereisp(b, get_current_player(b));
    sb.players[(get_current_player(b) + 1) % 2] = whereisp(b, (get_current_player(b) + 1) % 2);
    
    struct strat_board best_board = minimaxAB(&sb, get_current_player(b), -200, 200, 1);
    struct pos my_pos = best_board.players[get_current_player(b)];
    
    if (my_pos.d == -1) {
        move_pawn(b, my_pos.c, my_pos.l);
    } else {
        place_wall(b, my_pos.c, my_pos.l, my_pos.d);
    }
    
}


REGISTER_STRATEGY("Minimax", minimax__play);
