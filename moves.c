#include <stdio.h>

void moveFinder(char board[8][8]){
        int mv;
        int mv1,mv2,mv3,mv4;
        int x1,y1,x2,y2,kx1,ky1,kx2,ky2;
        int x_pos,y_pos;
        
        printf("Quelle pièce voulez-vous déplacer ?\nDonnez ses coordonées:\n");
        printf("Abscisse: ");
        scanf(" %d",&x_pos);
        if(x_pos <0 || x_pos >7){
            do{
                printf("Votre coordonnée ne correspond pas aux limites de l'échiquier.\nVeuillez entrer une coordonnée valide.\n");
                scanf(" %d",&x_pos);
            }while(x_pos <0 || x_pos >7);
        }
        printf("Ordonnée: ");
        scanf(" %d",&y_pos);
        if(y_pos <0 || y_pos >7){
            do{
                printf("Votre coordonnée ne correspond pas aux limites de l'échiquier.\nVeuillez entrer une coordonnée valide.\n");
                scanf(" %d",&y_pos);
            }while(y_pos <0 || y_pos >7);
        }
        char piece = board[y_pos][x_pos];
        printf("Tu as choisi de déplacer un '%c'\n",piece);
        
        switch(piece){
            case ' ':
                printf("Il n'y a pas de pièce sur cette case.\nChoisissez une autre case.\n");
                moveFinder(board);
                break;
            case 'P':
                if (board[y_pos+1][x_pos] == ' ' && y_pos+1 >= 0 && x_pos >= 0){
                    y1 = y_pos+1;
                    printf("Vous pouvez déplacer (1) votre pion à la case x:%d et y:%d\n", x_pos,y1);
                    mv1 = 1;
                }
                if (board[y_pos+2][x_pos] == ' ' && y_pos == 1 && y_pos+2 >= 0 && x_pos >= 0){
                    y2 = y_pos+2;
                    printf("Vous pouvez déplacer (2) votre pion à la case x:%d et y:%d\n", x_pos,y2);
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
                break;
                
                case 'p':
                    if (board[y_pos-1][x_pos] == ' ' && y_pos-1 >= 0 && x_pos >= 0){
                    y1 = y_pos-1;
                    printf("Vous pouvez déplacer (1) votre pion à la case x:%d et y:%d\n", x_pos,y1);
                    mv1 = 1;
                }
                if (board[y_pos-2][x_pos] == ' ' && y_pos == 6 && y_pos-2 >= 0 && x_pos >= 0){
                    y2 = y_pos-2;
                    printf("Vous pouvez déplacer (2) votre pion à la case x:%d et y:%d\n", x_pos,y2);
                    mv2 = 1;
                }
                if (board[y_pos-1][x_pos-1] != ' ' && y_pos+1 >= 0 && x_pos-1 >= 0){
                    ky1 = y_pos-1;
                    kx1 = x_pos-1;
                    printf("Vous pouvez tuer (3) la pièce %c à la case x:%d et y:%d\n",board[ky1][kx1], kx1,ky1);
                    mv3 = 1;
                }
                if (board[y_pos-1][x_pos+1] != ' ' && y_pos+1 >= 0 && x_pos+1 >= 0){
                    ky2 = y_pos-1;
                    kx2 = x_pos+1;
                    printf("Vous pouvez tuer (4) la pièce %c à la case x:%d et y:%d\n",board[ky2][kx2],kx2,ky2);
                    mv4 = 1;
                }
                break;
        }
                printf("Choisissez la case sur laquelle vous diriger.\n");
                scanf(" %d",&mv);
                switch(mv){
                    case 1:
                        if(mv1 == 1){
                            board[y1][x_pos] = board[y_pos][x_pos];
                            board[y_pos][x_pos]= ' ';
                        }
                        else{
                            printf("Ce déplacement n'existe pas.\nVeuillez recommencer svp\n");
                            moveFinder(board);
                        }
                        break;
                    case 2:
                        if(mv2 == 1){
                            board[y2][x_pos] = board[y_pos][x_pos];
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
