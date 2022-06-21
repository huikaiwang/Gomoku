#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include "main.h"
#include "gomoku.h"    

clock_t start, end;

int firstMove(char chess){
    if(chess==black)
        return 9+9*board_size; // chessboard center point
    else if(chess==white){
        int initWeight[board_size][board_size] =
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
            {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0},
            {0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0},
            {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0},
            {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0},
            {0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 0},
            {0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 0},
            {0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 0},
            {0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 0},
            {0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 0},
            {0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 0},
            {0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 0},
            {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0},
            {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0},
            {0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0},
            {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0},
            {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        };
        int i=0,j=0,weight=-1,bias=1;
        for(i=0;i<board_size;i++){
            for(j=0;j<board_size;j++){
                if(chessboard[i][j]!=noChess){
                    // find first black 
                    weight=initWeight[i][j];
                    break;
                }
            }
            if(weight!=-1) break; 
        }
        // now i,j is x's coordination
        if(weight==0) return 9+9*board_size;
        else if(weight>=6) bias=0;
        chess_queue sure_queue={.len=0};
        int N = i-1>0?i-1:0;
        int W = j-1>0?j-1:0;
        int S = i+1<board_size?i+1:i;
        int E = j+1<board_size?j+1:j;

        for(i=N;i<=S;i++){
            for(j=W;j<=E;j++){
                if(chessboard[i][j]==noChess){
                    if(initWeight[i][j]-weight>=bias){
                        sure_queue.chess[sure_queue.len].x = i;
                        sure_queue.chess[sure_queue.len].y = j;
                        sure_queue.len = sure_queue.len+1;   
                    }
                }
            }
        }
        srand(time(NULL));
        int k=(int)(rand()%sure_queue.len);
        int p=(sure_queue.chess[k].x) + (sure_queue.chess[k].y*board_size);
        return p;
    }

    return 0;
}

int MinMax_init(){
    start = clock();
    chess_queue option_queue;
    chess_queue sure_queue={.len=0};
    option_queue = moveGenerator(pc);
    
    int i=0, tmpScore=0, best=-inf;
    for(i=0;i<option_queue.len;i++){	
        chessboard[option_queue.chess[i].x][option_queue.chess[i].y] = pc;
        tmpScore = Min(1,option_queue.chess[i],-inf,inf); 
        chessboard[option_queue.chess[i].x][option_queue.chess[i].y] = noChess;	

        if(tmpScore>best){
            best = tmpScore;
            sure_queue.chess[0].x = option_queue.chess[i].x;
            sure_queue.chess[0].y = option_queue.chess[i].y;
            sure_queue.len=1;
        }
        else if(tmpScore==best){
            sure_queue.chess[sure_queue.len].x = option_queue.chess[i].x;
            sure_queue.chess[sure_queue.len].y = option_queue.chess[i].y;
            sure_queue.len = sure_queue.len+1;
        }
        end = clock();
        if((end-start)/CLOCKS_PER_SEC>=timeLimit){
            srand(time(NULL));
            int k=(int)(rand()%sure_queue.len);
            int p=(sure_queue.chess[k].x) + (sure_queue.chess[k].y*board_size);
            return p;
        }
    }
    if(sure_queue.len==0){
        int j=0;
        for(i=0;i<board_size;i++){
            for(j=0;j<board_size;j++){
                if(chessboard[i][j]==noChess){
                    sure_queue.chess[sure_queue.len].x = i;
                    sure_queue.chess[sure_queue.len].y = j;
                    sure_queue.len = sure_queue.len+1;
                }
            }
        }
    }
    srand(time(NULL));
    int k=(int)(rand()%sure_queue.len);
    int p=(sure_queue.chess[k].x) + (sure_queue.chess[k].y*board_size);
    return p;
}

int Min(int h,coordinate chess,int alpha,int beta){
    if(h>=depth || isWin(chess.x,chess.y,pc))
        return boardScore();

    chess_queue option_queue;
    option_queue = moveGenerator(rival);
    int i=0,best=inf,tmpScore=0;
    for(i=0;i<option_queue.len;i++){
        chessboard[option_queue.chess[i].x][option_queue.chess[i].y] = rival;
        tmpScore = Max(h+1,option_queue.chess[i],alpha,beta);
        chessboard[option_queue.chess[i].x][option_queue.chess[i].y] = noChess;

        if(tmpScore<best){
            best=tmpScore;
            if(best<beta){
                beta=best;
                if(alpha>=beta)
                    break;
            }
        }
        end = clock();
        if((end-start)/CLOCKS_PER_SEC>=timeLimit) return best;
    }
    return best;
}

int Max(int h,coordinate chess,int alpha,int beta){
    if(h>=depth || isWin(chess.x,chess.y,rival))
        return boardScore(); 

    chess_queue option_queue;
    option_queue = moveGenerator(pc);
    int i=0,best=-inf,tmpScore=0;
    for(i=0;i<option_queue.len;i++){
        chessboard[option_queue.chess[i].x][option_queue.chess[i].y] = pc;
        tmpScore = Min(h+1,option_queue.chess[i],alpha,beta);
        chessboard[option_queue.chess[i].x][option_queue.chess[i].y] = noChess;
        
        if(tmpScore>best){
            best=tmpScore;
            if(best>alpha){
                alpha=best;
                if(alpha>=beta)
                    break;
            }
        }
        end = clock();
        if((end-start)/CLOCKS_PER_SEC>=timeLimit) return best;
    }
    return best;
}

chess_queue moveGenerator(char chess){
    /*********************************************
        Four   = open fours
        SFour  = half open fours = sleepd fours
        Three  = open threes
        BThree = half open threes
        etc, ...
    **********************************************/
    // those queue diff base on chess type score
    chess_queue five = {.len=0};
    // pc
    chess_queue pc_Four = {.len=0};
    chess_queue pc_SFour = {.len=0};
    chess_queue pc_DThree = {.len=0}; // double open threes
    chess_queue pc_Three = {.len=0};
    chess_queue pc_Two = {.len=0};
    chess_queue pc_One = {.len=0}; // only one chess
    // rival
    chess_queue rival_Four = {.len=0};
    chess_queue rival_SFour = {.len=0};
    chess_queue rival_DThree = {.len=0}; // double open threes
    chess_queue rival_Three = {.len=0};
    chess_queue rival_Two = {.len=0};
    // final queue
    chess_queue queue = {.len=0};

    res score = {.pc_score=0, .rival_score=0};
    int i=0,j=0;
    for(i=0;i<board_size;i++){
        for(j=0;j<board_size;j++){
            if(chessboard[i][j]==noChess && has_neighbor(i,j)){
                score = eval_point(i,j,chess);
                if(score.pc_score>=fiveChess){
                    queue.chess[queue.len].x=i;
                    queue.chess[queue.len].y=j;
                    queue.len = queue.len+1;
                    return queue;
                }
                else if(score.rival_score>=fiveChess){
                    five.chess[five.len].x=i;
                    five.chess[five.len].y=j;
                    five.len = five.len+1;		
                }
                else if(score.pc_score>=openFours){
                    pc_Four.chess[pc_Four.len].x=i;
                    pc_Four.chess[pc_Four.len].y=j;
                    pc_Four.len = pc_Four.len+1;
                }
                else if(score.rival_score>=openFours){
                    rival_Four.chess[rival_Four.len].x=i;
                    rival_Four.chess[rival_Four.len].y=j;
                    rival_Four.len = rival_Four.len+1;
                }
                else if(score.pc_score>=half_openFours){
                    if(score.pc_score < (half_openFours+openThrees)){
                        // sleeped fours
                        pc_SFour.chess[pc_SFour.len].x=i;
                        pc_SFour.chess[pc_SFour.len].y=j;
                        pc_SFour.len = pc_SFour.len+1;
                    }
                    else{
                        pc_Four.chess[pc_Four.len].x=i;
                        pc_Four.chess[pc_Four.len].y=j;
                        pc_Four.len = pc_Four.len+1;
                    }
                }
                else if(score.rival_score>=half_openFours){
                    if(score.rival_score < (half_openFours+openThrees)){
                        // sleeped fours
                        rival_SFour.chess[rival_SFour.len].x=i;
                        rival_SFour.chess[rival_SFour.len].y=j;
                        rival_SFour.len = rival_SFour.len+1;
                    }
                    else{
                        rival_Four.chess[rival_Four.len].x=i;
                        rival_Four.chess[rival_Four.len].y=j;
                        rival_Four.len = rival_Four.len+1;
                    }
                }
                else if(score.pc_score>=dobule_OpenThrees){
                    pc_DThree.chess[pc_DThree.len].x=i;
                    pc_DThree.chess[pc_DThree.len].y=j;
                    pc_DThree.len = pc_DThree.len+1;
                }
                else if(score.rival_score>=dobule_OpenThrees){
                    rival_DThree.chess[rival_DThree.len].x=i;
                    rival_DThree.chess[rival_DThree.len].y=j;
                    rival_DThree.len = rival_DThree.len+1;
                }
                else if(score.pc_score>=openThrees){
                    pc_Three.chess[pc_Three.len].x=i;
                    pc_Three.chess[pc_Three.len].y=j;
                    pc_Three.len = pc_Three.len+1;
                }
                else if(score.rival_score>=openThrees){
                    rival_Three.chess[rival_Three.len].x=i;
                    rival_Three.chess[rival_Three.len].y=j;
                    rival_Three.len = rival_Three.len+1;
                }
                else if(score.pc_score>=openTwos){
                    pc_Two.chess[pc_Two.len].x=i;
                    pc_Two.chess[pc_Two.len].y=j;
                    pc_Two.len = pc_Two.len+1;
                }
                else if(score.rival_score>=openTwos){
                    rival_Two.chess[rival_Two.len].x=i;
                    rival_Two.chess[rival_Two.len].y=j;
                    rival_Two.len = rival_Two.len+1;
                }
                else if(score.pc_score>=openOnes){
                    pc_One.chess[pc_One.len].x=i;
                    pc_One.chess[pc_One.len].y=j;
                    pc_One.len = pc_One.len+1;
                }
            }
        }
    }
    if(five.len>0){
        for(i=0;i<five.len;i++){
            queue.chess[queue.len].x = five.chess[i].x;
            queue.chess[queue.len].y = five.chess[i].y;
            queue.len = queue.len+1;
        }
        return queue;
    }
    if(pc_Four.len>0){
        for(i=0;i<pc_Four.len;i++){
            queue.chess[queue.len].x = pc_Four.chess[i].x;
            queue.chess[queue.len].y = pc_Four.chess[i].y;
            queue.len = queue.len+1;
        }
        for(i=0;i<rival_Four.len;i++){
            queue.chess[queue.len].x = rival_Four.chess[i].x;
            queue.chess[queue.len].y = rival_Four.chess[i].y;
            queue.len = queue.len+1;
        }
        return queue;
    }
    if(rival_Four.len>0){
        for(i=0;i<rival_Four.len;i++){
            queue.chess[queue.len].x = rival_Four.chess[i].x;
            queue.chess[queue.len].y = rival_Four.chess[i].y;
            queue.len = queue.len+1;
        }
        for(i=0;i<pc_SFour.len;i++){
            queue.chess[queue.len].x = pc_SFour.chess[i].x;
            queue.chess[queue.len].y = pc_SFour.chess[i].y;
            queue.len = queue.len+1;
        }
        /*
        for(i=0;i<rival_SFour.len;i++){
            queue.chess[queue.len].x = rival_SFour.chess[i].x;
            queue.chess[queue.len].y = rival_SFour.chess[i].y;
            queue.len = queue.len+1;
        }			
        */
        return queue;
    }
    for(i=0;i<pc_DThree.len;i++){
        queue.chess[queue.len].x = pc_DThree.chess[i].x;
        queue.chess[queue.len].y = pc_DThree.chess[i].y;
        queue.len = queue.len+1;
    }
    for(i=0;i<rival_DThree.len;i++){
        queue.chess[queue.len].x = rival_DThree.chess[i].x;
        queue.chess[queue.len].y = rival_DThree.chess[i].y;
        queue.len = queue.len+1;
    }
    for(i=0;i<pc_SFour.len;i++){
        queue.chess[queue.len].x = pc_SFour.chess[i].x;
        queue.chess[queue.len].y = pc_SFour.chess[i].y;
        queue.len = queue.len+1;
    }
    for(i=0;i<rival_SFour.len;i++){
        queue.chess[queue.len].x = rival_SFour.chess[i].x;
        queue.chess[queue.len].y = rival_SFour.chess[i].y;
        queue.len = queue.len+1;
    }
    for(i=0;i<pc_Three.len;i++){
        queue.chess[queue.len].x = pc_Three.chess[i].x;
        queue.chess[queue.len].y = pc_Three.chess[i].y;
        queue.len = queue.len+1;
    }
    for(i=0;i<rival_Three.len;i++){
        queue.chess[queue.len].x = rival_Three.chess[i].x;
        queue.chess[queue.len].y = rival_Three.chess[i].y;
        queue.len = queue.len+1;
    }
    if(pc_DThree.len>0 || rival_DThree.len>0) return queue;

    if(queue.len+pc_Two.len>numLimit) pc_Two.len = numLimit-queue.len;
    for(i=0;i<pc_Two.len;i++){
        queue.chess[queue.len].x = pc_Two.chess[i].x;
        queue.chess[queue.len].y = pc_Two.chess[i].y;
        queue.len = queue.len+1;
    }
    if(queue.len>=numLimit) return queue;

    if(queue.len+rival_Two.len>numLimit) rival_Two.len = numLimit-queue.len;
    for(i=0;i<rival_Two.len;i++){
        queue.chess[queue.len].x = rival_Two.chess[i].x;
        queue.chess[queue.len].y = rival_Two.chess[i].y;
        queue.len = queue.len+1;
    }
    if(queue.len>=numLimit) return queue;

    if(queue.len+pc_One.len>numLimit) pc_One.len = numLimit-queue.len;
    for(i=0;i<pc_One.len;i++){
        queue.chess[queue.len].x = pc_One.chess[i].x;
        queue.chess[queue.len].y = pc_One.chess[i].y;
        queue.len = queue.len+1;
    }

    return queue;	
}

bool has_neighbor(int x, int y){
    // those alhabet represents direction
    int N = x-s>0?x-s:0;
    int W = y-s>0?y-s:0;
    int S = x+s<board_size?x+s:x;
    int E = y+s<board_size?y+s:y;

    int i=0,j=0;
    for(i=N;i<=S;i++){
        for(j=W;j<=E;j++){
            if(chessboard[i][j]!=noChess)
                return true;
        }
    }
    return false;
}

res eval_point(int x, int y, char chess){
    char rivalChess = chess==black?white:black;
    char dir[9];
    memset(dir,'x',sizeof(dir));
    res score={.pc_score=0, .rival_score=0};

    int i=0,j=0;
    for(i=1;i<5 && (x-i)>=0;i++)
        dir[4-i] = chessboard[x-i][y];
    for(i=1;i<5 && (x+i)<board_size;i++)
        dir[4+i] = chessboard[x+i][y];

    score.pc_score    += analysisLine(dir,chess);	
    score.rival_score += analysisLine(dir,rivalChess);

    memset(dir,'x',sizeof(dir));
    for(i=1;i<5 && (y-i)>=0;i++)
        dir[4-i] = chessboard[x][y-i];
    for(i=1;i<5 && (y+i)<board_size;i++)
        dir[4+i] = chessboard[x][y+i];

    score.pc_score    += analysisLine(dir,chess);	
    score.rival_score += analysisLine(dir,rivalChess);

    memset(dir,'x',sizeof(dir));
    for(i=1;i<5 && (x-i)>=0 && (y-i)>=0;i++)
        dir[4-i] = chessboard[x-i][y-i];
    for(i=1;i<5 && (x+i)<board_size && (y+i)<board_size;i++)
        dir[4+i] = chessboard[x+i][y+i];

    score.pc_score    += analysisLine(dir,chess);	
    score.rival_score += analysisLine(dir,rivalChess);

    memset(dir,'x',sizeof(dir));
    for(i=1;i<5 && (x-i)>=0 && (y+i)<board_size;i++)
        dir[4-i] = chessboard[x-i][y+i];
    for(i=1;i<5 && (x+i)<board_size && (y-i)>=0;i++)
        dir[4+i] = chessboard[x+i][y-i];

    score.pc_score    += analysisLine(dir,chess);	
    score.rival_score += analysisLine(dir,rivalChess);

    return score;
}

int analysisLine(char dir[], char chess){
    char rivalChess = chess==black?white:black;
    int lIndex=4,rIndex=4;
    while(lIndex>0){
        if(dir[lIndex-1] != chess) break;
        lIndex-=1;
    }
    while(rIndex<8){
        if(dir[rIndex+1] != chess) break;
        rIndex+=1;
    }

    int lRange=lIndex, rRange=rIndex;
    while(lRange>0){
        if(dir[lRange-1] == rivalChess || dir[lRange-1] == 'x') break;
        lRange-=1;
    }
    while(rRange<8){
        if(dir[rRange+1] == rivalChess || dir[rRange+1] == 'x') break;
        rRange+=1;
    }

    int range = rRange-lRange+1;
    if(range<5) return 0;

    int chessRange = rIndex-lIndex+1;
    if(chessRange>=5) return fiveChess;
    
    bool lEmpty=false, rEmpty=false;
    // e.g. chess = '1', rival = '0', x is space
    if(chessRange==4){ 
        // [x,1,1,1,1,x,x,x,x]
        if(dir[lIndex-1]==noChess) lEmpty=true;  
        if(dir[rIndex+1]==noChess) rEmpty=true;
        if(lEmpty && rEmpty) return openFours;
        else if(lEmpty || rEmpty) return half_openFours;
    }
    if(chessRange==3){
        // [x,x,1,1,1,x,x,x,x]
        int score=0;
        if(dir[lIndex-1]==noChess){
            if(dir[lIndex-2]==chess)
                score+=half_openFours;  // [1,x,1,1,1]
            lEmpty=true;
        }
        if(dir[rIndex+1]==noChess){
            if(dir[rIndex+2]==chess)
                score+=half_openFours; // [1,1,1,x,1]
            rEmpty=true;
        }
        if(score>0) return score;
        else if(lEmpty && rEmpty){
            if(range>5)
                return openThrees; // [x,1,1,1,x,x], [x,x,1,1,1,x]
            else 
                return half_openThress; // [0,x,1,1,1,x,0] 
        }
        else if(lEmpty || rEmpty)
            return half_openThress; // [0,1,1,1,x,x], [x,x,1,1,1,0]
    }
    if(chessRange==2){ 
        // [x,x,x,1,1,x,x,x,x] 
        int score=0; 
        if(dir[lIndex-1]==noChess){
            if(dir[lIndex-2]==chess){
                if(dir[lIndex-3]==noChess){
                    if(range>5)
                        score+=openThrees; // [x,1,x,1,1,x]
                    else 
                        score+=half_openThress; // [x,1,x,1,1,0]
                }
                else if(dir[lIndex-3]==chess)
                    score+=half_openFours; // [1,1,x,1,1]
                else
                    score+=half_openThress; // [0,1,x,1,1,x]
            }
            lEmpty=true;
        }
        if(dir[rIndex+1]==noChess){
            if(dir[rIndex+2]==chess){
                if(dir[rIndex+3]==noChess){
                    if(lEmpty) 
                        score+=openThrees; // [x,1,1,x,1,x]  
                    else 
                        score+=half_openThress; // [0,1,1,x,1,x]
                }
                else if(dir[rIndex+3]==chess)
                    score+=half_openFours; // [1,1,x,1,1]
                else
                    score+=half_openThress; // [x,1,1,x,1,0]
            }
            rEmpty=true;
        }
        if(score>0) return score;
        else if(lEmpty && rEmpty) return openTwos; // [x,1,1,x]
        else if(lEmpty || rEmpty) return half_openTwos; // [0,1,1,x], [x,1,1,0]
    }
    if(chessRange==1){ 
        // [x,x,x,x,1,x,x,x,x]
        int score=0;
        
        if(dir[lIndex-1]==noChess){
            if(dir[lIndex-2]==chess){
                if(dir[lIndex-3]==noChess){
                    if(dir[rIndex+1]==noChess) score+=openTwos; // [x,1,x,1,x] 
                    else score+=half_openTwos; // [x,1,x,1,0]
                }
                else if(dir[lIndex-3]==chess){
                    if(dir[lIndex-4]==noChess){
                        if(range>5)
                            score+=openThrees; // [x,1,1,x,1,x] 
                        else
                            score+=half_openThress;
                    }
                    else if(dir[lIndex-4]==chess)
                        score+=half_openFours; // [1,1,1,x,1]
                }
            }
            /*
            else if(dir[lIndex-2]==noChess){
                if(dir[lIndex-3]==chess && dir[lIndex-4]==noChess)
                    if(range>5) score+=openTwos; // [x,1,x,x,1,x]
            }
            */
           lEmpty=true;
        }
        if(dir[rIndex+1]==noChess){
            if(dir[rIndex+2]==chess){
                if(dir[rIndex+3]==noChess){
                   if(lEmpty) score+=openTwos; // [x,1,x,1,x]
                   else score+=half_openTwos; // [0,1,x,1,x]
                }
                else if(dir[rIndex+3]==chess){
                    if(dir[rIndex+4]==chess)
                        score+=half_openFours; // [1,x,1,1,1]
                    else if(dir[rIndex+4]==noChess){
                        if(range>5)
                            score+=openThrees; // [x,1,x,1,1,x]
                        else
                            score+=half_openThress;
                    }
                }
            }
            /*
            else if(dir[rIndex+2]==noChess){
                if(dir[rIndex+3]==chess && dir[rIndex+4]==noChess)
                    if(range>5) score+=openTwos; // [x,1,x,x,1,x]
            }
            */
        }
        return score;
    }
    return 0;
}

bool isWin(int x,int y,char chess){
    int i=0,number=1;

    for(i=1;i<5 && (x-i)>=0;i++){
        if(chessboard[x-i][y]==chess) number++;
        else break;
    }
    for(i=1;i<5 && (x+i)<board_size;i++){
        if(chessboard[x+i][y]==chess) number++;
        else break;
    }
    if(number>=5) 
        return true;

    number=1;
    for(i=1;i<5 && (y-i)>=0;i++){
        if(chessboard[x][y-i]==chess) number++;
        else break;
    }
    for(i=1;i<5 && (y+i)<board_size;i++){
        if(chessboard[x][y+i]==chess) number++;
        else break;
    }
    if(number>=5)
        return true;

    number=1;
    for(i=1;i<5 && (x-i)>=0 && (y-i)>=0;i++){
        if(chessboard[x-i][y-i]==chess) number++;
        else break;
    }
    for(i=1;i<5 && (x+i)<board_size && (y+i)<board_size;i++){
        if(chessboard[x+i][y+i]==chess) number++;
        else break;
    }
    if(number>=5)
        return true;

    number=1;
    for(i=1;i<5 && (x-i)>=0 && (y+i)<board_size;i++){
        if(chessboard[x-i][y+i]==chess) number++;
        else break;
    }
    for(i=1;i<5 && (x+i)<board_size && (y-i)>=0;i++){
        if(chessboard[x+i][y-i]==chess) number++;
        else break;
    }
    if(number>=5)
        return true;

    return false;
}

int boardScore(){
    char dir[board_size];
    int i=0,j=0,x=0,y=0,pcScore=0,rivalScore=0;

    for(i=0;i<board_size;i++){
        for(j=0;j<board_size;j++)
            dir[j]=chessboard[i][j]; // horizontal
        pcScore    += calc_score(dir,pc);
        rivalScore += calc_score(dir,rival);
    }
    for(i=0;i<board_size;i++){
        for(j=0;j<board_size;j++)
            dir[j]=chessboard[j][i]; // vertical
        pcScore    += calc_score(dir,pc);
        rivalScore += calc_score(dir,rival);
    }
    for(i=0;i<board_size;i++){
        memset(dir, 'x', sizeof(dir));
        for(x=i,y=0;(x<board_size)&&(y<board_size);x++,y++)
            dir[y]=chessboard[x][y]; // lower triangle
        pcScore    += calc_score(dir,pc);
        rivalScore += calc_score(dir,rival);
    }
    for(i=1;i<board_size;i++){
        memset(dir, 'x', sizeof(dir));
        for(x=board_size-1,y=i;(x>=0)&&(y<board_size);x--,y++)
            dir[y-i]=chessboard[x][y]; // reverse lower triangle
        pcScore    += calc_score(dir,pc);
        rivalScore += calc_score(dir,rival);
    }
    for(i=1;i<board_size;i++){
        memset(dir, 'x', sizeof(dir));
        for(x=0,y=i;(x<board_size)&&(y<board_size);x++,y++)
            dir[x]=chessboard[x][y]; // upper triangle
        pcScore    += calc_score(dir,pc);
        rivalScore += calc_score(dir,rival);
    }
    for(i=0;i<board_size;i++){
        memset(dir, 'x', sizeof(dir));
        for(x=0,y=i;(y>=0)&&(x<board_size);x++,y--)
            dir[x]=chessboard[x][y]; // reverse upper triangle
        pcScore    += calc_score(dir,pc);
        rivalScore += calc_score(dir,rival);
    }

    return pcScore-rivalScore;
}

int calc_score(char dir[],char chess){
    int i=1,num=0,empty=0,tmp=0;
	
    if(dir[0]==noChess) empty=1;
    else if(dir[0]==chess) num=1;
	
    while(i<board_size){
        if(dir[i]==chess) num+=1;
        else if(dir[i]==noChess){
            if(num==0) empty=1;
            else{
                tmp += scoreTable(num,empty+1);
                num=0;
                empty=1;
            }
        }
        else{
            tmp += scoreTable(num,empty);
            num=0;
            empty=0;
        }
        i+=1;
    }
    tmp += scoreTable(num,empty);
	
    return tmp;
}

int scoreTable(int num,int empty){
    if(num>=5) return fiveChess;
    else if(num==4){
        if(empty==2) return openFours;
        else if(empty==1) return openThrees; // revised sleeped fours
    }
    else if(num==3){
        if(empty==2) return openThrees;
        else if(empty==1) return half_openThress;
    }
    else if(num==2){
        if(empty==2) return openTwos;
        else if(empty==1) return half_openTwos;
    }
    else if(num==1 && empty==2) return openOnes;

    return 0;
}
