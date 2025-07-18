#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "board.h"

#define TAILLE_MAX 100

int secureScanf(const char *message, int min, int max) {
    char buffer[TAILLE_MAX];
    int valeur;
    char extra;

    while (1) {
        printf("%s ", message);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            fprintf(stderr, "Erreur de lecture.\n");
            exit(EXIT_FAILURE);
        }

        // Si sscanf lit autre chose qu’un entier seul → erreur
        if (sscanf(buffer, "%d %c", &valeur, &extra) != 1) {
            printf("Entrée invalide. Veuillez entrer un nombre entier.\n");
            continue;
        }

        // Si hors bornes → erreur
        if (valeur < min || valeur > max) {
            printf("Valeur hors limites (%d à %d).\n", min, max);
            continue;
        }

        return valeur;
    }
}

void moveFinder(char board[8][8]);

void bigPawnMoves(char board[8][8],int x_pos,int y_pos){

    int mv;
    int mv1, mv2, mv3, mv4;
    int x1, y1, x2, y2, kx1, ky1, kx2, ky2;

    if (board[y_pos+1][x_pos] == ' ' && y_pos+1 >= 0 && x_pos >= 0){
                    y1 = y_pos+1;
                    x1 = x_pos;
                    printf("Vous pouvez déplacer (1) votre pion à la case x:%d et y:%d\n", x1,y1);
                    mv1 = 1;
                }
                if (board[y_pos+2][x_pos] == ' ' && y_pos == 1 && y_pos+2 >= 0 && x_pos >= 0){
                    y2 = y_pos+2;
                    x2 = x_pos;
                    printf("Vous pouvez déplacer (2) votre pion à la case x:%d et y:%d\n", x2,y2);
                    mv2 = 1;
                }
                if (board[y_pos+1][x_pos-1] != ' ' && y_pos+1 >= 0 && x_pos-1 >= 0){
                    ky1 = y_pos+1;
                    kx1 = x_pos-1;
                    printf("Vous pouvez tuer (3) la pièce %c à la case x:%d et y:%d\n",board[ky1][kx1], kx1,ky1);
                    mv3 = 1;
                }
                if (board[y_pos+1][x_pos+1] != ' ' && y_pos+1 >= 0 && x_pos+1 >= 0){
                    ky2 = y_pos+1;
                    kx2 = x_pos+1;
                    printf("Vous pouvez tuer (4) la pièce %c à la case x:%d et y:%d\n",board[ky2][kx2],kx2,ky2);
                    mv4 = 1;
                }

                mv = secureScanf("Choisissez la case sur laquelle vous diriger.\n",1,4);
                switch(mv){
                    case 1:
                        if(mv1 == 1){
                            board[y1][x1] = board[y_pos][x_pos];
                            board[y_pos][x_pos]= ' ';
                        }
                        else{
                            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
                            moveFinder(board);
                        }
                        break;
                    case 2:
                        if(mv2 == 1){
                            board[y2][x2] = board[y_pos][x_pos];
                            board[y_pos][x_pos]= ' ';
                        }
                        else{
                            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
                            moveFinder(board);
                        }
                        break;

                    case 3:
                        if(mv3 == 1){
                            board[ky1][kx1] = board[y_pos][x_pos];
                            board[y_pos][x_pos]= ' ';
                        }
                        else{
                            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
                            moveFinder(board);
                        }
                        break;
                    case 4:
                    if(mv4 == 1){
                        board[ky2][kx2] = board[y_pos][x_pos];
                        board[y_pos][x_pos]= ' ';
                    }
                    else{
                            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
                            moveFinder(board);
                    }
                    break;
                    default:
                        printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
                        moveFinder(board);
                }

}

void smallPawnMoves(char board[8][8],int x_pos,int y_pos){

    int mv;
    int mv1, mv2, mv3, mv4;
    int x1, y1, x2, y2, kx1, ky1, kx2, ky2;

    if (board[y_pos-1][x_pos] == ' ' && y_pos-1 >= 0){
                    y1 = y_pos-1;
                    x1 = x_pos;
                    printf("Vous pouvez déplacer (1) votre pion à la case x:%d et y:%d\n", x1,y1);
                    mv1 = 1;
                }
                if (board[y_pos-2][x_pos] == ' ' && y_pos == 6 && y_pos-2 >= 0){
                    y2 = y_pos-2;
                    x2 = x_pos;
                    printf("Vous pouvez déplacer (2) votre pion à la case x:%d et y:%d\n", x2,y2);
                    mv2 = 1;
                }
                if (board[y_pos-1][x_pos-1] != ' ' && y_pos+1 <= 7 && x_pos-1 >= 0){
                    ky1 = y_pos-1;
                    kx1 = x_pos-1;
                    printf("Vous pouvez tuer (3) la pièce %c à la case x:%d et y:%d\n",board[ky1][kx1], kx1,ky1);
                    mv3 = 1;
                }
                if (board[y_pos-1][x_pos+1] != ' ' && y_pos+1 <= 7 && x_pos+1 <= 7){
                    ky2 = y_pos-1;
                    kx2 = x_pos+1;
                    printf("Vous pouvez tuer (4) la pièce %c à la case x:%d et y:%d\n",board[ky2][kx2],kx2,ky2);
                    mv4 = 1;
                }

    mv = secureScanf("Choisissez la case sur laquelle vous diriger.\n",1,4);
                switch(mv){
                    case 1:
                        if(mv1 == 1){
                            board[y1][x1] = board[y_pos][x_pos];
                            board[y_pos][x_pos]= ' ';
                        }
                        else{
                            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
                            moveFinder(board);
                        }
                        break;
                    case 2:
                        if(mv2 == 1){
                            board[y2][x2] = board[y_pos][x_pos];
                            board[y_pos][x_pos]= ' ';
                        }
                        else{
                            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
                            moveFinder(board);
                        }
                        break;

                    case 3:
                        if(mv3 == 1){
                            board[ky1][kx1] = board[y_pos][x_pos];
                            board[y_pos][x_pos]= ' ';
                        }
                        else{
                            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
                            moveFinder(board);
                        }
                        break;
                    case 4:
                    if(mv4 == 1){
                        board[ky2][kx2] = board[y_pos][x_pos];
                        board[y_pos][x_pos]= ' ';
                    }
                    else{
                            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
                            moveFinder(board);
                    }
                    break;
                    default:
                        printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
                        moveFinder(board);
                }
}

void knightMoves(char board[8][8],int x_pos, int y_pos) {

  int mv;
  int mv1, mv2, mv3, mv4, mv5, mv6, mv7, mv8;
  int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8;

  if (board[y_pos - 2][x_pos + 1] == ' ' && y_pos - 2 >= 0 && x_pos + 1 <= 7) {
    x1 = x_pos + 1;
    y1 = y_pos - 2;
    printf("Vous pouvez déplacer (1) votre pion à la case x:%d et y:%d\n", x1, y1);
    mv1 = 1;
  }
  if (board[y_pos - 2][x_pos - 1] == ' ' && y_pos - 2 >= 0 && x_pos - 1 >= 0) {
    x2 = x_pos - 1;
    y2 = y_pos - 2;
    printf("Vous pouvez déplacer (2) votre pion à la case x:%d et y:%d\n", x2, y2);
    mv2 = 1;
  }
  if (board[y_pos + 2][x_pos + 1] == ' ' && y_pos + 2 <= 7 && x_pos + 1 <= 7) {
    x3 = x_pos + 1;
    y3 = y_pos + 2;
    printf("Vous pouvez déplacer (3) votre pion à la case x:%d et y:%d\n", x3, y3);
    mv3 = 1;
  }
  if (board[y_pos + 2][x_pos - 1] == ' ' && y_pos + 2 <= 7 && x_pos - 1 >= 0) {
    x4 = x_pos - 1;
    y4 = y_pos + 2;
    printf("Vous pouvez déplacer (4) votre pion à la case x:%d et y:%d\n", x4, y4);
    mv4 = 1;
  }
  if (board[y_pos + 1][x_pos - 2] == ' ' && y_pos + 1 <= 7 && x_pos - 2 >= 0) {
    x5 = x_pos - 2;
    y5 = y_pos + 1;
    printf("Vous pouvez déplacer (5) votre pion à la case x:%d et y:%d\n", x5, y5);
    mv5 = 1;
  }
  if (board[y_pos + 1][x_pos + 2] == ' ' && y_pos + 1 <= 7 && x_pos + 2 <= 7) {
    x6 = x_pos + 2;
    y6 = y_pos + 1;
    printf("Vous pouvez déplacer (6) votre pion à la case x:%d et y:%d\n", x6, y6);
    mv6 = 1;
  }
  if (board[y_pos - 1][x_pos + 2] == ' ' && y_pos - 1 >= 0 && x_pos + 2 <= 7) {
    x7 = x_pos + 2;
    y7 = y_pos - 1;
    printf("Vous pouvez déplacer (7) votre pion à la case x:%d et y:%d\n", x7, y7);
    mv7 = 1;
  }
  if (board[y_pos - 1][x_pos - 2] == ' ' && y_pos - 1 >= 0 && x_pos - 2 >= 0) {
    x8 = x_pos - 2;
    y8 = y_pos - 1;
    printf("Vous pouvez déplacer (8) votre pion à la case x:%d et y:%d\n", x8, y8);
    mv8 = 1;
  }

  mv = secureScanf("Choisissez la case sur laquelle vous diriger.\n", 1, 8);
  switch (mv) {
  case 1:
    if (mv1 == 1) {
      board[y1][x1] = board[y_pos][x_pos];
      board[y_pos][x_pos] = ' ';
    } else {
      printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
      moveFinder(board);
    }
    break;
  case 2:
    if (mv2 == 1) {
      board[y2][x2] = board[y_pos][x_pos];
      board[y_pos][x_pos] = ' ';
    } else {
      printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
      moveFinder(board);
    }
    break;

  case 3:
    if (mv3 == 1) {
      board[y3][x3] = board[y_pos][x_pos];
      board[y_pos][x_pos] = ' ';
    } else {
      printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
      moveFinder(board);
    }
    break;

  case 4:
    if (mv4 == 1) {
      board[y4][x4] = board[y_pos][x_pos];
      board[y_pos][x_pos] = ' ';
    } else {
      printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
      moveFinder(board);
    }
    break;

  case 5:
    if (mv5 == 1) {
      board[y5][x5] = board[y_pos][x_pos];
      board[y_pos][x_pos] = ' ';
    } else {
      printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
      moveFinder(board);
    }
    break;

  case 6:
    if (mv6 == 1) {
      board[y6][x6] = board[y_pos][x_pos];
      board[y_pos][x_pos] = ' ';
    } else {
      printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
      moveFinder(board);
    }
    break;
  case 7:
    if (mv7 == 1) {
      board[y7][x7] = board[y_pos][x_pos];
      board[y_pos][x_pos] = ' ';
    } else {
      printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
      moveFinder(board);
    }
    break;
  case 8:
    if (mv8 == 1) {
      board[y8][x8] = board[y_pos][x_pos];
      board[y_pos][x_pos] = ' ';
    } else {
      printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
      moveFinder(board);
    }
    break;
  default:
    printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
    moveFinder(board);
  }

}

void moveFinder(char board[8][8]){

        int x_pos,y_pos;
        
        printf("Quelle pièce voulez-vous déplacer ?\nDonnez ses coordonées:\n");
        x_pos = secureScanf("Abscisse:",0,7);
        y_pos = secureScanf("Ordonnée:",0,7);
        
        char piece = board[y_pos][x_pos];
        printf("Tu as choisi de déplacer un '%c'\n",piece);
        
        switch(piece){
            case 'P':
                bigPawnMoves(board,x_pos,y_pos);
            break;
                
            case 'p':
                smallPawnMoves(board,x_pos,y_pos);
            break;

            case 'n':
            case 'N':
                knightMoves(board,x_pos,y_pos);
            break;
                
            default:
                printf("Il n'y a pas de pièce sur cette case.\nChoisissez une autre case.\n");
                moveFinder(board);
                break;
        }
    }