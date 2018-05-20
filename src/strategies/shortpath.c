#include "../header/interface.h"
#include "../registry.h"

#include <stdio.h>
#include <stdlib.h>


#define ICI t[l][c]
#define HAUT t[l-1][c]
#define BAS t[l+1][c]
#define GAUCHE t[l][c-1]
#define DROITE t[l][c+1]
#define PHAUT is_passable(b,c,l,1)
#define PBAS is_passable(b,c,l,3)
#define PGAUCHE is_passable(b,c,l,0)
#define PDROITE is_passable(b,c,l,2)
struct board b;
void PlusCourtCheminRec(struct board* b,int t[9][9], char c, char l)  
{
  if(PHAUT)   //si on peut passer en haut
  {
    if(get_position(b,c,l-1)==-1)   //si ya pas de joueur
    {
      if(t[l-1][c]>t[l][c]+1 && l!=0)  //si  plus court
      {
	t[l-1][c]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c,l-1);
      }
    }
    else                                 //ya un joueur
    {
      if(l!=1 && t[l-2][c]>t[l][c]+1 && is_passable(b,c,l-1,1))  //si on peut sauter par dessus
      {
	t[l-2][c]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c,l-2);
      }
      if(c!=0 && t[l-1][c-1]>t[l][c]+1 && is_passable(b,c,l-1,0) && is_passable(b,c,l-1,1)==0) //si on peut sauter en haut a gauche
      {
	t[l-1][c-1]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c-1,l-1);
      }
      if(c!=8 && t[l-1][c+1]>t[l][c]+1 && is_passable(b,c,l-1,2) && is_passable(b,c,l-1,1)==0) //si on peut sauter en haut a droite
      {
	t[l-1][c+1]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c+1,l-1);
      }
    }
  }
 if(PBAS)   //si on peut passer en bas
  {
    if(get_position(b,c,l+1)==-1)   //si ya pas de joueur
    {
      if(t[l+1][c]>t[l][c]+1 && l!=8)  //si  plus court
      {
	t[l+1][c]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c,l+1);
      }
    }
    else                                 //ya un joueur
    {
      if(l!=7 && t[l+2][c]>t[l][c]+1 && is_passable(b,c,l+1,3))  //si on peut sauter par dessus
      {
	t[l+2][c]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c,l+2);
      }
      if(c!=0 && t[l+1][c-1]>t[l][c]+1 && is_passable(b,c,l+1,0) && is_passable(b,c,l+1,3)==0) //si on peut sauter en bas a gauche
      {
	t[l+1][c-1]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c-1,l+1);
      }
      if(c!=8 && t[l+1][c+1]>t[l][c]+1 && is_passable(b,c,l+1,2) && is_passable(b,c,l+1,1)==0) //si on peut sauter en bas a droite
      {
	t[l+1][c+1]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c+1,l+1);
      }
    }
  }
 if(PGAUCHE)   //si on peut passer a gauche
  {
    if(get_position(b,c-1,l)==-1)   //si ya pas de joueur
    {
      if(t[l][c-1]>t[l][c]+1 && c!=0)  //si  plus court
      {
	t[l][c-1]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c-1,l);
      }
    }
    else                                 //ya un joueur
    {
      if(c!=1 && t[l][c-2]>t[l][c]+1 && is_passable(b,c-1,l,0))  //si on peut sauter par dessus
      {
	t[l][c-2]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c-2,l);
      }
      if(l!=8 && t[l+1][c-1]>t[l][c]+1 && is_passable(b,c-1,l,3) && is_passable(b,c-1,l,0)==0) //si on peut sauter en bas a gauche
      {
	t[l+1][c-1]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c-1,l+1);
      }
      if(l!=0 && t[l-1][c-1]>t[l][c]+1 && is_passable(b,c-1,l,1) && is_passable(b,c-1,l,0)==0) //si on peut sauter en haut a gauche
      {
	t[l-1][c-1]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c-1,l-1);
      }
    }
  }
 if(PDROITE)   //si on peut passer a droite 
  {
    if(get_position(b,c+1,l)==-1)   //si ya pas de joueur
    {
      if(t[l][c+1]>t[l][c]+1 && c!=8)  //si  plus court
      {
	t[l][c+1]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c+1,l);
      }
    }
    else                                 //ya un joueur
    {
      if(c!=7 && t[l][c+2]>t[l][c]+1 && is_passable(b,c+1,l,2))  //si on peut sauter par dessus
      {
	t[l][c+2]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c+2,l);
      }
      if(l!=8 && t[l+1][c+1]>t[l][c]+1 && is_passable(b,c+1,l,3) && is_passable(b,c+1,l,2)==0) //si on peut sauter en bas a droite
      {
	t[l+1][c+1]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c+1,l+1);
      }
      if(l!=0 && t[l-1][c+1]>t[l][c]+1 && is_passable(b,c+1,l,1) && is_passable(b,c+1,l,2)==0) //si on peut sauter en haut a droite
      {
	t[l-1][c+1]=t[l][c]+1;
	PlusCourtCheminRec(b,t,c+1,l-1);
      }
    }
  }
}

int PlusCourtChemin(struct board *b, int player, int t[9][9])  //renvoie taille du plus court chemin+tableau des distances
{
  char c;
  char l;
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      t[i][j]=81;
      if(get_position(b,j,i)==player)
      {
	t[i][j]=0;
	c=j;
	l=i;
      }
    }
  }
  PlusCourtCheminRec(b,t,c,l);
  int ennemi=(player)?0:1;   
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      if(get_position(b,j,i)==ennemi)
	t[i][j]=81;
    }
  }
  int min=99;
  int a;
  a=(player==0)?0:8;
  for(int k=0;k<9;k++)
  {
    if(t[a][k]<min && get_position(b,k,a)==-1)
      min=t[a][k];
  }
  return min;
}


int RemonterChemin(struct board *b, int t[9][9],int c, int l)  //permet de remonter le plus court chemin pour savoir ou se déplacer
{
  if(PGAUCHE) 
  {
    if(GAUCHE==81)                     //player left
    {
      if(ICI==t[l][c-2]+1)             //double left
	if(is_passable(b,c-1,l,0))  
	  return 7;                  
      if(ICI==t[l+1][c-1]+1)           //bot left
	if(is_passable(b,c-1,l,3) && !is_passable(b,c-1,l,1))
	  return 10;
      if(ICI==t[l-1][c-1]+1)           //top left
	if(is_passable(b,c-1,l,1) && !is_passable(b,c-1,l,3))
	  return 9;
    }
    else                            //no player left
      if(ICI==GAUCHE+1)
	return 0;
  }
  if(PDROITE) 
  {
    if(DROITE==81)                     //player right
    {
      if(ICI==t[l][c+2]+1)             //double right
	if(is_passable(b,c+1,l,2))   
	  return 6;
      if(ICI==t[l+1][c+1]+1)           //bot right
	if(is_passable(b,c+1,l,3) && !is_passable(b,c+1,l,1))                   
	  return 11;
      if(ICI==t[l-1][c+1]+1)           //top right
	if(is_passable(b,c+1,l,1) && !is_passable(b,c+1,l,3))
	  return 8;
    }
    else                            //no player right
      if(ICI==DROITE+1)
	return 2;
  }
  if(PHAUT) 
  {
    if(HAUT==81)                     //player top
    {
      if(ICI==t[l-2][c]+1)           //double top
	if(is_passable(b,c,l-1,1))   
	  return 4;
      if(ICI==t[l-1][c-1]+1)  //top left
	if(is_passable(b,c,l-1,0) && !is_passable(b,c,l-1,2))
	  return 9;
      if(ICI==t[l-1][c+1]+1)  //top right
	if(is_passable(b,c,l-1,2) && !is_passable(b,c,l-1,0))
	    return 8;
    }
    else                            //no player top
      if(ICI==HAUT+1)
	return 1;
  }
  if(PBAS) 
  {
    if(BAS==81)                     //player bot
    {
      if(ICI==t[l+2][c]+1)          //double bot
	if(is_passable(b,c,l+1,3))  
	  return 5;
      if(ICI==t[l+1][c-1]+1)        //bot left
	if(is_passable(b,c,l+1,0) && !is_passable(b,c,l+1,2))
	  return 10;
      if(ICI==t[l+1][c+1]+1)  //bot right
	if(is_passable(b,c,l+1,2) && !is_passable(b,c,l+1,0))
	  return 11;
    }
    else                            //no player bot
      if(ICI==BAS+1)
	return 3;
  }
  printf("erreur\n");
  return -1;
}

void Bouge(struct board *b, int player, int t[9][9], int min)  
{
  //printf("Bouge\n");
  int sens;
  int l;
  int c=0;
  int rez=20;
  l=(player==0)?0:8;
  while(t[l][c]!=min)   //OK
    c++;
  while(t[l][c]!=1 && rez>0)
  {
    rez--;
    sens=RemonterChemin(b,t,c,l);
    if(sens==0) //gauche
      c--;
    if(sens==1)
      l--;
    if(sens==2)
      c++;
    if(sens==3)
      l++;
    if(sens==4)  //hh
      l=l-2;
    if(sens==5)  //bb
      l=l+2;
    if(sens==6)  //dd
      c=c+2;
    if(sens==7)  //gg
      c=c-2;
    if(sens==8)  //hd
    {
      l--;
      c++;
    }
    if(sens==9)  //hg
    {
      l--;
      c--;
    }
    if(sens==10)  //bg
    {
      l++;
      c--;
    }
    if(sens==11)  //bd
    {
      l++;
      c++;
    }
  }
  move_pawn(b, c, l);
}


void Main( struct board *PB)
{
  b=*PB;
  int moi,lui;
  moi=get_current_player(&b);   //joueur en bas =0, joueur en haut = 1
  lui= (moi==1)?0:1;    //lui = l'autre joueur
  int t[9][9];
  int monChemin,sonChemin;
  sonChemin=PlusCourtChemin(&b,lui,t);    //calcule de la taille de leur plus court chemin
  monChemin=PlusCourtChemin(&b,moi,t);


  if(monChemin<=sonChemin || remaining_bridges(&b,moi)==0 ) //si chemin +court ou plus de mur
  {
    Bouge(PB,moi,t,monChemin);
  }
  else //on place un mur
  {
    int difference,minimum;
    minimum=PlusCourtChemin(&b,lui,t)-PlusCourtChemin(&b,moi,t);
    int l, c;
    int d=-1;


     for(int i=0;i<9;i++)
     {
       for(int j=0;j<9;j++)
       {
	 b=*PB;
	 if(is_blockable(&b,j,i,1))  
	 {
	   place_wall(&b,j,i,1);
	   difference=PlusCourtChemin(&b,lui,t)-PlusCourtChemin(&b,moi,t);
	   if(difference>minimum)
	   {
	     c=j;
	     l=i;
	     d=1;
	     difference=minimum;
	   }
	 }
	 b=*PB;
	 if(is_blockable(&b,i,j,0))
	 {
	   place_wall(&b,i,j,0);
	   difference=PlusCourtChemin(&b,lui,t)-PlusCourtChemin(&b,moi,t);
	   if(difference>minimum)
	   {
	     c=i;
	     l=j;
	     d=0;
	     difference=minimum;
	   }
	 }
       }
     }   //on a trouvé le meilleur emplacement de mur
     if(d==-1) //si pas trouvé de mur
     {
       Bouge(PB,moi,t,monChemin);
     }
     else
       place_wall(PB,c,l,d);
  }
}
REGISTER_STRATEGY("ShortPath", Main);
