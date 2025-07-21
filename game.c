#include <stdio.h>
#include "board.h"
#include "moves.h"

int main(){
    char board[8][8];
    initBoard(board);
    printBoard(board);
    while(1){
        printf("Joueurs minuscules:\n");
        moveFinder(board,1);
        printBoard(board);
        printf("Joueurs majuscules:\n");
        moveFinder(board,0);
        printBoard(board);
    }
    return 0;
}