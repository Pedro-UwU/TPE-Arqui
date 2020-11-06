#include <chess.h>

static char *figures[PIECES_AMOUNT]={"king","queen","bishop","knight","rook","pawn"};

static int board[SQUARES][SQUARES] ={
    {5,4,3,1,2,3,4,5},
    {6,6,6,6,6,6,6,6},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {-6,-6,-6,-6,-6,-6,-6,-6},
    {-5,-4,-3,-2,-1,-3,-4,-5}
    };

static char pieces[PIECES_AMOUNT][PIECES_SIZE][PIECES_SIZE] = {
    {
        {'/','/','/','/','/','/','/','/'},
        {'/','/','/','#','.','#','/','/'},
        {'/','/','#','.','.','.','#','/'},
        {'/','/','/','#','.','#','/','/'},
        {'/','/','/','#','#','#','/','/'},
        {'/','/','#','.','.','.','#','/'},
        {'/','/','#','.','.','.','#','/'},
        {'/','/','#','.','#','.','#','/'}
    },
    {
        {'/','/','/','/','/','/','/','/'},
        {'/','#','.','#','.','#','.','#'},
        {'/','/','#','.','.','.','#','/'},
        {'/','/','/','#','#','#','/','/'},
        {'/','/','#','.','.','.','#','/'},
        {'/','/','#','.','.','.','#','/'},
        {'/','/','#','.','.','.','#','/'},
        {'/','/','#','.','#','.','#','/'}
    },
    {
        {'/','/','/','/','/','/','/','/'},
        {'/','/','/','#','.','#','/','/'},
        {'/','/','#','#','.','.','#','/'},
        {'/','/','#','.','#','.','#','/'},
        {'/','/','/','#','#','#','/','/'},
        {'/','/','#','.','.','.','#','/'},
        {'/','/','#','.','.','.','#','/'},
        {'/','/','#','.','#','.','#','/'}
    },
    {
        {'/','/','/','/','/','/','/','/'},
        {'/','/','/','/','/','/','/','/'},
        {'/','/','#','.','.','#','/','/'},
        {'/','/','/','#','.','.','#','/'},
        {'/','/','#','.','.','#','/','/'},
        {'/','#','.','.','.','.','#','/'},
        {'/','/','#','.','.','.','#','/'},
        {'/','/','#','.','.','.','#','/'}
    },
    {
        {'/','/','/','/','/','/','/','/'},
        {'/','#','.','#','.','#','.','#'},
        {'/','#','.','#','.','#','.','#'},
        {'/','#','.','.','.','.','.','#'},
        {'/','#','#','.','.','.','#','#'},
        {'/','/','#','.','.','.','#','/'},
        {'/','/','#','.','.','.','#','/'},
        {'/','/','#','.','.','.','#','/'}
    },
    {
        {'/','/','/','/','/','/','/','/'},
        {'/','/','/','/','/','/','/','/'},
        {'/','/','/','/','/','/','/','/'},
        {'/','/','/','#','.','#','/','/'},
        {'/','/','#','.','.','.','#','/'},
        {'/','/','/','#','.','#','/','/'},
        {'/','/','#','.','.','.','#','/'},
        {'/','/','#','.','.','.','#','/'}
    }
    };

static int secondsV[3]={0,0,0};
static int turn = 1;
static int oldGame = 0;
static char buffer[TOTAL_LINES_CHESS][CONSOLE_SIZE_X/BASE_CHAR_WIDTH-2] = {{0}};
static int rotate=0;
static int castleMove[2][3]={{0,0,0},{0,0,0}};

static void loadColorsPieces(uint64_t pieceC[][PIECES_SIZE],int j);
static void console();
static void reDrawChessConsole(char buffer[][CONSOLE_SIZE_X/BASE_CHAR_WIDTH-2]);
static void endGame();
static void drawBoard();
static int playAgain();
static void promotePiece(int x,int y);
static int rookValidMov(int xi,int yi,int xf, int yf);
static int kingValidMov(int xi,int yi,int xf, int yf);
static int bishopValidMov(int xi,int yi,int xf, int yf);
static int queenValidMov(int xi,int yi,int xf, int yf);
static int pawnValidMov(int xi,int yi,int xf, int yf);
static int knightValidMov(int xi,int yi,int xf, int yf);
static int validMovement(int xi,int yi,int xf, int yf);
static void internTimer();
static void turnBoard();

void chess(){
    clearScreen(0x800000);
    if (!oldGame || playAgain()){
        oldGame = 0;
        secondsV[0]=0;
        secondsV[1]=0;
        secondsV[2]=readSeconds(); //lleva el tiempo eliminar si se  implementa timer tic
        turn =1;
        rotate = 0;
        for (int i =0;i<2;i++){
            for (int j = 0;j<3;j++){
                castleMove[i][j]=0;
            }
        }
        for  (int i = 0;i  < TOTAL_LINES_CHESS;i++){
            for  (int j =0 ;j<CONSOLE_SIZE_X/BASE_CHAR_WIDTH-2;j++){
                buffer[i][j]=0;
            }
        }
        int newboard[SQUARES][SQUARES] = {
            {5,4,3,1,2,3,4,5},
            {6,6,6,6,6,6,6,6},
            {0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0},
            {-6,-6,-6,-6,-6,-6,-6,-6},
            {-5,-4,-3,-2,-1,-3,-4,-5}
        };
        for (int i = 0; i < SQUARES; i++){
            for (int j = 0; j < SQUARES; j++){
                board[i][j] = newboard[i][j];
            }
        }
    }
    clearScreen(0x800000);
    drawString(PLAYER_12_PLACE_X,PLAYER_1_PLACE_Y,"Player 1",strlen("player 1"),0xffffff,0x000000,2,1);
    drawString(PLAYER_12_PLACE_X,PLAYER_2_PLACE_Y,"Player 2",strlen("player 2"),0xffffff,0x000000,2,1);
    
    console();
}

static void turnBoard(){
    rotate= (rotate+1)%4; //si rotate es par van las letras arriba y los numeros de costado
}

static int playAgain(){
    drawString(SCREEN_WIDTH/2-3*BASE_CHAR_WIDTH*16,CONSOLE_LIMIT_Y,"DO YOU WANT TO PLAY A NEW GAME?",32,0xffffff,0,3,1);
    drawString(SCREEN_WIDTH/2-3*BASE_CHAR_WIDTH*10,CONSOLE_LIMIT_Y+BASE_CHAR_HEIGHT*3*2,"TYPE [ y ] or [ n ]",20,0xffffff,0,3,1);
    char buf[1];
    buf[0] = 0;
    int ans=0;
    while (1){
        if (readKeyboard(buf, 1)) {
            if (buf[0]=='y'){
                ans=1;
                break;
            } else if(buf[0]=='n'){
                ans=0;
                break;
            }   
        }
    }
    return ans;
}

static void drawBoard(){
    int x =SCREEN_WIDTH/2-BOARDDIM/2;
    int y= BOARDDIM/8;
    int movx = x;
    int movy = y;
    uint64_t colorPieces[PIECES_SIZE][PIECES_SIZE];
    for (int i = 0; i < SQUARES; movy+=SQUAREDIM, movx= x ,i++){
        for (int j = 0; j < SQUARES; movx+=SQUAREDIM,j++){
                if ((j+i)%2){
                    drawRect(movx,movy,SQUAREDIM,SQUAREDIM,BACKGROUND);
                } else {
                    drawRect(movx,movy,SQUAREDIM,SQUAREDIM,0x696969);
                }
        }
    }
    int startT,endT,startL,endL,stepT,stepL;
    switch (rotate) {
    case 0:
        startT=startL=0;
        endL=endT=7;
        stepL=stepT=1;
        break;
    case 1:
        endL=startT=0;
        endT=startL=7;
        stepT=1;
        stepL=-1;
        break;
    case 2:
        startT=startL=7;
        endT=endL=0;
        stepT=stepL=-1;
        break;
    case 3:
        startL=endT=0;
        endL=startT=7;
        stepL=1;
        stepT=-1;
        break;
    }
    //indices cambiar squares con otro indice
    movx = x+SQUAREDIM/2-BASE_CHAR_WIDTH/2;
    movy = y - BASE_CHAR_HEIGHT*2;
    char indix[2][SQUARES+1] = {{"ABCDEFGH"},{"12345678"}};
    for (int i = 0,t = startT; i < SQUARES; i++,t+=stepT){
        drawString(movx,movy,indix[rotate%2]+t,1,0xffffff,0x800000,2,0);
        movx+=SQUAREDIM;
    }
    movx = x- BASE_CHAR_WIDTH*3;
    movy = y + SQUAREDIM/2-BASE_CHAR_HEIGHT/2;
    for (int i = 0,l =startL; i < SQUARES; i++,  l+=stepL){
        drawString(movx,movy,indix[(rotate+1)%2]+l,1,0xffffff,0x800000,2,0);
        movy+=SQUAREDIM;
    }
    movy=y;
    movx=x;
    if (rotate==0||rotate==2){
        for (int i = 0,t=startT; i < SQUARES; movy+=SQUAREDIM, movx= x ,i++,t+=stepT){
            for (int j = 0,l=startL; j < SQUARES; movx+=SQUAREDIM,j++, l+=stepL){
                if (board[t][l]!=0){
                    loadColorsPieces(colorPieces,board[t][l]);
                    drawMatrix(movx,movy,colorPieces[0],PIECES_SIZE,PIECES_SIZE,SQUAREDIM/PIECES_SIZE);
                }
            }
        }
    } else { 
        for (int i = 0,t=endT; i < SQUARES; movy+=SQUAREDIM, movx= x ,i++,t-=stepT){
            for (int j = 0,l=endL; j < SQUARES; movx+=SQUAREDIM,j++, l-=stepL){
                if (board[l][t]!=0){
                    loadColorsPieces(colorPieces,board[l][t]);
                    drawMatrix(movx,movy,colorPieces[0],PIECES_SIZE,PIECES_SIZE,SQUAREDIM/PIECES_SIZE);
                }
            }
        }
    }
}

static void loadColorsPieces(uint64_t pieceC[][PIECES_SIZE],int j){
    int playern = (j>0)? 1:0;
    int piece = (j>0)? j-1:-j-1;
    uint64_t color[2]= {0xffffff,0x000000};
    for (int i = 0; i < PIECES_SIZE; i++){
        for (int k = 0; k < PIECES_SIZE; k++){
            if (pieces[piece][i][k]=='.') {
                pieceC[i][k] = color[playern];
            } else if (pieces[piece][i][k]=='#'){
                pieceC[i][k] = color[(playern+1)%2];
            } else {
                pieceC[i][k] = 0x01000000;
            }
        }
    }
}

static int kingValidMov(int xi,int yi,int xf, int yf){
    if ( fabs(xi-xf) > 1 || fabs(yi-yf) >1 ) return 0;
    return 1;
}

static int bishopValidMov(int xi,int yi,int xf, int yf){
    if (fabs(xi-xf)!=fabs(yi-yf) ) return 0;
    int starty=(yi < yf)?yi:yf;
    int endy=(yi < yf)?yf:yi;
    int startx=(xi < xf)?xi:xf;
    for (int i = starty+1,j=startx+1; i < endy; i++,j++) {
        if (board[i][j]!=0) return 0;
    }
    return 1;
}

static int rookValidMov(int xi,int yi,int xf, int yf){
    if ((xi-xf)*(yi-yf)!=0) return 0;
    if (xi-xf==0){
        int start=(yi < yf)?yi:yf;
        int end=(yi < yf)?yf:yi;
        for (int i = start+1; i < end; i++) {
            if (board[i][xi]!=0) return 0;
        }
    } else {
        int start=(xi < xf)?xi:xf;
        int end=(xi < xf)?xf:xi;
        for (int i = start+1; i < end; i++){
            if(board[yi][i]!=0) return 0;
        }
    }
    return 1;
}

static int queenValidMov(int xi,int yi,int xf, int yf){
    if ((xi-xf)==0 || (yf-yi)==0 ){
        return rookValidMov(xi,yi,xf,yf);
    }else if(fabs((xf-xi)/(yf-yi))==1){
        return bishopValidMov(xi,yi,xf,yf);
    }
    return 0;
}

static int knightValidMov(int xi,int yi,int xf, int yf){
    if (fabs(xi-xf)*fabs(yi-yf)!=2) return 0;
    return 1;
}

static int pawnValidMov(int xi,int yi,int xf, int yf){
    if (fabs(xi-xf)>1 || fabs(yi-yf)>2) return 0;
    if (board[yf][xf]==0 && xi-xf!=0) return 0;
    if (board[yf][xf]!=0 && xi-xf==0) return 0;
    if (board[yi][xi]>0) {
        if (board[yf][xf]==0 && yf-yi==2 && yi==1) return 1;
        if (yf-yi!=1) return 0;
    } else if (board[yi][xi]< 0){
        if  (board[yf][xf]==0 && yf-yi==-2 && yi==6)return 1;
        if (yf-yi!=-1) return 0;
    }
    if (fabs(yi-yf)==2){
        
    }
    
    return 1;
}

static int commandDecoder(){

}

static int validMovement(int xi,int yi,int xf, int yf){
    if (xi < 0 || xi >7 || yi < 0 || yi >7|| xf < 0 || xf >7|| yf < 0 || yf >7) return 0; // error de tamano
    if (turn%2==0 && board[yi][xi]<0) return 0; //error de player
    if (turn%2==1 && board[yi][xi]>0) return 0;
    if (board[yi][xi]==0) return 0; // no se puede ejecutar este movimiento
    if (board[yi][xi] * board[yf][xf] > 0) return 0;
    switch (fabs(board[yi][xi]))
    {
    case 1:
        return kingValidMov(xi,yi,xf,yf);
    case 2:
        return queenValidMov(xi,yi,xf,yf);
    case 3:
        return bishopValidMov(xi,yi,xf,yf);
    case 4:
        return knightValidMov(xi,yi,xf,yf);
    case 5:
        return rookValidMov(xi,yi,xf,yf);
    case 6:
        return pawnValidMov(xi,yi,xf,yf);
    default:
        break;
    }
    return 0;
}

static void internTimer(){
    if (secondsV[2]!=readSeconds()){
        secondsV[(turn)%2]++;
        char toPrintTimer1[5];
        toPrintTimer1[0] = secondsV[(turn)%2]/60/10%10+'0';
        toPrintTimer1[1] = secondsV[(turn)%2]/60%10+'0';
        toPrintTimer1[2] = ':';
        toPrintTimer1[3] = secondsV[(turn)%2]%60/10%10+'0';
        toPrintTimer1[4] = secondsV[(turn)%2]%60%10+'0';
        char toPrintTimer2[5];
        toPrintTimer2[0] = secondsV[(turn+1)%2]/60/10%10+'0';
        toPrintTimer2[1] = secondsV[(turn+1)%2]/60%10+'0';
        toPrintTimer2[2] = ':';
        toPrintTimer2[3] = secondsV[(turn+1)%2]%60/10%10+'0';
        toPrintTimer2[4] = secondsV[(turn+1)%2]%60%10+'0';
        int movy = PLAYER_2_PLACE_Y+2*BASE_CHAR_HEIGHT;
        drawRect(PLAYER_12_PLACE_X,movy+(turn%2)*BOARDDIM/2,5*2*BASE_CHAR_WIDTH,2*BASE_CHAR_HEIGHT,0x800000);
        drawString(PLAYER_12_PLACE_X,movy+(turn%2)*BOARDDIM/2,toPrintTimer1,5,0xffffff,0,2,1);
        drawRect(PLAYER_12_PLACE_X,movy+((turn+1)%2)*BOARDDIM/2,5*2*BASE_CHAR_WIDTH,2*BASE_CHAR_HEIGHT,0x800000);
        drawString(PLAYER_12_PLACE_X,movy+((turn+1)%2)*BOARDDIM/2,toPrintTimer2,5,0xffffff,0,2,1);
        secondsV[2]=readSeconds();
    }
}

static void console(){
    reDrawChessConsole(buffer);
    drawBoard();
    int movx = 7*BASE_CHAR_WIDTH+CONSOLE_LIMIT_X;
    int l=0;
    while (1){
        internTimer();
        if (secondsV[1]-secondsV[0]>60 || secondsV[1]>3600){
            endGame(2);
            break;
        } else if (secondsV[0]-secondsV[1]>60 || secondsV[0]>3600){
            endGame(1);
            break;
        }
        
        uint8_t bufferLength = 1;
        char buf[bufferLength];
        for (int i = 0; i < bufferLength; i++){
            buf[i] = 0;
        }
        if (readKeyboard(buf, bufferLength)) {
            drawRect(CONSOLE_LIMIT_X,PROMOTE_LOGS,CONSOLE_SIZE_X,(9)*BASE_CHAR_HEIGHT,0x000000);
            if (buf[0]=='x') {
                oldGame =1;
                break;
            }
            if (buf[0]=='`'){
                turnBoard();
                drawBoard();
            } else if (buf[0]=='\n' || l > MAX_LENGTH){
                l=0;
                if (!strcmp("castle r",buffer[turn])){
                    if (turn%2){ //turno de blancas
                        if (castleMove[turn%2][0]==0 && castleMove[turn%2][1]==0){
                            if (board[7][5]==0 && board[7][6]==0){
                                board[7][6]=board[7][4];
                                board[7][4]=0;
                                board[7][5]=board[7][7];
                                board[7][7]=0;
                                castleMove[turn%2][0]=1;
                                drawBoard();
                                turn=(turn+1)%TOTAL_LINES_CHESS;
                                reDrawChessConsole(buffer);
                            }
                        } // castlemove == 0 el rey no se movio
                    } else {
                        if (castleMove[turn%2][0]==0 && castleMove[turn%2][1]==0){
                            if (board[0][1]==0 && board[0][2]==0){
                                board[0][1]=board[0][3];
                                board[0][3]=0;
                                board[0][2]=board[0][0];
                                board[0][0]=0;
                                castleMove[turn%2][0]=1;
                                drawBoard();
                                turn=(turn+1)%TOTAL_LINES_CHESS;
                                reDrawChessConsole(buffer);
                            }
                        }
                    }
                }else if(!strcmp("castle l",buffer[turn])){
                    if (turn%2){
                        if (castleMove[turn%2][0]==0 && castleMove[turn%2][2]==0){
                            if (board[7][2]==0 && board[7][1]==0 && board[7][3]==0){
                                board[7][2]=board[7][4];
                                board[7][4]=0;
                                board[7][3]=board[7][0];
                                board[7][0]=0;
                                castleMove[turn%2][0]=1;
                                drawBoard();
                                turn=(turn+1)%TOTAL_LINES_CHESS;
                                reDrawChessConsole(buffer);
                            }
                        }
                    } else {
                        if (castleMove[turn%2][0]==0 && castleMove[turn%2][2]==0){
                            if (board[0][6]==0 && board[0][5]==0 && board[0][4]==0){
                                board[0][5]=board[0][3];
                                board[0][3]=0;
                                board[0][4]=board[0][7];
                                board[0][7]=0;
                                castleMove[turn%2][0]=1;
                                drawBoard();
                                turn=(turn+1)%TOTAL_LINES_CHESS;
                                reDrawChessConsole(buffer);
                            }
                        }
                    }
                }
                int xi = buffer[turn][0]-'a';
                int yi = buffer[turn][1]-'0'-1;
                int xf =buffer[turn][6]-'a';
                int yf = buffer[turn][7]-'0'-1;
                if (validMovement(xi,yi,xf,yf) ){
                    if(fabs(board[yi][xi])==KING){
                        castleMove[turn%2][0]=1;
                    }else if ((board[yi,xi])==ROOK){
                        if(xi==7){
                            castleMove[turn%2][2]=1;
                        } else{
                            castleMove[turn%2][1]=1;
                        }
                    }else if(board[yi][xi]==-ROOK){
                        if(xi==7){
                            castleMove[turn%2][1]=1;
                        } else{
                            castleMove[turn%2][2]=1;
                        }
                    }
                    if (board[yf][xf]){
                        drawString(CONSOLE_LIMIT_X,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y+8*BASE_CHAR_HEIGHT,figures[fabs(board[yi][xi])-1],strlen(figures[fabs(board[yi][xi])-1]),0xffffff,0x000000,1,0);
                        drawString(CONSOLE_LIMIT_X+(strlen(figures[fabs(board[yi][xi])-1]))*BASE_CHAR_WIDTH,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y+8*BASE_CHAR_HEIGHT," eats ",6,0xffffff,0x000000,1,0);     
                        drawString(CONSOLE_LIMIT_X+(strlen(figures[fabs(board[yi][xi])-1])+6)*BASE_CHAR_WIDTH,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y+8*BASE_CHAR_HEIGHT,figures[fabs(board[yf][xf])-1],strlen(figures[fabs(board[yf][xf])-1]),0xffffff,0x000000,1,0);
                    }
                    if (fabs(board[yf][xf])==KING) {
                        endGame((turn+1)%2+1);
                        break;
                    }
                    board[yf][xf]= board[yi][xi];
                    board[yi][xi] = 0;
                    drawBoard();
                    if((board[yf][xf]==6 && yf==7) || (board[yf][xf] == -6 && yf==0)){
                        promotePiece(xf,yf);
                        drawBoard();
                    }
                    turn=(turn+1)%TOTAL_LINES_CHESS;
                    reDrawChessConsole(buffer);
                } else {
                    drawRect(CONSOLE_LIMIT_X,PROMOTE_LOGS,CONSOLE_SIZE_X,(9)*BASE_CHAR_HEIGHT,0x000000);
                    drawString(CONSOLE_LIMIT_X,MOVEMENT,"UNVALID MOVEMENT",17,0xffffff,0,1,0);
                    for (int i=0;i<CONSOLE_SIZE_X/BASE_CHAR_WIDTH-2;i++) {
                        buffer[turn][i]=0;
                    }
                    reDrawChessConsole(buffer);
                }
            } else if (buf[0]=='\b'){
                if (l>0){
                    l--;
                    buffer[turn][l]=0;
                drawRect(movx+l*BASE_CHAR_WIDTH,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y-BASE_CHAR_HEIGHT,BASE_CHAR_WIDTH,BASE_CHAR_HEIGHT,0);
                }
            }else {
                drawString(movx+l*BASE_CHAR_WIDTH,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y-BASE_CHAR_HEIGHT,buf,1,0x0000ff,0,1,0);
                buffer[turn][l++] = buf[0];
            }
        }
    }
}

static void promotePiece(int x,int y){
    drawString(CONSOLE_LIMIT_X,PROMOTE_LOGS,"you can promote your",21,0xffffff,1,1,1);
    drawString(CONSOLE_LIMIT_X,PROMOTE_LOGS+BASE_CHAR_HEIGHT,"pawn choose between:",21,0xffffff,1,1,1);
    for (int i =1;i<PIECES_AMOUNT-1;i++){
        drawString(CONSOLE_LIMIT_X,PROMOTE_LOGS+BASE_CHAR_HEIGHT*(i+1),figures[i],strlen(figures[i]),0xffffff,1,1,0);
        char pieceNumber[2];
        intToBase(i,10,pieceNumber);
        drawString(CONSOLE_LIMIT_X+BASE_CHAR_WIDTH*10,PROMOTE_LOGS+BASE_CHAR_HEIGHT*(i+1),pieceNumber,1,0xffffff,1,1,0);
    }
    while(1){
        uint8_t bufferLength = 1;
        char buf[bufferLength];
        for (int i = 0; i < bufferLength; i++){
            buf[i] = 0;
        }
        int team = (board[y][x]>0)?1:-1;
        if (readKeyboard(buf, bufferLength)) {
            if (buf[0]-'0' < 5 &&  buf[0]-'0'>0){
                board[y][x] = (buf[0]-'0'+1)*team;
                break;
            }
        }
    }
    drawRect(CONSOLE_LIMIT_X,PROMOTE_LOGS,42*BASE_CHAR_WIDTH,(PIECES_AMOUNT-1)*BASE_CHAR_HEIGHT,0x800000);
}

static void endGame(int winner){
    int movx=0,movy=0;
    for (int i = 0; i < SCREEN_HEIGHT/SQUAREDIM; movy+=SQUAREDIM, movx= 0 ,i++){
        for (int j = 0; j < SCREEN_WIDTH/SQUAREDIM; movx+=SQUAREDIM,j++){
            if ((j+i)%2){
                drawRect(movx,movy,SQUAREDIM,SQUAREDIM,BACKGROUND);
            } else {
                drawRect(movx,movy,SQUAREDIM,SQUAREDIM,0x696969);
            }
        }
    }
    char winnerC = (char)winner+'0';
    drawString(SCREEN_WIDTH/2-7*4*BASE_CHAR_WIDTH,SCREEN_HEIGHT/2-2*BASE_CHAR_HEIGHT,"THE WINNER IS",14,0x800000,0,4,1);
    drawString(SCREEN_WIDTH/2-4*4*BASE_CHAR_WIDTH,SCREEN_HEIGHT/2+BASE_CHAR_HEIGHT*4-2*BASE_CHAR_HEIGHT,"PLAYER :",9,0x800000,0,4,1);
    drawString(SCREEN_WIDTH/2-4*4*BASE_CHAR_WIDTH+BASE_CHAR_WIDTH*4*9,SCREEN_HEIGHT/2+BASE_CHAR_HEIGHT*4-2*BASE_CHAR_HEIGHT,&winnerC,1,0x800000,0,4,1);
    drawString(SCREEN_WIDTH/2-13*3*BASE_CHAR_WIDTH,SCREEN_HEIGHT/2+BASE_CHAR_HEIGHT*4*3-2*BASE_CHAR_HEIGHT,"TOUCH ANY KEYBOARD TO EXIT",27,0x800000,0,3,1);
    while(1){
        uint8_t bufferLength = 1;
        char buf[bufferLength];
        for (int i = 0; i < bufferLength; i++){
            buf[i] = 0;
        }
        if (readKeyboard(buf, bufferLength)) {
            break;
        }
    }
}

static void reDrawChessConsole(char buffer[][CONSOLE_SIZE_X/BASE_CHAR_WIDTH-2]){
    int x= CONSOLE_LIMIT_X;
    int y = CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y-BASE_CHAR_HEIGHT*2;
    char player[1] = {(turn+1)%2+'1'};
    drawRect(CONSOLE_LIMIT_X,CONSOLE_LIMIT_Y,CONSOLE_SIZE_X,CONSOLE_SIZE_Y,0x000000);
    drawString(CONSOLE_LIMIT_X,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y-BASE_CHAR_HEIGHT,"P  |> ",7,0x00ff00,0x000000,1,0);
    drawString(CONSOLE_LIMIT_X+BASE_CHAR_WIDTH,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y-BASE_CHAR_HEIGHT,player,1,0x00ff00,0x000000,1,0);
    for (int i = turn; y>CONSOLE_LIMIT_Y; i--){
        drawString(x,y,buffer[i%TOTAL_LINES_CHESS],CONSOLE_SIZE_X/BASE_CHAR_WIDTH,0xffffff,0,1,1);
        y-=BASE_CHAR_HEIGHT;
    }
}
