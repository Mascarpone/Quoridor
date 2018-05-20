#include "interface.h"


// Returns the number of available bridges for the player.
unsigned int remaining_bridges(const struct board* b, unsigned int player) {
    
    switch (player) {
        case 0:
            return b->A.bar_nb;
            break;
        case 1:
            return b->B.bar_nb;
        default:
            fprintf(stderr, "Unknown player\n");
            return 0;
            break;
    }
    
}



int may_end(const struct board* b, int t[N][N], char col, char row, char end_row) {
    
    if (row == end_row) {
        return 1;
    } else if (t[row][col] == 1) {
        return 0;
    } else {
        t[row][col] = 1;
        return ((is_passable(b, col, row, 2)
                    && (get_position(b, col + 1, row) == -1)
                    && may_end(b, t, col + 1, row, end_row))
                || (is_passable(b, col, row, 0)
                    && (get_position(b,col - 1,row) == -1)
                    && may_end(b, t, col - 1, row, end_row))
                || (is_passable(b, col, row, 3)
                    && (get_position(b,col,row + 1) == -1)
                    && may_end(b, t, col, row + 1, end_row))
                || (is_passable(b, col, row, 1)
                    && (get_position(b,col,row - 1) == -1)
                    && may_end(b, t, col, row - 1, end_row))
                );
    }
    
    
}



// Returns an integer indicating whether it is possible to place a wall
// on the corresponding column, line and direction.
// Directions are either 0 (horizontal) or 1 (vertical).
int is_blockable(struct board* b, char column, char line, char direction) {
    
    int res = 1;
    
    int c = toBoardcoor(column);
    int l = toBoardcoor(line);
    
    
    
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
    
    if ((may_end(b, tA, b->A.column, b->A.line, 0) == 0)
        || (may_end(b, tB, b->B.column, b->B.line, N - 1) == 0))
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



// Places a wall on the corresponding column, line and position
// Positions are either 0 (horizontal) or 1 (vertical).
void place_wall(struct board* b, char column, char line, char direction) {
    
    if (remaining_bridges(b, (b->current_player == 'A') ? 0 : 1) > 0) {
        
        if (is_blockable(b, column, line, direction)) {
            
            int l = toBoardcoor(line);
            int c = toBoardcoor(column);
            
            if(direction) {

                b->t[l][c - 1] = 1;
                b->t[l + 1][c - 1] = 1;
                b->t[l + 2][c - 1] = 1;
                
            } else {

                b->t[l - 1][c] = 1;
                b->t[l - 1][c + 1] = 1;
                b->t[l - 1][c + 2] = 1;
                
            }
            
        } else {
            
            printf("You can't place a wall here !\n");
            exit(EXIT_FAILURE);
            
        }
        
    } else {
        
        fprintf(stderr, "You haven't walls anymore\n");
        exit(EXIT_FAILURE);
        
    }
    
}
