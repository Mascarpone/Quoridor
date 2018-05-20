#include "../header/interface.h"
#include "../registry.h"

#include <stdio.h>
#include <stdlib.h>



struct pos {
    char c, l, d; // c and l in 0..N-1 and d in {-1, 0, 1}.
};



// ----- USE ANOTHER STRUCTURE TO DO TESTS ----- //
// we need to make the enemy pawn move

struct strat_board {
    struct board board;
    int t[2 * N - 1][2 * N - 1];
    struct pos players[2];
    int current_player;
};

int get_position_strat(struct strat_board* b, char col, char row) {
    
    if ((b->players[0].c == col) && (b->players[0].l == row)) {
        return 0;
    } else if ((b->players[1].c == col) && (b->players[1].l == row)) {
        return 1;
    } else {
        return -1;
    }
    
}

int is_passable_strat(struct strat_board* b, char column, char line, char direction) {
    
    
    int res = 1;
    int l = 2 * line;
    int c = 2 * column;
    
    
    switch (direction)
    {
        case 0:
            
            if (c == 0)
                res = 0;
            else if (b->t[l][c - 1])
                res = 0;
            
            break;
            
        case 1:
            
            if (l == 0)
                res = 0;
            else if (b->t[l - 1][c])
                res = 0;
            
            break;
            
        case 2:
            
            if (c == 16)
                res = 0;
            else if (b->t[l][c + 1])
                res = 0;
            
            break;
            
        case 3:
            
            if (l == 16)
                res = 0;
            else if (b->t[l + 1][c])
                res = 0;
            
            break;
            
        default:
            
            fprintf(stderr, "Unknown direction in is_passable_strat()\n");
            return 0;
            break;
    }
    
    
    return res;
    
}

int is_movement_allowed(struct strat_board* b, char column, char line) {
    
    struct pos p_pos = b->players[b->current_player];
    
    // check if this is a movement concerning the jump of the enemy pawn
    
    int jump = 0;
    
    // diagonals if there is a wall dehind the enemy
    if ((p_pos.c - column == 1) && (p_pos.l - line == 1)) //up left
    {
        fprintf(stderr, "up left\n");
        if ((get_position_strat(b, p_pos.c - 1, p_pos.l) != -1)
            && is_passable_strat(b, p_pos.c, p_pos.l, 0)
            && is_passable_strat(b, p_pos.c - 1, p_pos.l, 1)
            && (is_passable_strat(b,p_pos.c - 1, p_pos.l, 0) == 0)
            
            && (get_position(&b->board, p_pos.c - 1, p_pos.l) != -1)
            && is_passable(&b->board, p_pos.c, p_pos.l, 0)
            && is_passable(&b->board, p_pos.c - 1, p_pos.l, 1)
            && (is_passable(&b->board,p_pos.c - 1, p_pos.l, 0) == 0)) //left
        {
            jump = 1;
        }
        else if ((get_position_strat(b, p_pos.c, p_pos.l - 1) != -1)
                 && is_passable_strat(b, p_pos.c, p_pos.l, 1)
                 && is_passable_strat(b, p_pos.c, p_pos.l-1, 0)
                 && (is_passable_strat(b, p_pos.c, p_pos.l-1, 1) == 0)
                 
                 && (get_position(&b->board, p_pos.c, p_pos.l - 1) != -1)
                 && is_passable(&b->board, p_pos.c, p_pos.l, 1)
                 && is_passable(&b->board, p_pos.c, p_pos.l-1, 0)
                 && (is_passable(&b->board, p_pos.c, p_pos.l-1, 1) == 0)) // up
        {
            jump = 1;
        }
    }
    
    else if ((column - p_pos.c == 1) && (p_pos.l - line == 1)) // up right
    {
        if ((get_position_strat(b, p_pos.c, p_pos.l - 1) != -1)
            && is_passable_strat(b,p_pos.c, p_pos.l, 1)
            && is_passable_strat(b, p_pos.c, p_pos.l - 1, 2)
            && (is_passable_strat(b, p_pos.c, p_pos.l - 1, 1) == 0)
            
            && (get_position(&b->board, p_pos.c, p_pos.l - 1) != -1)
            && is_passable(&b->board,p_pos.c, p_pos.l, 1)
            && is_passable(&b->board, p_pos.c, p_pos.l - 1, 2)
            && (is_passable(&b->board, p_pos.c, p_pos.l - 1, 1) == 0)) // up
        {
            jump = 1;
        }
        else if ((get_position_strat(b, p_pos.c + 1, p_pos.l) != -1)
                 && is_passable_strat(b,p_pos.c, p_pos.l, 2)
                 && is_passable_strat(b, p_pos.c + 1, p_pos.l, 1)
                 && (is_passable_strat(b, p_pos.c + 1, p_pos.l, 2) == 0)
                 
                 && (get_position(&b->board, p_pos.c + 1, p_pos.l) != -1)
                 && is_passable(&b->board,p_pos.c, p_pos.l, 2)
                 && is_passable(&b->board, p_pos.c + 1, p_pos.l, 1)
                 && (is_passable(&b->board, p_pos.c + 1, p_pos.l, 2) == 0)) // right
        {
            jump = 1;
        }
    }
    
    else if ((column - p_pos.c == 1) && (line - p_pos.l == 1)) // bellow right
    {
        if ((get_position_strat(b, p_pos.c + 1, p_pos.l) != -1)
            && is_passable_strat(b, p_pos.c, p_pos.l, 2)
            && is_passable_strat(b, p_pos.c + 1, p_pos.l, 3)
            && (is_passable_strat(b, p_pos.c + 1, p_pos.l, 2) == 0)
            
            && (get_position(&b->board, p_pos.c + 1, p_pos.l) != -1)
            && is_passable(&b->board, p_pos.c, p_pos.l, 2)
            && is_passable(&b->board, p_pos.c + 1, p_pos.l, 3)
            && (is_passable(&b->board, p_pos.c + 1, p_pos.l, 2) == 0)) // right
        {
            jump = 1;
        }
        else if ((get_position_strat(b, p_pos.c, p_pos.l + 1) != -1)
                 && is_passable_strat(b, p_pos.c, p_pos.l, 3)
                 && is_passable_strat(b, p_pos.c, p_pos.l + 1, 2)
                 && (is_passable_strat(b, p_pos.c, p_pos.l + 1, 3) == 0)
                 
                 && (get_position(&b->board, p_pos.c, p_pos.l + 1) != -1)
                 && is_passable(&b->board, p_pos.c, p_pos.l, 3)
                 && is_passable(&b->board, p_pos.c, p_pos.l + 1, 2)
                 && (is_passable(&b->board, p_pos.c, p_pos.l + 1, 3) == 0))  // bellow ok
        {
            jump = 1;
        }
    }
    
    else if ((column - p_pos.c == 1) && (line - p_pos.l == 1)) // bellow left
    {
        if ((get_position_strat(b, p_pos.c, p_pos.l + 1) != -1)
            && is_passable_strat(b, p_pos.c, p_pos.l, 3)
            && is_passable_strat(b, p_pos.c, p_pos.l + 1, 0)
            && (is_passable_strat(b, p_pos.c, p_pos.l + 1, 3) == 0)
            
            && (get_position(&b->board, p_pos.c, p_pos.l + 1) != -1)
            && is_passable(&b->board, p_pos.c, p_pos.l, 3)
            && is_passable(&b->board, p_pos.c, p_pos.l + 1, 0)
            && (is_passable(&b->board, p_pos.c, p_pos.l + 1, 3) == 0)) // bellow
        {
            jump = 1;
        }
        else if ((get_position_strat(b, p_pos.c - 1, p_pos.l) != -1)
                 && is_passable_strat(b, p_pos.c, p_pos.l, 0)
                 && is_passable_strat(b, p_pos.c - 1, p_pos.l, 3)
                 && (is_passable_strat(b, p_pos.c - 1, p_pos.l, 0) == 0)
                 
                 && (get_position(&b->board, p_pos.c - 1, p_pos.l) != -1)
                 && is_passable(&b->board, p_pos.c, p_pos.l, 0)
                 && is_passable(&b->board, p_pos.c - 1, p_pos.l, 3)
                 && (is_passable(&b->board, p_pos.c - 1, p_pos.l, 0) == 0)) // left
        {
            jump = 1;
        }
    }
    
    // jump forward
    if ((p_pos.c - column == 2)
        && (p_pos.l == line)
        && is_passable_strat(b, p_pos.c, p_pos.l, 0)
        && is_passable_strat(b, p_pos.c - 1, p_pos.l, 0)
        && (get_position_strat(b, p_pos.c - 1, p_pos.l) != -1)
        
        && is_passable(&b->board, p_pos.c, p_pos.l, 0)
        && is_passable(&b->board, p_pos.c - 1, p_pos.l, 0)
        && (get_position(&b->board, p_pos.c - 1, p_pos.l) != -1))
    {
        jump = 1;
    }
    else if ((column - p_pos.c == 2)
             && (p_pos.l == line)
             && is_passable_strat(b, p_pos.c, p_pos.l, 2)
             && is_passable_strat(b, p_pos.c + 1, p_pos.l, 2)
             && (get_position_strat(b, p_pos.c + 1, p_pos.l) != -1)
             
             && is_passable(&b->board, p_pos.c, p_pos.l, 2)
             && is_passable(&b->board, p_pos.c + 1, p_pos.l, 2)
             && (get_position(&b->board, p_pos.c + 1, p_pos.l) != -1))
    {
        jump = 1;
    }
    else if ((p_pos.l - line == 2)
             && (p_pos.c == column)
             && is_passable_strat(b, p_pos.c, p_pos.l, 1)
             && is_passable_strat(b, p_pos.c, p_pos.l - 1, 1)
             && (get_position_strat(b, p_pos.c, p_pos.l - 1) != -1)
             
             && is_passable(&b->board, p_pos.c, p_pos.l, 1)
             && is_passable(&b->board, p_pos.c, p_pos.l - 1, 1)
             && (get_position(&b->board, p_pos.c, p_pos.l - 1) != -1))
    {
        jump = 1;
    }
    else if ((line - p_pos.l == 2)
             && (p_pos.c == column)
             && is_passable_strat(b, p_pos.c, p_pos.l, 3)
             && is_passable_strat(b, p_pos.c, p_pos.l + 1, 3)
             && (get_position_strat(b, p_pos.c, p_pos.l + 1) != -1)
             
             && is_passable(&b->board, p_pos.c, p_pos.l, 3)
             && is_passable(&b->board, p_pos.c, p_pos.l + 1, 3)
             && (get_position(&b->board, p_pos.c, p_pos.l + 1) != -1))
    {
        jump = 1;
    }
    
    
    // find direction
    
    char d = -1;
    if ((p_pos.c - column == 1) && (p_pos.l == line)) {
        d = 0;
    } else if ((p_pos.l - line == 1) && (p_pos.c == column)) {
        d = 1;
    } else if ((column - p_pos.c == 1) && (p_pos.l == line)) {
        d = 2;
    } else if ((line - p_pos.l == 1) && (p_pos.c == column)) {
        d = 3;
    }
    
    return jump || (is_passable(&b->board, column, line, d) && is_passable_strat(b, column, line, d)) ;
    
}

int may_end_strat(struct strat_board* b, int t[N][N], char col, char row, char end_row) {
    
    if (row == end_row) {
        return 1;
    } else if (t[row][col] == 1) {
        return 0;
    } else {
        t[row][col] = 1;
        return ((is_passable_strat(b, col, row, 2)
                 && (get_position_strat(b, col + 1, row) == -1)
                 && may_end_strat(b, t, col + 1, row, end_row))
                || (is_passable_strat(b, col, row, 0)
                    && (get_position_strat(b,col - 1,row) == -1)
                    && may_end_strat(b, t, col - 1, row, end_row))
                || (is_passable_strat(b, col, row, 3)
                    && (get_position_strat(b,col,row + 1) == -1)
                    && may_end_strat(b, t, col, row + 1, end_row))
                || (is_passable_strat(b, col, row, 1)
                    && (get_position_strat(b,col,row - 1) == -1)
                    && may_end_strat(b, t, col, row - 1, end_row))
                );
    }
    
    
}

int is_blockable_strat(struct strat_board* b, char column, char line, char direction) {
    
    int res = 1;
    
    int c = 2 * column;
    int l = 2 * line;
    
    if (is_blockable(&b->board, column, line, direction) == 0) {
        res = 0;
    }
    
    // Check if there is not a wall already at this spot
    // and if you are within the board limits
    
    switch (direction) {
        case 0:
            if ((line < 1) || (column > N - 2))
                res = 0;
            else if ((b->t[l - 1][c] == 1) || (b->t[l - 1][c + 1] == 1) || (b->t[l - 1][c + 2] == 1))
                res = 0;
            
            break;
        case 1:
            if ((column < 1) || (line > N - 2))
                res = 0;
            else if ((b->t[l][c - 1] == 1) || (b->t[l + 1][c - 1] == 1) || (b->t[l + 2][c - 1] == 1))
                res = 0;
            break;
        default:
            break;
    }
    
    // If it's not blockable return now to prevent a lot of calculs
    // and to prevent the erasing of existing walls
    if (res == 0) {
        return res;
    }
    
    
    
    // Check if both players can still win
    
    int tA[N][N];
    int tB[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tA[i][j] = 0;
            tB[i][j] = 0;
        }
    }
    
    // place the wall for testing
    if (direction) {
        b->t[l][c - 1] = 1;
        b->t[l + 1][c - 1] = 1;
        b->t[l + 2][c - 1] = 1;
    } else {
        b->t[l - 1][c] = 1;
        b->t[l - 1][c + 1] = 1;
        b->t[l - 1][c + 2] = 1;
    }
    
    if ((may_end_strat(b, tA, b->players[get_current_player(&b->board)].c, b->players[get_current_player(&b->board)].l, 0) == 0)
        || (may_end_strat(b, tB, b->players[(get_current_player(&b->board) + 1) % 2].l, b->players[(get_current_player(&b->board) + 1) % 2].l, N - 1) == 0))
    {
        res = 0;
    }
    
    // remove the wall
    if (direction) {
        b->t[l][c - 1] = 0;
        b->t[l + 1][c - 1] = 0;
        b->t[l + 2][c - 1] = 0;
    } else {
        b->t[l - 1][c] = 0;
        b->t[l - 1][c + 1] = 0;
        b->t[l - 1][c + 2] = 0;
    }
    
    return res;

}

void place_wall_strat(struct strat_board* b, char column, char line, char direction) {
 
    if (is_blockable_strat(b, column, line, direction)) {
        
        int l = 2 * line;
        int c = 2 * column;
        
        if (direction ==  1) {
            b->t[l][c - 1] = 1;
            b->t[l + 1][c - 1] = 1;
            b->t[l + 2][c - 1] = 1;
        } else {
            b->t[l - 1][c] = 1;
            b->t[l - 1][c + 1] = 1;
            b->t[l - 1][c + 2] = 1;
        }
        
    }
    
}

// Modifies the strat_board to move player p
void move_pawn_strat(struct strat_board *b, char column, char line) {
    
    int p = b->current_player;
    
    b->players[p].c = column;
    b->players[p].l = line;
    b->players[p].d = -1;
    
    b->current_player = (p + 1) % 2;
    
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
    
    fprintf(stderr, "Couldn't find this player !\n");
    exit(EXIT_FAILURE);
    
}



// Writes in a table NxN initialized with zeros all the paths from the position indicated.
int paths(struct strat_board *b, int t[N][N], char column, char line, int n, int p) {
    
    if ((b->players[(p + 1) % 2].c == column) && (b->players[(p + 1) % 2].l == line)) {
        t[line][column] = -1;
        if (is_passable_strat(b, column, line, 0)
            && is_passable(&b->board, column, line, 0)
            && ((t[line][column - 1] > n) || (t[line][column] == 0))) {
            t[line][column - 1] = n;
        }
        if (is_passable_strat(b, column, line, 1)
            && is_passable(&b->board, column, line, 1)
            && ((t[line - 1][column] > n) || (t[line][column] == 0))) {
            t[line - 1][column] = n;
        }
        if (is_passable_strat(b, column, line, 2)
            && is_passable(&b->board, column, line, 2)
            && ((t[line][column + 1] > n) || (t[line][column] == 0))) {
            t[line][column + 1] = n;
        }
        if (is_passable_strat(b, column, line, 3)
            && is_passable(&b->board, column, line, 3)
            && ((t[line + 1][column] > n) || (t[line][column] == 0))) {
            t[line + 1][column] = n;
        }
    } else if (t[line][column] && (t[line][column] < n)) {
        return 0;
    } else {
        t[line][column] = n;
    }
    
    return (   (is_passable_strat(b, column, line, 0)
                && is_passable(&b->board, column, line, 0)
                && paths(b, t, column - 1, line, n + 1, p))
            || (is_passable_strat(b, column, line, 1)
                && is_passable(&b->board, column, line, 1)
                && paths(b, t, column, line - 1, n + 1, p))
            || (is_passable_strat(b, column, line, 2)
                && is_passable(&b->board, column, line, 2)
                && paths(b, t, column + 1, line, n + 1, p))
            || (is_passable_strat(b, column, line, 3)
                && is_passable(&b->board, column, line, 3)
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
     fprintf(stderr, "%d\t", t[i][j]);
     }
     fprintf(stderr, "\n");
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
int board_value(struct strat_board *b) {
    
        return shortest_path(b, (b->current_player + 1) % 2) - shortest_path(b, b->current_player);
    
}




// Returns and integer indicating the best mark you can get with a specific board state
// by testing the next n turns.
// This AI maximize and its enemy minimize.
void minimax(struct strat_board *b, int *mark, struct pos *pos, int n) {
    
    int p = b->current_player;
    
    if ((n == 0) || (b->players[p].l == ((p == 0) ? 0 : N - 1))) {
        
        *mark = board_value(b);
        return ;
        
    } else {
        /*
        // Initialize
        pos->c = -1;
        pos->l = -1;
        pos->d = -1;
        */
        if (p == get_current_player(&b->board)) {
            *mark = -1;
        } else {
            *mark = 200;
        }
        
        // play the possible moves from this state of the board
        // and keep in memory the best one.
        
        // --- moves --- //
        
        /* VERSION 1
        // there are 12 possible moves
        // 0..3 : normal moves ; 4..7 : jumps over ; 7..11 : diagonals.
        
        int col_move[12] = {-1, 0, 1, 0, -2, 0, 2, 0, -1, 1, 1, -1};
        int row_move[12] = {0, -1, 0, 1, 0, -2, 0, 2, -1, -1, 1, 1};

        fprintf(stderr, "Ca va tourner pour les mouvements\n");
        
        for (int i = 0; i < 12; i++) {
            
            //fprintf(stderr, "Et un petit tour\n");
            
            if (is_movement_allowed(b, b->players[p].c + col_move[i], b->players[p].l + row_move[i])) {
                
                struct strat_board b_cpy = *b;
                move_pawn_strat(&b_cpy, b->players[p].c + col_move[i], b->players[p].l + row_move[i]);
                struct pos new_pos = {.c = b->players[p].c + col_move[i], .l = b->players[p].l + row_move[i], .d = -1};
                int new_mark;
                minimax(&b_cpy, &new_mark, &new_pos, n - 1);
                if ((p == get_current_player(&b->board)) && new_mark > *mark) {
                    *mark = new_mark;
                    *pos = new_pos;
                    fprintf(stderr, "New best board\n");
                } else if ((p == (get_current_player(&b->board) + 1) % 2) && new_mark < *mark) {
                    *mark = new_mark;
                    *pos = new_pos;
                    fprintf(stderr, "New best board\n");
                }
                
            }
            
        }
         */
        
        /* VERSION 2 */
        
        int moves_nb = 0;
        
        int t[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                t[i][j] = 0;
            }
        }
        
        paths(b, t, b->players[p].c, b->players[p].l, 0, p);
        t[b->players[p].l][b->players[p].c] = -1;
        
        
        // TEST //
        fprintf(stderr, "\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                fprintf(stderr, "%d\t", t[i][j]);
            }
            fprintf(stderr, "\n");
        }
        fprintf(stderr, "\n");
        // ---- //
        
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (t[i][j] == 1) {
                    
                    struct strat_board b_cpy = *b;
                    move_pawn_strat(&b_cpy, j, i);
                    struct pos new_pos = {.c = j, .l = i, .d = -1};
                    int new_mark;
                    minimax(&b_cpy, &new_mark, &new_pos, n - 1);
                    if ((p == get_current_player(&b->board)) && new_mark > *mark) {
                        *mark = new_mark;
                        *pos = new_pos;
                        fprintf(stderr, "New best board\n");
                    } else if ((p == (get_current_player(&b->board) + 1) % 2) && new_mark < *mark) {
                        *mark = new_mark;
                        *pos = new_pos;
                        fprintf(stderr, "New best board\n");
                    }

                    
                }
            }
        }
        
        // ------------- //
      
        /*
        // -- bridges -- //
        struct pos bridges[2 * N * N];
        int bridges_nb = 0;
        
        // Calculate the most profitable bridges.
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if(is_blockable_strat(b, j, i, 0)) {
                    bridges[bridges_nb].c = j;
                    bridges[bridges_nb].l = i;
                    bridges[bridges_nb].d = 0;
                    bridges_nb++;
                }
                if(is_blockable_strat(b, j, i, 1)) {
                    bridges[bridges_nb].c = j;
                    bridges[bridges_nb].l = i;
                    bridges[bridges_nb].d = 1;
                    bridges_nb++;
                }
            }
        }
        
        fprintf(stderr, "Ca va tourner pour les murs\n");
        
        for (int i = 0; i < bridges_nb; i++) {
            
            // if (is_blockable_strat(b, bridges[i].c, bridges[i].l, bridges[i].d)) {
                
                struct strat_board b_cpy = *b;
                place_wall_strat(&b_cpy, bridges[i].c, bridges[i].l, bridges[i].d);
                struct pos new_pos = {.c = bridges[i].c, .l = bridges[i].l, .d = bridges[i].d};
                int new_mark;
                minimax(&b_cpy, &new_mark, &new_pos, n - 1);
                if ((p == get_current_player(&b->board)) && new_mark > *mark) {
                    *mark = new_mark;
                    *pos = new_pos;
                    fprintf(stderr, "New best board\n");
                } else if ((p == (get_current_player(&b->board) + 1) % 2) && new_mark < *mark) {
                    *mark = new_mark;
                    *pos = new_pos;
                    fprintf(stderr, "New best board\n");
                }
                
            // }
            
        }
        // ------------- //
       */
        
    }
    
}


void minimax2__play(struct board *b) {
    
    struct strat_board sb;
    sb.board = *b;
    sb.players[get_current_player(b)] = whereisp(b, get_current_player(b));
    sb.players[(get_current_player(b) + 1) % 2] = whereisp(b, (get_current_player(b) + 1) % 2);
    sb.current_player = get_current_player(b);
    for (int i = 0; i < 2 * N - 1; i++) {
        for (int j = 0; j < 2 * N - 1; j++) {
            sb.t[i][j] = 0;
        }
    }
    
    int mark;
    struct pos position;
    
    minimax(&sb, &mark, &position, 1);
    
    if (position.d == -1) {
        move_pawn(b, position.c, position.l);
    } else {
        place_wall(b, position.c, position.l, position.d);
    }
    
}


REGISTER_STRATEGY("Minimax2", minimax2__play);
