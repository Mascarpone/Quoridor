#include "interface.h"


WINDOW *create_newwin(int height, int width, int starty, int startx) {
    
    WINDOW *local_win;
    
    local_win = newwin(height, width, starty, startx);

    
    return local_win;
    
}

void print_board(const struct board* b) {
    
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_YELLOW);
    init_pair(4, COLOR_WHITE, COLOR_RED);
    init_pair(5, COLOR_WHITE, COLOR_BLUE);

    mvprintw(2, 27, "JOUEUR 2");
    mvprintw(38, 127, "JOUEUR 1");

    refresh();


    WINDOW *cadre[2];
    cadre[0] = create_newwin(39, 78, 1 , (COLS - 75) / 2);
    wbkgd(cadre[0], COLOR_PAIR(2));
    cadre[1] = create_newwin(37, 74, 2 , (COLS - 72) / 2 );
    wbkgd(cadre[1], COLOR_PAIR(1));
    
    wrefresh(cadre[0]);
    wrefresh(cadre[1]);
    WINDOW *grille[17*17];
    int n = 0, m = 0, r = 0;
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 17; j++) {
            if (i % 2 == 0 && i != 1 && j % 2 == 0 && b->t[i][j] ==0 ) {     // grille
                grille[n] = create_newwin(3, 6, 3 + 2 * i, (COLS - 67) / 2 + 4 * j);
                wbkgd(grille[n], COLOR_PAIR(2));
                wrefresh(grille[n]);
                n++;
            } else if (i % 2 == 0 && j % 2 == 1 && b->t[i][j] == 1) {       // barre verticale
                grille[n] = create_newwin(3, 2, 3 + 2 * i, (COLS - 63) / 2 + 4 * j);
                wbkgd(grille[n], COLOR_PAIR(3));
                wrefresh(grille[n]);
                n++;
            } else if (i % 2 == 1 && j % 2 == 0 && b->t[i][j] == 1) {       // barre horizantale
                grille[n] = create_newwin(1, 6, 4 + 2 * i, (COLS - 67) / 2 + 4 * j);
                wbkgd(grille[n], COLOR_PAIR(3));
                wrefresh(grille[n]);
                n++;
            } else if ( i % 2 == 1 && j % 2 == 1 && b->t[i][j] == 1) {      // barre centrale
                grille[n] = create_newwin(1, 2, 4 + 2 * i, (COLS - 63) / 2 + 4 * j);
                wbkgd(grille[n], COLOR_PAIR(3));
                wrefresh(grille[n]);
                n++;
            }
        }
    }
    
    // Display players
    WINDOW *players[2];
    players[0] = create_newwin(3, 6, 3 + 2 * toBoardcoor(b->A.line), (COLS - 67) / 2 + 4 * toBoardcoor(b->A.column));
    players[1] = create_newwin(3, 6, 3 + 2 * toBoardcoor(b->B.line), (COLS - 67) / 2 + 4 * toBoardcoor(b->B.column));
    wbkgd(players[0], COLOR_PAIR(4));
    wbkgd(players[1], COLOR_PAIR(5));
    wrefresh(players[0]);
    wrefresh(players[1]);
    

    // Display remaining bridges
    WINDOW *player_1[10];
    WINDOW *player_2[10];
    for (int i = 0 ; i < b->B.bar_nb; i++) {                                 // joueur 1
      player_2[i]=create_newwin(1, 14, 4 + 2 * i, (COLS - 110) / 2 );
      wbkgd(player_2[i], COLOR_PAIR(3));
      wrefresh(player_2[i]);
    }
    
    for (int i = b->B.bar_nb ; i < 10; i++) {                                 // mettre des barres noires
      player_2[i]=create_newwin(1, 14, 4 + 2 * i, (COLS - 110) / 2 );
      wbkgd(player_2[i], COLOR_PAIR(1));
      wrefresh(player_2[i]);
    }
    
    
    
    for (int j = 0 ; j < b->A.bar_nb ; j++) {                                 //joueur 2
      player_1[j]=create_newwin(1, 14, 36 - 2 * j, (COLS + 90) / 2 );
      wbkgd(player_1[j], COLOR_PAIR(3));
      wrefresh(player_1[j]);

      }
   for (int j = b->A.bar_nb ; j < 10 ; j++) {                                 // mettre des barres noires
      player_1[j]=create_newwin(1, 14, 36 - 2 * j, (COLS + 90) / 2 );
      wbkgd(player_1[j], COLOR_PAIR(1));
      wrefresh(player_1[j]);

      }
   
    

    
    getch();
    
    endwin();

    
}
