#include <stdio.h>
    
    void initBoard(char board[8][8]){
        char* black = "RNBQKBNR";
        char* white = "rnbqkbnr";
        
        for (int i=0; i<8; i++){
            board[0][i] = black[i];
            board[1][i] = 'P';
            board[6][i] = 'p';
            board[7][i] = white[i];
        }
        
        for (int i=2; i<6; i++){
            for(int j=0; j<8; j++){
               board[i][j] = ' '; 
            }
        }
    }
    
    void printBoard(char board[8][8]){
        printf("  a b c d e f g h\n");
        for(int i=0;i<8;i++){
            printf("%d ",8-i);
            for(int j=0;j<8;j++){
                printf("%c ",board[i][j]);
            }
            printf("%d\n", 8 - i);
        }
        printf("  a b c d e f g h\n");
    }
