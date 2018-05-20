************************************* Explication de compilation ************************************


Afin de compiler, il faut faire un "make" dans le dossier src. 


************************************* Tester les IA *************************************************


Après avoir compilé, lancez "server" puis choisissez 2 IA parmis celles proposées.
Enfin pressez "Enter" pour passer au tour suivant.
Pour ajouter une IA, placez le .c dans le répertoire "strategies" du dossier "src" puis compilez.


************************************ Pour créer sa propre IA ****************************************

Votre fonction principale prendra en entrée un "struct board*".
Les colonnes et lignes sont des entiers de 0 à 8.
Horizontal est l'entier 0, Vertical est l'entier 1.
Vous pourrez utiliser les fonctions suivantes :

// renvoie l'ID du joueur courant : 0 (blanc) or 1 (noir).
unsigned int get_current_player(struct board * b);

// Renvoie un entier selon ce qui se trouve à la position (column,line)
// sur le plateau b. Le résultat est -1 (rien), 0 (blanc) or 1 (noir).
int get_position(struct board* b, char column, char line);

// Renvoie un entier si il y a un mur de la position (column, line) vers la direction
// gauche (0), haut (1), droite (2), bas (3). Un mur (1), pas de mur (0).
int is_passable(const struct board* b, char column, char line, char direction);

// Bouge le pion sur la position (column,line)
void move_pawn(const struct board* b, char column, char line); 

// Renvoie le nombre de murs restant pour le joueur : player. 
unsigned int remaining_bridges(const struct board* b, unsigned int player);

// Renvoie (1) si il est possible de poser un mur a la position (column, line) 
// de direction (direction), (0) sinon.
int is_blockable(const struct board* b, char column, char line, char direction);

// Place un mur dans la colonne, ligne et à la direction correspondante.
void place_wall(const struct board* b, char column, char line, char direction);


************************************ Pour utiliser l'IAplayer ***************************************


Avant d'écrire son action, appuyer 2 fois sur "entrer" pour faire apparaitre un "Joueur X : "
Ecrivez la lettre de la colonne ('a'-'i'), puis le chiffre de la ligne ('1'-'9') 
puis '0' pour un mouvement, 'h' pour un mur horizontal, 'v' pour un mur vertical.
Puis pressez "Entrer".

Attention, il est extrèmement facile de se tromper dans son action, l'IA random devient un adversaire coriace.
Bonne chance !

En cas de mauvais mouvement, écrivez "reset" dans le terminal.

************************************* Compilation des tests *****************************************

Pour effectuer des tests grâce à des fichiers de coups symptomatiques, allez dans le dossier tst/.
Pour choisir le fichier .txt à lire, ouvrez le fichier "readgame.c" et remplacez à l'endroit de l'ouverture 
du fichier le nom présent par le nom souhaité.
Faites un "make".
Lancer "./test" et appuyer sur "Enter" pour passer au tour suivant.


