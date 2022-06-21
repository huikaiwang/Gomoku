#ifndef _GOMOKU_H_
#define _GOMOKU_H_

// chess number & game time limit
#define numLimit 25
#define timeLimit 14
// tree max height
#define depth 6

// declare score type
typedef enum{
    inf               = 1000000000,
    fiveChess         = 16000000,
    openFours         = 800000,
    half_openFours    = 40000,
    dobule_OpenThrees = 4000,
    openThrees        = 2000,
    half_openThress   = 100,
    openTwos          = 100,
    half_openTwos     = 5,
    openOnes          = 5
}scoreType;
// related struct 
typedef struct{
    int x;
    int y;
}coordinate;

typedef struct{
    coordinate chess[board_size*board_size];
    int len;
}chess_queue;

typedef struct{
    int pc_score;
    int rival_score;
}res;

// declare func
bool has_neighbor(int x, int y);
bool isWin(int x,int y,char chess);
int boardScore();
int scoreTable(int num,int empty);
int calc_score(char dir[],char chess);
int analysisLine(char dir[], char chess);
int Min(int h,coordinate chess,int alpha,int beta);
int Max(int h,coordinate chess,int alpha,int beta);
res eval_point(int x, int y, char chess);
chess_queue moveGenerator(char chess);

#endif
