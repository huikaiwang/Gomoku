#include<stdio.h>
#include"main.h"

char pc = noChess, rival = noChess;
char chessboard[board_size][board_size] = {};

int main(int argc, char *argv[]){
    // check chess color
    if(strcmp(argv[1],"Black") == 0){
        pc = black;
        rival = white;
    }
    else if(strcmp(argv[1],"White") == 0){
        pc = white;
        rival = black;
    }
    else return -1;

    char Alphabet[board_size] = {'A','B','C','D','E','F','G','H','I','J',
                                    'K','L','M','N','O','P','Q','R','S'};
    // get chessboard
    int i=0,j=0,chessNum=0,pos=0;
    for(i=0;i<board_size;i++){
        for(j=0;j<board_size;j++){
            scanf(" %c", &chessboard[i][j]);
            if(chessboard[i][j]!=noChess) chessNum+=1;
        }
    }
    if(chessNum<=1) 
        pos = firstMove(pc); // first move
    else 
        pos = MinMax_init(); // x = pos%board_size, y = pos/board_size

    printf("%c,%d\n",Alphabet[pos/board_size],(pos%board_size)+1);

    return 0;
}
