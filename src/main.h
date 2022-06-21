#ifndef _MAIN_H_
#define _MAIN_H_
#include<string.h>
// chess
#define black   49 // '1'  ascii is 49
#define white   48 // '0'  ascii is 48
#define noChess 46 // '.'  ascii is 46
extern char pc, rival;
// board
#define s 2
#define board_size 19
extern char chessboard[board_size][board_size];
// declare func
int firstMove(char chess);
int MinMax_init();

#endif