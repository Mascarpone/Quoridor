#include "interface.h"



// Returns an integer describing what is at position (column, line)
// on the board b. The result is either -1 (empty), 0 (player A) or 1 (player B).
int get_position(const struct board* b, char column, char line) {
    
    int res = -1;
    
    if ((b->A.line == line) && (b->A.column == column)) {
        res = 0;
    } else if ((b->B.line == line) && (b->B.column == column)) {
        res = 1;
    }
    
    return res;
    
}



// Returns an integer indicating whether there is a wall on the board b
// at position starting from (column, line), in a direction that is either
// towards smaller cols (0), smaller lines (1), larger cols (2) or larger lines (3).
int is_passable(const struct board* b, char column, char line, char direction)
{
    
    int res = 1;
    int l = toBoardcoor(line);
    int c = toBoardcoor(column);
    
    
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
            break;
    }
    
    return res;
    
}



// Moves a pawn on the position (column, line)
// Columns and lines are numbered from 0 to N-1.
void move_pawn(struct board* b, char column, char line) {
    
    // find current player
    struct player* P;
    if (b->current_player == 'A')
        P = &(b->A);
    else
        P = &(b->B);
    
    
    
    // check if this is a movement concerning the jump of the enemy pawn
    
    int jump = 0;
    
    // diagonals if there is a wall dehind the enemy
    if ((P->column - column == 1) && (P->line - line == 1)) //up left
    {
        if ((get_position(b, P->column - 1, P->line) != -1)
            && is_passable(b, P->column, P->line, 0)
            && is_passable(b, P->column - 1, P->line, 1)
            && (is_passable(b,P->column - 1,P->line, 0) == 0)) //left
        {
            jump = 1;
        }
        else if ((get_position(b, P->column, P->line - 1) != -1)
                 && is_passable(b, P->column, P->line, 1)
                 && is_passable(b, P->column, P->line-1, 0)
                 && (is_passable(b, P->column, P->line-1, 1) == 0))
        {
            jump = 1;
        }
        else
        {
            printf("You tried to cheat ul !\n");
            exit(EXIT_FAILURE);
        }
    }
    
    else if ((column - P->column == 1) && (P->line - line == 1)) // up right
    {
        if ((get_position(b, P->column, P->line - 1) != -1)
            && is_passable(b,P->column, P->line, 1)
            && is_passable(b, P->column, P->line - 1, 2)
            && (is_passable(b, P->column, P->line - 1, 1) == 0)) // up
        {
            jump = 1;
        }
        else if ((get_position(b, P->column + 1, P->line) != -1)
                 && is_passable(b,P->column, P->line, 2)
                 && is_passable(b, P->column + 1, P->line, 1)
                 && (is_passable(b, P->column + 1, P->line, 2) == 0)) // right
        {
            jump = 1;
        }
        else
        {
            printf("You tried to cheat ur !\n");
            exit(EXIT_FAILURE);
        }
    }
    
    else if ((column - P->column == 1) && (line - P->line == 1)) // bellow right
    {
        if ((get_position(b, P->column + 1, P->line) != -1)
            && is_passable(b, P->column, P->line, 2)
            && is_passable(b, P->column + 1, P->line, 3)
            && (is_passable(b, P->column + 1, P->line, 2) == 0)) // right
        {
            jump = 1;
        }
        else if ((get_position(b, P->column, P->line + 1) != -1)
                 && is_passable(b, P->column, P->line, 3)
                 && is_passable(b, P->column, P->line + 1, 2)
                 && (is_passable(b, P->column, P->line + 1, 3) == 0))  // bellow ok
        {
            jump = 1;
        }
        else
        {
            printf("You tried to cheat br!\n");
            exit(EXIT_FAILURE);
        }
    }
    
    else if ((column - P->column == 1) && (line - P->line == 1)) // bellow left
    {
        if ((get_position(b, P->column, P->line + 1) != -1)
            && is_passable(b, P->column, P->line, 3)
            && is_passable(b, P->column, P->line + 1, 0)
            && (is_passable(b, P->column, P->line + 1, 3) == 0)) // bellow
        {
            jump = 1;
        }
        else if ((get_position(b, P->column - 1, P->line) != -1)
                 && is_passable(b, P->column, P->line, 0)
                 && is_passable(b, P->column - 1, P->line, 3)
                 && (is_passable(b, P->column - 1, P->line, 0) == 0)) // left
        {
            jump = 1;
        }
        else
        {
            printf("You tried to cheat bl!\n");
            exit(EXIT_FAILURE);
        }
    }
    
    // jump forward
    if ((P->column - column == 2)
        && (P->line == line)
        && is_passable(b, P->column, P->line, 0)
        && is_passable(b, P->column - 1, P->line, 0)
        && (get_position(b, P->column - 1, P->line) != -1))
    {
        jump = 1;
    }
    else if ((column - P->column == 2)
             && (P->line == line)
             && is_passable(b, P->column, P->line, 2)
             && is_passable(b, P->column + 1, P->line, 2)
             && (get_position(b, P->column + 1, P->line) != -1))
    {
        jump = 1;
    }
    else if ((P->line - line == 2)
             && (P->column == column)
             && is_passable(b, P->column, P->line, 1)
             && is_passable(b, P->column, P->line - 1, 1)
             && (get_position(b, P->column, P->line - 1) != -1))
    {
        jump = 1;
    }
    else if ((line - P->line == 2)
             && (P->column == column)
             && is_passable(b, P->column, P->line, 3)
             && is_passable(b, P->column, P->line + 1, 3)
             && (get_position(b, P->column, P->line + 1) != -1))
    {
        jump = 1;
    }
    
    // jump
    if (jump == 1)
    {
        P->column = column;
        P->line = line;
        return;
    }
    
    
    
    // otherwise, find the direction wanted
    
    char d;
    if ((P->column == column) && (P->line == line)) {
        printf("You can't pass your turn !\n");
        exit(EXIT_FAILURE);
    } else if ((P->column - column == 1) && (P->line == line)) {
        d = 0;
    } else if ((P->line - line == 1) && (P->column == column)) {
        d = 1;
    } else if ((column - P->column == 1) && (P->line == line)) {
        d = 2;
    } else if ((line - P->line == 1) && (P->column == column)) {
        d = 3;
    } else {
        printf("You tried to cheat (direction) !\n");
        exit(EXIT_FAILURE);
    }

    // move the pawn
    if ((d == 0)
        && is_passable(b, P->column, P->line, d)
        && (get_position(b, P->column - 1, P->line) == -1))
    {
        P->column = column;
        P->line = line;
    }
    else if ((d == 1)
             && is_passable(b, P->column, P->line, d)
             && (get_position(b, P->column, P->line - 1) == -1))
    {
        P->column = column;
        P->line = line;
    }
    else if((d == 2)
            && is_passable(b, P->column, P->line, d)
            && (get_position(b, P->column + 1, P->line) == -1))
    {
        P->column = column;
        P->line = line;
    }
    else if((d == 3)
            && is_passable(b, P->column, P->line, d)
            && (get_position(b, P->column, P->line + 1) == -1))
    {
        P->column = column;
        P->line = line;
    }
    else
    {
        printf("You can't play here !\n");
        exit(EXIT_FAILURE);
    }

    
}
