#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define LIGNE 7
#define COLONNE 7

void joueur();
void ran();
void ai_run();

int Grille [LIGNE][COLONNE];
int player = 1;
int nbr = 0;
int premiere_partie = 0;

void menu(){
  printf("\n\n---menu---\n\n");
  printf("a. joueur vs jouer\n");
  printf("b. joueur vs random\n");
  printf("c. joueur vs Ordinateur\n\n");
  printf("votre choix ? ");
  char n;
  printf("\n");
 
  scanf(" %c", &n);
  switch(n){
  case 'a' : //appel fonction qui permet jouer avec une autre personne
    joueur();
    break;
  case 'b' :
    ran();
    break;
  case 'c' :
    ai_run();
    break;
  default :
    printf("le choix ne rentre correspond pas dans le menu\n");
    break;
  }
}

int win(int Grille[LIGNE][COLONNE], int player){
  int i,j;
  for(i=0; i < COLONNE;i++){
    for(j=0; j < LIGNE;j++){
      //horizontal
      if(i < 4){//i est inferieur a 4
	if(Grille[j][i]== player && Grille[j][i+1]== player && Grille[j][i+2]== player && Grille[j][i+3]== player)
	  return player;
      }
      //vertical
      if(j < 4){//j est inferieur a 4
	if(Grille[j][i]== player && Grille[j+1][i]== player && Grille[j+2][i]== player && Grille[j+3][i]== player)
	  return player;
      }
      //bas ver la droite
      if(j < COLONNE && i < LIGNE){//j doit etre inferieur a la colonne et i inferieur a la ligne
	if(Grille[j][i]== player && Grille[j+1][i+1]== player && Grille[j+2][i+2]== player && Grille[j+3][i+3]== player)
	  return player;
      }
      //bas ver la gauche
      if(j < 4 && i > 2){
	if(Grille[j][i]== player && Grille[j+1][i-1]== player && Grille[j+2][i-2]== player && Grille[j+3][i-3]== player)
	  return player;
      }
    }
  }
  return 0;
}

int ai_decide(int Grille[LIGNE][COLONNE],int player){
  int ia_player = 0;
  if(player == 1)
    ia_player = 2;
  else
    ia_player = 1;
  // colonne possible dans lesquelles jouer, contient la row dans lequel le coup peut être joué
  int possiblecol[COLONNE];
  int i;
  int j;
  int countcol = 0;
  for(i = 0; i < COLONNE; i++){
    possiblecol[i] = -1;
  }
  for(i = 0; i < COLONNE; i++){
    for(j = 0; j < LIGNE; j++){
      if(Grille[j][i] == 0){
	possiblecol[countcol++] = j;
	break;
      }
    }
  }
  // pour toute les cols possible,  on met le coup dans chaque position, si ca nous fait gagner alors on joue le coup
  for(i = 0; i < countcol; i++){
    if(possiblecol[i] != -1){
      Grille[possiblecol[i]][i] = player;
      if(win(Grille, player)){
	Grille[possiblecol[i]][i] = 0;
	printf("Can win !\n");
        return i+1;
      }
      else{
	Grille[possiblecol[i]][i] = 0;
      }
    }
  }
  // pour toute les cols possible,  on set le coup de l'autre joueur dans chaque position, si ca fait gagner l'autre joueur alors on bloque
  for(i = 0; i < countcol; i++){
    if(possiblecol[i] != -1){
      Grille[possiblecol[i]][i] = ia_player;
      if(win(Grille, ia_player)){
	Grille[possiblecol[i]][i] = 0;
	printf("Can block !\n");
        return i+1;
      }
      else{
	Grille[possiblecol[i]][i] = 0;
      }
    }
  }
  // play random
  int col = rand() % (countcol-1 + 1 - 0) + 0;
  printf("DECIDE %d\n",col);
  return col + 1;
}

int joueur_rand(){
  int i;
  i=(rand()%(COLONNE))+1;
  return i;
}

int play(int Grille[LIGNE][COLONNE], int player, int nbr){
  int i = 0;
  int pass = 0;
  while(i<COLONNE){
    if(Grille[i][nbr-1] == 0 && i < LIGNE){
      Grille[i][nbr-1] = player;
      pass = 1;
      break;
    }
    i++;
  }
  return pass;
}

void init_Grille(int Grille[LIGNE][COLONNE]){  //initialisation du tableau jeu
  int  i,j;
  for (i = 0; i < LIGNE; i++){
    for (j = 0; j < COLONNE; j++){
      Grille[i][j] = 0;
    }
  }
}

void afficher(int Grille[LIGNE][COLONNE]){  //afficher du tableau jeu
  int i,j;
  printf("\n     |---puissance 4---|\n");
  printf("\n  ----+---+---+---+---+---+---+\n");
  for(i=LIGNE-1; i>=0; i--){
    printf("%d |", i);
    for(j=0; j<COLONNE; j++){
      if(Grille[i][j] == 1)
        printf(" X |");
      if(Grille[i][j] == 2)
        printf(" O |");
      if(Grille[i][j]== 0)
        printf("   |");
    }
    printf("\n  ----+---+---+---+---+---+---+\n");
  }
  for(j=0; j<COLONNE; j++){
    printf("   %d",j+1);
  }
  printf("\n  -----------------------------\n");
}

void joueur(){ //joueur contre joueur
  int w=0;
  init_Grille(Grille);
  afficher(Grille);
 
  while(w==0){
    int nb;
    printf(" A tour du joueur %d : ", player);
    scanf(" %d",&nb);
    while(nb>COLONNE  || nb <= 0 ){
      printf("Le nombre ne rentre pas dans la grille,choisissez un nombre entre 1 et 7 ! ==> %d : ", nb);
      scanf(" %d",&nb);
    }
    while((play(Grille, player, nb) == 0) && (nb>COLONNE  || nb <= 0)){
      printf("Cette colonne est remplie, choissisez une autre que %d", nb);
      scanf(" %d",&nb);
    }
    afficher(Grille);
    w=win(Grille,player);
    if(player == 1){
      player = 2;
    }
    else{
      player = 1;
    }
  }
  printf(" le joueur %d a gagné \n ", w);
}

void ran(){ //joueur contre random
  int w=0;
  init_Grille(Grille);
  afficher(Grille);
 
  while(w==0){
    int nb;
    printf(" A tour du joueur %d : ", player);
    if(player == 1){
      scanf("%d",&nb);
      while(nb>COLONNE || nb <= 0){
        printf("Le nombre ne rentre pas dans la grille,choisissez un nombre entre 1 et 7 ! ==> %d : ", nb);
        scanf(" %d",&nb);
      }
    }
    else{
      nb =  joueur_rand();
    }
    while(play(Grille, player, nb) == 0  && (nb>COLONNE  || nb <= 0)){
      printf("Cette colonne est remplie, choissisez une autre que %d", nb);
      scanf(" %d",&nb);
    }
    afficher(Grille);
    w=win(Grille,player);
    if(player == 1){
      player = 2;
    }
    else{
      player = 1;
    }
  }
  printf(" le joueur %d a gagné \n ", w);
}

void ai_run(){ //joueur contre IA
  int w=0;
  init_Grille(Grille);
  afficher(Grille);

  while(w==0){ //int w=0;
    int nb;
    printf(" A tour du joueur %d : ", player);
    if(player == 1){
      scanf(" %d",&nb);
      while(nb>COLONNE  || nb <= 0){
        printf("Le nombre ne rentre pas dans la grille,choisissez un nombre entre 1 et 7 ! ==> %d : ", nb);
        scanf(" %d",&nb);
      }
    }
    else{
      nb = ai_decide(Grille,player);
    }
    while(play(Grille, player, nb) == 0){
      printf("Cette colonne est remplie, choissisez une autre que %d", nb);
      scanf(" %d",&nb);
    }
    afficher(Grille);
    w=win(Grille,player);
    if(player == 1){
      player = 2;
    }
    else{
      player = 1;
    }
  }
  printf(" le joueur %d a gagné \n ", w);
}

int rejouer(int Grille[LIGNE][COLONNE],int player,int nbr){
  // int player=1;
  if(premiere_partie == 0)
    printf("\n\nVoulez vous jouer ? (oui = 1 , non = 2)\n");
  else
    printf("\n\nVoulez vous rejouer ? (oui = 1 , non = 2)\n");
  scanf(" %d",&player);
  if(player == 1){
    return 1;
  }
  else{
    return 0;
  }
}

int main(){
  int test = rejouer(Grille, player, nbr);
  while(test == 1){
    menu();
    premiere_partie++;
  }
  return 0;
}
