#ifndef MOVES_H
#define MOVES_H

int secureScanf(const char *message, int min, int max);
void bigPawnMoves(char board[8][8],int x_pos,int y_pos);
void smallPawnMoves(char board[8][8],int x_pos,int y_pos);
void knightMoves(char board[8][8],int x_pos,int y_pos);
void moveFinder(char board[8][8]);

#endif