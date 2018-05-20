#include "../header/interface.h"
#include "../registry.h"

#include <stdio.h>
#include <stdlib.h>

void player__play(struct board * b) {
    
    noecho();
    raw();
    char c;
    char l;
    char d;
    mvprintw(LINES - 5,COLS - 100,"Joueur %d : ",get_current_player(b)+1);
    c = getch();
    mvprintw(LINES-5,COLS-87,"%c",c);
    l = getch();
    mvprintw(LINES-5,COLS-86,"%c",l);
    d=getch();
    getch();
    if(d=='h')
    {
      mvprintw(LINES-5,COLS-85,"%c",d);
      mvprintw(LINES - 4, COLS - 100,"vous avez joué : %c%c%c", c, l, d);
      place_wall(b,c-'a',l-'1',0);
      getch();
    }
    else if(d=='v')
    {
      mvprintw(LINES-5,COLS-85,"%c",d);
      mvprintw(LINES - 4, COLS - 100,"vous avez joué : %c%c%c", c, l, d);
      place_wall(b,c-'a',l-'1',1);
      getch();
    }
    else if(d=='0')
    {
      mvprintw(LINES - 4, COLS - 100,"vous avez joué : %c%c", c, l);
      move_pawn(b, c - 'a', l - '1');   
      getch();
    }
    else
      mvprintw(LINES - 4, COLS - 100,"erreur");
}

REGISTER_STRATEGY("Player", player__play);
