#include "./header/interface.h"
#include "registry.h"

// A copy of the real BOARD is given to the player
// The real BOARD can only be changed by using OUR functions

// REMEMBER (cf interface.h) : struct board BOARD; is the real board.



struct move compare_board(struct board* b) {
    
    struct player *p = NULL, *P = NULL;
    
    switch (BOARD.current_player) {
        case 'A':
            p = &(b->A);
            P = &BOARD.A;
            break;
        case 'B':
            p = &(b->B);
            P = &BOARD.B;
            break;
        default:
            break;
    }
    
    
    struct move move;
    
    int count = 0;
    
    for (int i = 0; i < 2 * N - 1; i++) {
        for (int j = 0;  j < 2 * N - 1; j++) {
            if (b->t[i][j] != BOARD.t[i][j]) {
                count++;
                if (count == 1) {
                    move.c = j; // move.c is temporarily set between 0 and 2 * N - 2
                    move.l = i; // move.l is temporarily set between 0 and 2 * N - 2
                }
            }
        }
    }
    
    
    if ((move.c + 1 < 2 * N - 1) && (b->t[move.l][move.c + 1] == 1))
        move.d = 0; // horizontal
    else if ((move.l + 1 < 2 * N - 1) && (b->t[move.l + 1][move.c] == 1))
        move.d = 1; // vertical
            
    
        
    if ((p->line == P->line) && (p->column == P->column) && (count == 0)) {
        
        fprintf(stderr, "Player hasn't played !\n");
        exit(EXIT_FAILURE);
        
    } else if ((p->line != P->line || p->column != P->column) && (count == 0)) { // player has moved his pawn
        
        move.c = p->column;
        move.l = p->line;
        move.d = -1;
        
    } else if (count == 3) { // player has placed a bridge
        
        // check bridges number
        if (p->bar_nb != P->bar_nb)
            p->bar_nb = P->bar_nb;
        
        if (move.d == 1) {
            move.l = move.l / 2;
            move.c = (move.c + 1) / 2;
        } else if (move.d == 0) {
            move.l = (move.l + 1) / 2;
            move.c = move.c / 2;
        } else {
            fprintf(stderr, "Problem in wall direction\n");
            exit(EXIT_FAILURE);
        }
        
    } else {
        
        fprintf(stderr, "Unknown movement !\n");
        exit(EXIT_FAILURE);
        
    }

    
    return move;
    
}



void playReal(struct move move, FILE* file) {
    
    // make the player play with OUR functions
    if (move.d == -1) {
        move_pawn(&BOARD, move.c, move.l);
    } else {
        place_wall(&BOARD, move.c, move.l, move.d);
        
        // decrement bar_nb count
        switch (BOARD.current_player) {
            case 'A':
                BOARD.A.bar_nb--;
                break;
            case 'B':
                BOARD.B.bar_nb--;
                break;
            default:
                break;
        }
        
    }
    
    // write what it has done in the file (historic)
    write_in_file(move, file, get_current_player(&BOARD));
    
}



int main(int argc, char* argv[]) {
    
    init_board(&BOARD);
    
    // the copy
    struct board b_cpy;
    
    
    
    
    FILE* historic; // game historic
    historic = fopen("historic.txt", "w");
    if(historic == NULL){
        fprintf(stderr, "Didn't manage to open historic.txt\n");
        exit(EXIT_FAILURE);
    }
    
    

    
    printf("-------------------\n");
    printf("Quoridor strategies\n");
    
    for (int i = 0; i < strategies_count; i++) {
        printf("Strat n°%d : %s\n", i, strategies[i]->name);
    }
    
    int p1, p2;
    printf("Choose player 1 : ");
    scanf("%d", &p1);
    printf("Choose player 2 : ");
    scanf("%d", &p2);
    int p = p1;
    
    
    
    print_board(&BOARD);
    struct move move;
    while (!win(&BOARD)) {
        
        b_cpy = BOARD;
        
        strategies[p]->play(&b_cpy);
        move = compare_board(&b_cpy);
        //printf("%s wants to play in %d%d%d\n", strategies[p]->name, move.c, move.l, move.d);
        playReal(move, historic);
        
        print_board(&BOARD);
        
        // change player
        p = (p == p1) ? p2 : p1;
        switch (BOARD.current_player) {
            case 'A':
                BOARD.current_player = 'B';
                break;
            case 'B':
                BOARD.current_player = 'A';
                break;
            default:
                printf("Unknown player\n");
                break;
        }  
        
    }
    
    
    
    printf("Strat %s WINS !\n", (win(&BOARD) == -1) ? strategies[p1]->name : strategies[p2]->name);
    
    return EXIT_SUCCESS;
    
}
