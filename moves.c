#include <stdio.h>

void move(char board[8][8], int y_pos, int x_pos){
        int x_dest;
        int y_dest;
        char direction;
        scanf("%c",&direction);
        switch(direction){
            case 'z':
                y_dest = y_pos-1;
                board[y_dest][x_pos] = board[y_pos][x_pos];
                board[y_pos][x_pos]= ' ';
                break;
            case 's':
                y_dest = y_pos+1;
                board[y_dest][x_pos] = board[y_pos][x_pos];
                board[y_pos][x_pos]= ' ';
                break;
            case 'q':
                x_dest = x_pos-1;
                board[y_pos][x_dest] = board[y_pos][x_pos];
                board[y_pos][x_pos]= ' ';
                break;
            case 'd':
                x_dest = x_pos+1;
                board[y_pos][x_dest] = board[y_pos][x_pos];
                board[y_pos][x_pos]= ' ';
                break;
            default:
                printf("Mauvaise touche !\n");
        }
    }
