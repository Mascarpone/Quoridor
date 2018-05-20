#include "../src/header/interface.h"

// This main reads the moves written by advance in a file .txt
// following specific syntax rules

int main() {
    
    const struct board* b = init_board(&BOARD);
    
    struct move move[2];
    int turn = 0;
    FILE* lecture;
    lecture = fopen("test_blockable.txt", "r");
    if(lecture == NULL){
        printf("Impossible d'ouvrir le fichier \n");
        exit(1);
    }
    
    int p = 0;
    
    while (1) {
        
        
        
        // Is there a winner ? //
        if (win(b)) {
            printf("Player %c wins !\n\n", ((b->current_player == 'A') ? 'B' : 'A'));
            fclose(lecture);
            return (EXIT_SUCCESS);
        }
        
        
        
        turn++;
        printf("TOUR NUMERO %d\n", turn);
        if (turn % 2 == 1) {
            parser(move, lecture, 1); // One line read i the file for the move of A AND the move of B
        }
        
       
        
        print_board(b);
        
        
        
        // Play //
        if (move[p].d == 0) {
            move_pawn(b, move[p].c, move[p].l);
        } else {
            switch (move[p].d) {
                case 'v':
                    place_wall(b, move[p].c, move[p].l, 1);
                    break;
                case 'h':
                    place_wall(b, move[p].c, move[p].l, 0);
                    break;
                default:
                    printf("unknown direction of the wall\n");
                    exit(EXIT_FAILURE);
                    break;
            }
        }
        
        
        
        // Change Player //
        switch (b->current_player) {
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
        
        p = (p == 0) ? 1 : 0;
        
        
        
    }
    
}
