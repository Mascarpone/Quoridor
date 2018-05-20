#include "interface.h"



void parser(struct move move[2], FILE* file, int num_line) {
    
    char line[9];
    
    for (int i = 0; i < num_line; i++) {
        fgets(line, sizeof(line), file);
    }
    
    sscanf(line, "%c%c%c %c%c%c\n", &move[0].c, &move[0].l, &move[0].d, &move[1].c, &move[1].l, &move[1].d);
    
    if(move[0].d==' ')
        move[0].d = -1;
    if(move[1].d=='\n')
        move[1].d = -1;
    
    for (int i = 0; i < 2; i++) {
        move[i].c = move[i].c - 'a';
        move[i].l = move[i].l - '1';
        if (move[i].d == 'h')
            move[i].d = 0;
        else if (move[i].d == 'v')
            move[i].d = 1;
    }
    
}



void write_in_file(struct move move, FILE* write_file, int p) {
   
    move.c = move.c + 'a';
    if (move.d == 0)
        move.d = 'h';
    else if (move.d == 1)
        move.d = 'v';
    else
        move.d = 0;
   
    
    fprintf(write_file,"%c%d", move.c, move.l);
    if (move.d)
      fprintf(write_file,"%c", move.d);


    switch (p) {
    case 0:
      fprintf(write_file, " ");
      break;
    case 1:
      fprintf(write_file, "\n");
      break;
    default:
      fprintf(stderr, "Unknown player\n");
      break;
    }

}
