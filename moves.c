#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "board.h"

#define MAX_SIZE 100

int secureScanf(const char *message, int min, int max) {
    char buffer[MAX_SIZE];
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

int isAlly(char piece, int team){
    if (team) {
        return (piece == 'p' || piece == 'r' || piece == 'n' ||
                piece == 'b' || piece == 'q' || piece == 'k');
    }
    else {
        return (piece == 'P' || piece == 'R' || piece == 'N' ||
                piece == 'B' || piece == 'Q' || piece == 'K');
    }
}

int limits(int y, int x){
    return (x >=0 && x <=7 && y>=0 && y<=7);
}

void moveFinder(char board[8][8],int team);

void pawnMoves(char board[8][8],int x_pos,int y_pos,int direction, int op_line,int team){

    int mv;
    int mv1, mv2, mv3, mv4;
    int x1, y1, x2, y2, kx1, ky1, kx2, ky2;
    int can_move = 0;

    if (board[y_pos+direction][x_pos] == ' ' && limits(y_pos+direction,x_pos)){
        y1 = y_pos+direction;
        x1 = x_pos;
        printf("Vous pouvez déplacer (1) votre pion à la case x:%d et y:%d\n", x1,y1);
        mv1 = 1;
        can_move = 1;
    }
    if (board[y_pos+2*direction][x_pos] == ' ' && y_pos == op_line && limits(y_pos+2*direction,x_pos)){
        y2 = y_pos+2*direction;
        x2 = x_pos;
        printf("Vous pouvez déplacer (2) votre pion à la case x:%d et y:%d\n", x2,y2);
        mv2 = 1;
        can_move = 1;
    }
    if (board[y_pos+direction][x_pos-1] != ' ' && limits(y_pos+direction,x_pos-1)  && !isAlly(board[y_pos+direction][x_pos-1],team)){
        ky1 = y_pos+direction;
        kx1 = x_pos-1;
        printf("Vous pouvez tuer (3) la pièce %c à la case x:%d et y:%d\n",board[ky1][kx1], kx1,ky1);
        mv3 = 1;
        can_move = 1;
    }
    if (board[y_pos+direction][x_pos+1] != ' ' && limits(y_pos+direction,x_pos+1) && !isAlly(board[y_pos+direction][x_pos+1],team)){
        ky2 = y_pos+direction;
        kx2 = x_pos+1;
        printf("Vous pouvez tuer (4) la pièce %c à la case x:%d et y:%d\n",board[ky2][kx2],kx2,ky2);
        mv4 = 1;
        can_move = 1;
    }

    if(!can_move){
        printf("Votre pion ne peut pas se déplacer. Veuillez recommencer svp\n");
        moveFinder(board,team);
        return ;
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
                moveFinder(board,team);
            }
        break;
        case 2:
            if(mv2 == 1){
                board[y2][x2] = board[y_pos][x_pos];
                board[y_pos][x_pos]= ' ';
            }
            else{
                printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
                moveFinder(board,team);
            }
            break;

            case 3:
                if(mv3 == 1){
                    board[ky1][kx1] = board[y_pos][x_pos];
                    board[y_pos][x_pos]= ' ';
                }
                else{
                    printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
                    moveFinder(board,team);
                }
                break;
            case 4:
                if(mv4 == 1){
                    board[ky2][kx2] = board[y_pos][x_pos];
                    board[y_pos][x_pos]= ' ';
                }
                else{
                    printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
                    moveFinder(board,team);
                }
            break;
            default:
                printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
                moveFinder(board,team);
                break;
            }

}


void knightMoves(char board[8][8], int x_pos, int y_pos, int team) {

    int mv;
    int mv1, mv2, mv3, mv4, mv5, mv6, mv7, mv8;
    int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8;
    int can_move = 0;

    if (!isAlly(board[y_pos - 2][x_pos + 1],team) && y_pos - 2 >= 0 && x_pos + 1 <= 7) {
        x1 = x_pos + 1;
        y1 = y_pos - 2;
        printf("Vous pouvez déplacer (1) votre cavalier à la case x:%d et y:%d\n", x1, y1);
        mv1 = 1;
        can_move = 1;
    }
    if (!isAlly(board[y_pos - 2][x_pos - 1],team) && y_pos - 2 >= 0 && x_pos - 1 >= 0) {
        x2 = x_pos - 1;
        y2 = y_pos - 2;
        printf("Vous pouvez déplacer (2) votre cavalier à la case x:%d et y:%d\n", x2, y2);
        mv2 = 1;
        can_move = 1;
    }
    if (!isAlly(board[y_pos + 2][x_pos + 1],team) && y_pos + 2 <= 7 && x_pos + 1 <= 7) {
        x3 = x_pos + 1;
        y3 = y_pos + 2;
        printf("Vous pouvez déplacer (3) votre cavalier à la case x:%d et y:%d\n", x3, y3);
        mv3 = 1;
        can_move = 1;
    }
    if (!isAlly(board[y_pos + 2][x_pos - 1],team) && y_pos + 2 <= 7 && x_pos - 1 >= 0) {
        x4 = x_pos - 1;
        y4 = y_pos + 2;
        printf("Vous pouvez déplacer (4) votre cavalier à la case x:%d et y:%d\n", x4, y4);
        mv4 = 1;
        can_move = 1;
    }
    if (!isAlly(board[y_pos + 1][x_pos - 2],team) && y_pos + 1 <= 7 && x_pos - 2 >= 0) {
        x5 = x_pos - 2;
        y5 = y_pos + 1;
        printf("Vous pouvez déplacer (5) votre cavalier à la case x:%d et y:%d\n", x5, y5);
        mv5 = 1;
        can_move = 1;
    }
    if (!isAlly(board[y_pos + 1][x_pos + 2],team) && y_pos + 1 <= 7 && x_pos + 2 <= 7) {
        x6 = x_pos + 2;
        y6 = y_pos + 1;
        printf("Vous pouvez déplacer (6) votre cavalier à la case x:%d et y:%d\n", x6, y6);
        mv6 = 1;
        can_move = 1;
    }
    if (!isAlly(board[y_pos - 1][x_pos + 2],team) && y_pos - 1 >= 0 && x_pos + 2 <= 7) {
        x7 = x_pos + 2;
        y7 = y_pos - 1;
        printf("Vous pouvez déplacer (7) votre cavalier à la case x:%d et y:%d\n", x7, y7);
        mv7 = 1;
        can_move = 1;
    }
    if (!isAlly(board[y_pos - 1][x_pos - 2],team) && y_pos - 1 >= 0 && x_pos - 2 >= 0) {
        x8 = x_pos - 2;
        y8 = y_pos - 1;
        printf("Vous pouvez déplacer (8) votre cavalier à la case x:%d et y:%d\n", x8, y8);
        mv8 = 1;
        can_move = 1;
    }

    if(!can_move){
        printf("Votre cavalier ne peut pas se déplacer. Veuillez recommencer svp\n");
        moveFinder(board,team);
        return ;
    }

    mv = secureScanf("Choisissez la case sur laquelle vous diriger.\n", 1, 8);
    switch (mv) {
    case 1:
        if (mv1 == 1) {
          if(board[y1][x1] != ' '){
              printf("Vous avez mangé la pièce '%c'",board[y1][x1]);
          }
            board[y1][x1] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;
    case 2:
        if (mv2 == 1) {
            if(board[y2][x2] != ' '){
                printf("Vous avez mangé la pièce '%c'",board[y2][x2]);
            }
            board[y2][x2] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;

    case 3:
        if (mv3 == 1) {
            board[y3][x3] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;

    case 4:
        if (mv4 == 1) {
            board[y4][x4] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;

    case 5:
        if (mv5 == 1) {
            board[y5][x5] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;

    case 6:
        if (mv6 == 1) {
            board[y6][x6] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;
    case 7:
        if (mv7 == 1) {
            board[y7][x7] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;
    case 8:
        if (mv8 == 1) {
            board[y8][x8] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;
    }
}


void rookMoves(char board[8][8], int x_pos, int y_pos, int team){

    int y = y_pos;
    int x = x_pos;
    int count = 0;
    int x_array[50];
    int y_array[50];
    int index = 0;
    int mv;

    while (y+1 <=7 && !isAlly(board[y+1][x],team)){
        y++;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }
    }
    y=y_pos;
    x=x_pos;
     while (y-1 >= 0 && !isAlly(board[y-1][x],team)){
        y--;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }
    }
    y=y_pos;
    x=x_pos;
     while (x + 1 <=7 && !isAlly(board[y][x+1],team)){
        x++;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }
    }
    y=y_pos;
    x=x_pos;
     while (x - 1 >= 0 && !isAlly(board[y][x-1],team)){
        x--;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }
    }

    if(count == 0){
        printf("Vous ne pouvez pas déplacer cette pièce. Veuillez recommencer svp\n");
        moveFinder(board,team);
        return ;
    }
    else{

        for(int i=0; i<count; i++){
            printf("Vous pouvez déplacer (%d) votre tour à la case x:%d et y:%d\n",i+1, x_array[i], y_array[i]);
        }

        mv = secureScanf("Choisissez la case sur laquelle vous diriger.\n", 1, count+1);

        for(int j=0; j<count;j++){
            if(mv==j+1){
                y = y_array[j];
                x = x_array[j];
                board[y][x] = board[y_pos][x_pos];
                board[y_pos][x_pos] = ' ';
                break;
            }
        }
    }
}

void bishopMoves(char board[8][8],int x_pos, int y_pos, int team){

    int y = y_pos;
    int x = x_pos;
    int count = 0;
    int x_array[50];
    int y_array[50];
    int index = 0;
    int mv;

    while(!isAlly(board[y+1][x+1], team) && y+1 <= 7 && x+1 <= 7){
        y++;
        x++;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }
    }

    y = y_pos;
    x = x_pos;

    while(!isAlly(board[y+1][x-1], team) && y+1 <= 7 && x-1 >= 0){
        y++;
        x--;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }
    }

    y = y_pos;
    x = x_pos;

    while(!isAlly(board[y-1][x+1], team) && y-1 >= 0 && x+1 <= 7){
        y--;
        x++;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }
    }

    y = y_pos;
    x = x_pos;

    while(!isAlly(board[y-1][x-1], team) && y-1 >= 0 && x-1 >= 0){
        y--;
        x--;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }    
    }

    if(count == 0){
        printf("Vous ne pouvez pas déplacer cette pièce. Veuillez recommencer svp\n");
        moveFinder(board,team);
        return ;
    }
    else{

        for(int i=0; i<count; i++){
            printf("Vous pouvez déplacer (%d) votre fou à la case x:%d et y:%d\n",i+1, x_array[i], y_array[i]);
        }

        mv = secureScanf("Choisissez la case sur laquelle vous diriger.\n", 1, count+1);

        for(int j=0; j<count;j++){
            if(mv==j+1){
                y = y_array[j];
                x = x_array[j];
                board[y][x] = board[y_pos][x_pos];
                board[y_pos][x_pos] = ' ';
                break;
            }
        }
    }
}

void queenMoves(char board[8][8], int x_pos, int y_pos, int team){
    int y = y_pos;
    int x = x_pos;
    int count = 0;
    int x_array[50];
    int y_array[50];
    int index = 0;
    int mv;

    while (y+1 <=7 && !isAlly(board[y+1][x],team)){
        y++;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }
    }
    y=y_pos;
    x=x_pos;
     while (y-1 >= 0 && !isAlly(board[y-1][x],team)){
        y--;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }
    }
    y=y_pos;
    x=x_pos;
     while (x + 1 <=7 && !isAlly(board[y][x+1],team)){
        x++;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }
    }
    y=y_pos;
    x=x_pos;
     while (x - 1 >= 0 && !isAlly(board[y][x-1],team)){
        x--;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }
    }

     while(!isAlly(board[y+1][x+1], team) && y+1 <= 7 && x+1 <= 7){
        y++;
        x++;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }
    }

    y = y_pos;
    x = x_pos;

    while(!isAlly(board[y+1][x-1], team) && y+1 <= 7 && x-1 >= 0){
        y++;
        x--;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }
    }

    y = y_pos;
    x = x_pos;

    while(!isAlly(board[y-1][x+1], team) && y-1 >= 0 && x+1 <= 7){
        y--;
        x++;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }
    }

    y = y_pos;
    x = x_pos;

    while(!isAlly(board[y-1][x-1], team) && y-1 >= 0 && x-1 >= 0){
        y--;
        x--;
        y_array[index] = y;
        x_array[index] = x;
        index++;
        count++;
        if(board[y][x] != ' ' ){
            break;
        }    
    }

    if(count == 0){
        printf("Vous ne pouvez pas déplacer cette pièce. Veuillez recommencer svp\n");
        moveFinder(board,team);
        return ;
    }
    else{

        for(int i=0; i<count; i++){
            printf("Vous pouvez déplacer (%d) votre tour à la case x:%d et y:%d\n",i+1, x_array[i], y_array[i]);
        }

        mv = secureScanf("Choisissez la case sur laquelle vous diriger.\n", 1, count+1);

        for(int j=0; j<count;j++){
            if(mv==j+1){
                y = y_array[j];
                x = x_array[j];
                board[y][x] = board[y_pos][x_pos];
                board[y_pos][x_pos] = ' ';
                break;
            }
        }
    }
}

void kingMoves(char board[8][8], int x_pos, int y_pos, int team){
    int mv;
    int mv1, mv2, mv3, mv4, mv5, mv6, mv7, mv8;
    int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8;
    int can_move = 0;

    if (!isAlly(board[y_pos - 1][x_pos],team) && y_pos - 1 >= 0) {
        x1 = x_pos;
        y1 = y_pos - 1;
        printf("Vous pouvez déplacer (1) votre cavalier à la case x:%d et y:%d\n", x1, y1);
        mv1 = 1;
        can_move = 1;
    }
    if (!isAlly(board[y_pos - 1][x_pos - 1],team) && y_pos - 1 >= 0 && x_pos - 1 >=0) {
        x2 = x_pos - 1;
        y2 = y_pos + 1;
        printf("Vous pouvez déplacer (2) votre cavalier à la case x:%d et y:%d\n", x2, y2);
        mv2 = 1;
        can_move = 1;
    }
    if (!isAlly(board[y_pos - 1][x_pos + 1],team) && y_pos - 1 >= 0 && x_pos + 1 <= 7) {
        x3 = x_pos + 1;
        y3 = y_pos - 1;
        printf("Vous pouvez déplacer (3) votre cavalier à la case x:%d et y:%d\n", x3, y3);
        mv3 = 1;
        can_move = 1;
    }
    if (!isAlly(board[y_pos][x_pos - 1],team) && x_pos - 1 >= 0) {
        x4 = x_pos - 1;
        y4 = y_pos;
        printf("Vous pouvez déplacer (4) votre cavalier à la case x:%d et y:%d\n", x4, y4);
        mv4 = 1;
        can_move = 1;
    }
    if (!isAlly(board[y_pos][x_pos + 1],team) && x_pos + 1 <= 7) {
        x5 = x_pos + 1;
        y5 = y_pos;
        printf("Vous pouvez déplacer (5) votre cavalier à la case x:%d et y:%d\n", x5, y5);
        mv5 = 1;
        can_move = 1;
    }
    if (!isAlly(board[y_pos + 1][x_pos - 1],team) && y_pos + 1 <= 7 && x_pos - 1 >= 0) {
        x6 = x_pos - 1;
        y6 = y_pos + 1;
        printf("Vous pouvez déplacer (6) votre cavalier à la case x:%d et y:%d\n", x6, y6);
        mv6 = 1;
        can_move = 1;
    }
    if (!isAlly(board[y_pos + 1][x_pos],team) && y_pos + 1 <= 7) {
        x7 = x_pos;
        y7 = y_pos + 1;
        printf("Vous pouvez déplacer (7) votre cavalier à la case x:%d et y:%d\n", x7, y7);
        mv7 = 1;
        can_move = 1;
    }
    if (!isAlly(board[y_pos + 1][x_pos + 1],team) && y_pos + 1 <= 7 && x_pos + 1 <= 7) {
        x8 = x_pos + 1;
        y8 = y_pos + 1;
        printf("Vous pouvez déplacer (8) votre cavalier à la case x:%d et y:%d\n", x8, y8);
        mv8 = 1;
        can_move = 1;
    }

    if(!can_move){
        printf("Votre roi ne peut pas se déplacer. Veuillez recommencer svp\n");
        moveFinder(board,team);
        return ;
    }

    mv = secureScanf("Choisissez la case sur laquelle vous diriger.\n", 1, 8);
    switch (mv) {
    case 1:
        if (mv1 == 1) {
          if(board[y1][x1] != ' '){
              printf("Vous avez mangé la pièce '%c'",board[y1][x1]);
          }
            board[y1][x1] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;
    case 2:
        if (mv2 == 1) {
            if(board[y2][x2] != ' '){
                printf("Vous avez mangé la pièce '%c'",board[y2][x2]);
            }
            board[y2][x2] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;

    case 3:
        if (mv3 == 1) {
            board[y3][x3] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;

    case 4:
        if (mv4 == 1) {
            board[y4][x4] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;

    case 5:
        if (mv5 == 1) {
            board[y5][x5] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;

    case 6:
        if (mv6 == 1) {
            board[y6][x6] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;
    case 7:
        if (mv7 == 1) {
            board[y7][x7] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;
    case 8:
        if (mv8 == 1) {
            board[y8][x8] = board[y_pos][x_pos];
            board[y_pos][x_pos] = ' ';
        } else {
            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
            moveFinder(board,team);
            return ;
        }
        break;
    }
}

void moveFinder(char board[8][8], int team){

        int x_pos,y_pos;
        
        printf("Quelle pièce voulez-vous déplacer ?\nDonnez ses coordonées:\n");
        x_pos = secureScanf("Abscisse:",0,7);
        y_pos = secureScanf("Ordonnée:",0,7);
        
        char piece = board[y_pos][x_pos];
        printf("Tu as choisi de déplacer un '%c'\n",piece);
        
        switch(piece){
            case 'p':
                if(team == 0){
                    printf("Vous pouvez uniquement déplacer vos pions\n");
                    moveFinder(board,team);
                    return ;
                }
                pawnMoves(board,x_pos,y_pos,-1, 6, team);
            break;
            case 'P':
                if(team == 1){
                    printf("Vous pouvez uniquement déplacer vos pions\n");
                    moveFinder(board,team);
                    return ;
                }
                pawnMoves(board,x_pos,y_pos, 1, 1, team);
            break;
            case 'n':
                if(team == 0){
                    printf("Vous pouvez uniquement déplacer vos pions\n");
                    moveFinder(board,team);
                    return ;
                }
                knightMoves(board,x_pos,y_pos,team);
            break;
            case 'N':
                if(team == 1){
                    printf("Vous pouvez uniquement déplacer vos pions\n");
                    moveFinder(board,team);
                    return ;
                }
                knightMoves(board,x_pos,y_pos,team);
            break;

            case 'r':
                if (team == 0){
                    printf("Vous pouvez uniquement déplacer vos pions\n");
                    moveFinder(board,team);
                    return ;
                }
                rookMoves(board,x_pos,y_pos,team);
            break;

            case 'R':
                if(team == 1){
                    printf("Vous pouvez uniquement déplacer vos pions\n");
                    moveFinder(board,team);
                    return ;
                }
                rookMoves(board,x_pos,y_pos,team);
            break;

            case 'b':
                if (team == 0){
                    printf("Vous pouvez uniquement déplacer vos pions\n");
                    moveFinder(board,team);
                    return ;
                }
                bishopMoves(board,x_pos,y_pos,team);
            break;

            case 'B':
                if(team == 1){
                    printf("Vous pouvez uniquement déplacer vos pions\n");
                    moveFinder(board,team);
                    return ;
                }
                bishopMoves(board,x_pos,y_pos,team);
            break;

            case 'q':
                if (team == 0){
                    printf("Vous pouvez uniquement déplacer vos pions\n");
                    moveFinder(board,team);
                    return ;
                }
                queenMoves(board,x_pos,y_pos,team);
            break;

            case 'Q':
                if(team == 1){
                    printf("Vous pouvez uniquement déplacer vos pions\n");
                    moveFinder(board,team);
                    return ;
                }
                queenMoves(board,x_pos,y_pos,team);
            break;

            case 'k':
                if (team == 0){
                    printf("Vous pouvez uniquement déplacer vos pions\n");
                    moveFinder(board,team);
                    return ;
                }
                kingMoves(board,x_pos,y_pos,team);
            break;

            case 'K':
                if(team == 1){
                    printf("Vous pouvez uniquement déplacer vos pions\n");
                    moveFinder(board,team);
                    return ;
                }
                kingMoves(board,x_pos,y_pos,team);
            break;
                
            default:
                printf("Il n'y a pas de pièce sur cette case.\nChoisissez une autre case.\n");
                moveFinder(board,team);
            break;
        }
    }