#include <chess.h>

char *figures[PIECES_AMOUNT]={"king","queen","bishop","knight","rook","pawn"};

int board[SQUARES][SQUARES] ={
    {5,4,3,2,1,3,4,5},
    {6,6,6,6,6,6,6,6},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {-6,-6,-6,-6,-6,-6,-6,-6},
    {-5,-4,-3,-1,-2,-3,-4,-5}
    };;

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

static void loadColorsPieces(uint64_t pieceC[][PIECES_SIZE],int j);
static void console();
static void reDrawChessConsole(char buffer[][CONSOLE_SIZE_X/BASE_CHAR_WIDTH-2],int actLine);
static void reDrawChessConsole(char buffer[][CONSOLE_SIZE_X/BASE_CHAR_WIDTH-2],int actLine);
static void endGame();
static void drawBoard();
int playAgain();
void newGame();

void chess(){
    clearScreen(0x800000);
    if (playAgain()){
    int newboard[SQUARES][SQUARES] = {{5,4,3,2,1,3,4,5},
    {6,6,6,6,6,6,6,6},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {-6,-6,-6,-6,-6,-6,-6,-6},
    {-5,-4,-3,-1,-2,-3,-4,-5}
    };
    for (int i = 0; i < SQUARES; i++){
        for (int j = 0; j < SQUARES; j++){
            board[i][j] = newboard[i][j];
        }
        
    }
    
        }
    clearScreen(0x800000);
    
    int x =SCREEN_WIDTH/2-BOARDDIM/2;
    int y= BOARDDIM/8;
    //indices
    int movx = x;
    int movy = y - BASE_CHAR_HEIGHT*2;
    movx+=SQUAREDIM/2-BASE_CHAR_WIDTH/2;
    char indixL[SQUARES+1] = "ABCDEFGH";
    for (int i = 0; i < SQUARES; i++){
        drawString(movx,movy,indixL+i,1,0xffffff,0,2,1);
        movx+=SQUAREDIM;
    }
    movx = x- BASE_CHAR_WIDTH*3;
    movy = y + SQUAREDIM/2-BASE_CHAR_HEIGHT/2;
    char indixN[SQUARES+1] = "12345678";
    for (int i = 0; i < SQUARES; i++){
        drawString(movx,movy,indixN+i,1,0xffffff,0,2,1);
        movy+=SQUAREDIM;
    }
    drawString(PLAYER_12_PLACE_X,PLAYER_1_PLACE_Y,"Player 1",strlen("player 1"),0xffffff,0x000000,2,1);
    drawString(PLAYER_12_PLACE_X,PLAYER_2_PLACE_Y,"Player 2",strlen("player 2"),0xffffff,0x000000,2,1);
    
    console();
}

int playAgain(){
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
    movy=y;
    movx=x;
    for (int i = 0; i < SQUARES; movy+=SQUAREDIM, movx= x ,i++){
        for (int j = 0; j < SQUARES; movx+=SQUAREDIM,j++){
            if (board[i][j]!=0){
                loadColorsPieces(colorPieces,board[i][j]);
                drawMatrix(movx,movy,colorPieces,PIECES_SIZE,PIECES_SIZE,SQUAREDIM/PIECES_SIZE);
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
    if (fabs(xi-xf) > 1 || fabs(yi-yf) >1 ) return 0;
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
    if ((xi-xf)>1 || fabs(yi-yf)>1) return 0;
    if (board[yf][xf]==0 && xi-xf!=0) return 0;
    if (board[yf][xf]!=0 && xi-xf==0) return 0;
    if (board[yi][xi]>0) {
        if (yf-yi!=1) return 0;
    } else if (board[yi][xi]< 0){
        if (yf-yi!=-1) return 0;
    }
    return 1;
}

static int validMovement(int xi,int yi,int xf, int yf,int player){
    if (xi < 0 || xi >7 || yi < 0 || yi >7|| xf < 0 || xf >7|| yf < 0 || yf >7) return 0; // error de tamano
    if (player%2==0 && board[yi][xi]<0) return 0; //error de player
    if (player%2==1 && board[yi][xi]>0) return 0;
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

static void console(){
    char buffer[TOTAL_LINES_CHESS][CONSOLE_SIZE_X/BASE_CHAR_WIDTH-2] = {{0}};
    reDrawChessConsole(buffer,1);
    drawBoard();
    int movx = 7*BASE_CHAR_WIDTH+CONSOLE_LIMIT_X;
    int l=0,h=1;
    int prevSeconds = readSeconds();
    int secondsV[2]={0,0};
    while (1){
        int seconds = readSeconds();
        if (prevSeconds!=seconds){
            secondsV[(h+1)%2] += 1;
            char toPrintTimer[5];
            toPrintTimer[0] = secondsV[(h+1)%2]/60/10%10+'0';
            toPrintTimer[1] = secondsV[(h+1)%2]/60%10+'0';
            toPrintTimer[2] = ':';
            toPrintTimer[3] = secondsV[(h+1)%2]%60/10%10+'0';
            toPrintTimer[4] = secondsV[(h+1)%2]%60%10+'0';
            prevSeconds = seconds;
            int movy = PLAYER_2_PLACE_Y+2*BASE_CHAR_HEIGHT;
            drawRect(PLAYER_12_PLACE_X,movy+((h)%2)*BOARDDIM/2,5*2*BASE_CHAR_WIDTH,2*BASE_CHAR_HEIGHT,0x800000);
            drawString(PLAYER_12_PLACE_X,movy+((h)%2)*BOARDDIM/2,toPrintTimer,5,0xffffff,0,2,1);
        }
        if (secondsV[1]-secondsV[0]>60 || secondsV[1]>3600){
            endGame(1);
            break;
        } else if (secondsV[0]-secondsV[1]>60 || secondsV[0]>3600){
            endGame(2);
            break;
        }
        
        
        uint8_t bufferLength = 1;
        char buf[bufferLength];
        for (int i = 0; i < bufferLength; i++){
            buf[i] = 0;
        }
        if (readKeyboard(buf, bufferLength)) {
            if (buf[0]=='x') break; 
            if (buf[0]=='\n' || l > MAX_LENGTH){
                l=0;
                reDrawChessConsole(buffer,h+1);
                int xi = buffer[h][0]-'a';
                int yi = buffer[h][1]-'0'-1;
                int xf =buffer[h][6]-'a';
                int yf = buffer[h][7]-'0'-1;
                if (validMovement(xi,yi,xf,yf,h) ){
                    if (board[yf][xf]){
                        drawString(CONSOLE_LIMIT_X,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y+8*BASE_CHAR_HEIGHT,figures[fabs(board[yi][xi])-1],strlen(figures[fabs(board[yi][xi])-1]),0xffffff,0x000000,1,0);
                        drawString(CONSOLE_LIMIT_X+(strlen(figures[fabs(board[yi][xi])-1]))*BASE_CHAR_WIDTH,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y+8*BASE_CHAR_HEIGHT," come ",6,0xffffff,0x000000,1,0);     
                        drawString(CONSOLE_LIMIT_X+(strlen(figures[fabs(board[yi][xi])-1])+6)*BASE_CHAR_WIDTH,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y+8*BASE_CHAR_HEIGHT,figures[fabs(board[yf][xf])-1],strlen(figures[fabs(board[yf][xf])-1]),0xffffff,0x000000,1,0);
                    }
                    if (fabs(board[yf][xf])==KING) {
                        endGame((h+1)%2+1);
                        break;
                    }
                    board[yf][xf]= board[yi][xi];
                    board[yi][xi] = 0;
                    drawBoard();
                    drawRect(CONSOLE_LIMIT_X,CONSOLE_LIMIT_Y,18*BASE_CHAR_WIDTH,BASE_CHAR_HEIGHT,0);
                    if((board[yf][xf]==6 && yf==7) || (board[yf][xf] == -6 && yf==0)){
                        promotePiece(xf,yf);
                        drawBoard();
                    }
                    h=(h+1)%TOTAL_LINES_CHESS;
                }
                else {
                    drawString(CONSOLE_LIMIT_X,CONSOLE_LIMIT_Y,"UNVALID MOVEMENT",17,0xffffff,0,1,0);
                }
            } else if (buf[0]=='\b'){
                if (l>0){
                    l--;
                    buffer[h][l]=0;
                drawRect(movx+l*BASE_CHAR_WIDTH,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y-BASE_CHAR_HEIGHT,BASE_CHAR_WIDTH,BASE_CHAR_HEIGHT,0);
                }
            }else {
                drawString(movx+l*BASE_CHAR_WIDTH,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y-BASE_CHAR_HEIGHT,buf,1,0x0000ff,0,1,0);
                buffer[h][l++] = buf[0];
            }
        }
    }
}

void promotePiece(int x,int y){
    drawRect(CONSOLE_LIMIT_X,PROMOTE_LOGS,42*BASE_CHAR_WIDTH,(10)*BASE_CHAR_HEIGHT,0x000000);
    drawString(CONSOLE_LIMIT_X,PROMOTE_LOGS,"you can promote your pawn",26,0xffffff,1,1,1);
    drawString(CONSOLE_LIMIT_X,PROMOTE_LOGS,"choose between:",16,0xffffff,1,1,1);
    for (int i =1;i<PIECES_AMOUNT-1;i++){
        drawString(CONSOLE_LIMIT_X,PROMOTE_LOGS+BASE_CHAR_HEIGHT*(i+2,figures[i],strlen(figures[i]),0xffffff,1,1,0);
        char pieceNumber[2];
        intToBase(i,10,pieceNumber);
        drawString(CONSOLE_LIMIT_X+BASE_CHAR_WIDTH*10,PROMOTE_LOGS+BASE_CHAR_HEIGHT*i,pieceNumber,1,0xffffff,1,1,0);
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
    
    
}

static void reDrawChessConsole(char buffer[][CONSOLE_SIZE_X/BASE_CHAR_WIDTH-2],int actLine){
    int x= CONSOLE_LIMIT_X;
    int y = CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y-BASE_CHAR_HEIGHT*2;
    char player[1] = {(actLine+1)%2+'0'+1};
    drawRect(CONSOLE_LIMIT_X,CONSOLE_LIMIT_Y,CONSOLE_SIZE_X,CONSOLE_SIZE_Y,0x000000);
    drawString(CONSOLE_LIMIT_X,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y-BASE_CHAR_HEIGHT,"P  |> ",7,0x00ff00,0x000000,1,0);
    drawString(CONSOLE_LIMIT_X+BASE_CHAR_WIDTH,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y-BASE_CHAR_HEIGHT,player,1,0x00ff00,0x000000,1,0);
    for (int i = actLine; y>CONSOLE_LIMIT_Y; i--){
        drawString(x,y,buffer[i%TOTAL_LINES_CHESS],CONSOLE_SIZE_X/BASE_CHAR_WIDTH,0xffffff,0,1,1);
        y-=BASE_CHAR_HEIGHT;
    }    
}
