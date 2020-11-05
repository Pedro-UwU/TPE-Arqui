#include <chess.h>

// char *figures[PIECES_AMOUNT]={"king","queen","bishop","knight","rook","pawn"};

char chessPieces[PIECES_AMOUNT][PIECES_SIZE][PIECES_SIZE] = {
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

int board[8][8] = {
    {4,3,2,1,0,2,3,4},
    {5,5,5,5,5,5,5,5},
    {-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1},
    {5,5,5,5,5,5,5,5},
    {4,3,2,0,1,2,3,4}
    };

static void loadColorsPieces(uint64_t pieceC[][PIECES_SIZE],int j);
static void console();
static void reDrawChessConsole(char buffer[][CONSOLE_SIZE_X/BASE_CHAR_WIDTH-2],int actLine);
static void cleanConsole(char buffer[][CONSOLE_SIZE_X/BASE_CHAR_WIDTH-2]);

void drawBoard(){
    clearScreen(0x800000);
    int x =SCREEN_WIDTH/2-BOARDDIM/2;
    int y= BOARDDIM/8;
    int movx = x;
    int movy = y;
    uint64_t colorPieces[PIECES_SIZE][PIECES_SIZE];
    for (int i = 0; i < SQUARES; movy+=SQUAREDIM, movx= x ,i++){
        for (int j = 0; j < SQUARES; movx+=SQUAREDIM,j++){
            // if (board[i][j]>=0){
                // loadColorsPieces(colorPieces,board[i][j]);
                // drawMatrixSyscall(movx,movy,colorPieces[board[i][j]],PIECES_SIZE,PIECES_SIZE,5);
            // }else{
                if ((j+i)%2){
                    drawRect(movx,movy,SQUAREDIM,SQUAREDIM,BACKGROUND);
                } else {
                    drawRect(movx,movy,SQUAREDIM,SQUAREDIM,0x696969);
                }
            // }
        }
    }
    //indices
    movx = x;
    movy = y - BASE_CHAR_HEIGHT*2;
    movx+=SQUAREDIM/2-BASE_CHAR_WIDTH/2;
    char indixL[SQUARES+1] = "abcdefgh";
    for (int i = 0; i < SQUARES; i++){
        drawString(movx,movy,indixL+i,1,0xffffff,0,2,1);
        movx+=SQUAREDIM;
    }
    movx = x- BASE_CHAR_WIDTH*2;
    movy = y + SQUAREDIM/2-BASE_CHAR_HEIGHT/2;
    char indixN[SQUARES+1] = "12345678";
    for (int i = 0; i < SQUARES; i++){
        drawString(movx,movy,indixN+i,1,0xffffff,0,2,1);
        movy+=SQUAREDIM;
    }
    drawString(x-BASE_CHAR_WIDTH*(strlen("player 1") + 15),y,"Player 1",strlen("player 1"),0xffffff,0x000000,2,1);
    drawString(x-BASE_CHAR_WIDTH*(strlen("player 2") + 15),y+BOARDDIM/2,"Player 2",strlen("player 2"),0xffffff,0x000000,2,1);
    console();
}

static void loadColorsPieces(uint64_t pieceC[][PIECES_SIZE],int j){
    for (int i = 0; i < PIECES_SIZE; i++){
        for (int k = 0; k < PIECES_SIZE; k++){
            if (chessPieces[j][i][k]=='.') {
                pieceC[i][k] = 0xffffff;
            } else if (chessPieces[j][i][k]=='#'){
                pieceC[i][k] = 0x000000;
            } else {
                pieceC[i][k] = BACKGROUND;
            }
            
        }
    }
}

static void console(){
    char buffer[TOTAL_LINES_CHESS][CONSOLE_SIZE_X/BASE_CHAR_WIDTH-2] ={0};
    reDrawChessConsole(buffer,0);
    int movx = 7*BASE_CHAR_WIDTH+CONSOLE_LIMIT_X;
    int l=0,h=0;
    while (1){
        uint8_t bufferLength = 1;
        char buf[bufferLength];
        for (int i = 0; i < bufferLength; i++){
            buf[i] = 0;
        }
        if (readKeyboard(buf, bufferLength)) {
            if (buf[0]=='\n' || l > MAX_LENGTH){
                l=0;
                reDrawChessConsole(buffer,h);
                h=(h+1)%TOTAL_LINES_CHESS;
            } else if (buf[0]=='\b'){
                if (l>0){
                    l--;
                drawRect(movx+l*BASE_CHAR_WIDTH,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y-BASE_CHAR_HEIGHT,BASE_CHAR_WIDTH,BASE_CHAR_HEIGHT,0);
                }
            }else {
                drawString(movx+l*BASE_CHAR_WIDTH,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y-BASE_CHAR_HEIGHT,buf,1,0x0000ff,0,1,0);
                buffer[h][l++] = buf[0];
            }
        }
    }
}

static void reDrawChessConsole(char buffer[][CONSOLE_SIZE_X/BASE_CHAR_WIDTH-2],int actLine){
    int x= CONSOLE_LIMIT_X;
    int y = CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y-BASE_CHAR_HEIGHT*2;
    drawRect(CONSOLE_LIMIT_X,CONSOLE_LIMIT_Y,CONSOLE_SIZE_X,CONSOLE_SIZE_Y,0x000000);
    drawString(CONSOLE_LIMIT_X,CONSOLE_LIMIT_Y+CONSOLE_SIZE_Y-BASE_CHAR_HEIGHT,"P1 |> ",7,0x00ff00,0x000000,1,0);
    for (int i = actLine; y>CONSOLE_LIMIT_Y; i--){
        drawString(x,y,buffer[i%TOTAL_LINES_CHESS],CONSOLE_SIZE_X/BASE_CHAR_WIDTH,0xffffff,0,1,1);
        y-=BASE_CHAR_HEIGHT;
    }    
}

