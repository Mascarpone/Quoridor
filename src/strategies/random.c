#include "../header/interface.h"
#include "../registry.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random__play(struct board * b) {
    
    srand(time(NULL));
    
    // choose between placing a wall or moving
    int wORd;
    if (remaining_bridges(b, get_current_player(b)) == 0)
        wORd = 1;
    else
        wORd = rand() % 2;
    
    
    
    char column, line, direction;
    switch (wORd) {
        case 0: // place a wall
            
            do {
                column = rand() % 9;
                line = rand() % 9;
                direction = rand() % 2;
            } while (is_blockable(b, column, line, direction) == 0);
            
            //printf("je veux jouer en %d%d%d\n", column, line, direction);
            place_wall(b, column, line, direction);
            
            break;
        case 1: // move
            
            // find my position
            column = 0;
            line = 0;
            while (get_position(b, column, line) != get_current_player(b)) {
                column++;
                if (column == N) {
                    line++;
                    column = 0;
                }
                if (line == N) {
                    printf("Couldn't find my position !\n");
                    exit(EXIT_FAILURE);
                }
            }
            
            
            // choose a direction
            do {
                direction = rand() % 4; // doesn't care about jumping over the enemy
            } while (is_passable(b, column, line, direction) == 0);
            
            switch (direction) {
                case 0:
                    column--;
                    break;
                case 1:
                    line--;
                    break;
                case 2:
                    column++;
                    break;
                case 3:
                    line++;
                    break;
                default:
                    break;
            }
            
            //printf("je veux jouer en %d%d\n", column, line);
            move_pawn(b, column, line);
            
            break;
        default:
            break;
    }
    
};

REGISTER_STRATEGY("Random", random__play);
