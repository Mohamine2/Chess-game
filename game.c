#include <stdio.h>
#include "board.h"
#include "moves.h"

int main(){
    char board[8][8];
    initBoard(board);
    printBoard(board);
    for(int i=0;i<4;i++){
        moveFinder(board);
        printBoard(board);
    }
    return 0;
}