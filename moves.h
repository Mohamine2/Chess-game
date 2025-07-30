#ifndef MOVES_H
#define MOVES_H

int secureScanf(const char *message, int min, int max);
void pawnMoves(char board[8][8],int x_pos,int y_pos,int direction, int op_line,int team);
void knightMoves(char board[8][8],int x_pos,int y_pos,int team);
void rookMoves(char board[8][8], int x_pos, int y_pos, int team);
void bishopMoves(char board[8][8],int x_pos, int y_pos, int team);
void queenMoves(char board[8][8], int x_pos, int y_pos, int team);
void kingMoves(char board[8][8], int x_pos, int y_pos, int team);
void moveFinder(char board[8][8],int team);
int isAlly(char piece, int team);
int limits(int y, int x);

#endif