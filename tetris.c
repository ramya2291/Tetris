#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 16
#define RED     "\x1b[31m"
#define BLACK    "\x1b[30m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define GREY   "\x1b[90m"
#define DARKRED "\x1b[91m"
#define RESET   "\x1b[0m"
#define blackbg    "\x1b[40m"
#define redbg "\x1b[41m"
#define greenbg "\x1b[42m"
#define yellowbg "\x1b[43m"
#define bluebg "\x1b[44m"
#define magentabg "\x1b[45m"
#define cyanbg "\x1b[46m"
#define whitebg "\x1b[47m"
#define bright "\x1b[1m"
#define dim "\x1b[2m"

typedef enum{
    T_SHAPE = 1,
    I_SHAPE,
    J_SHAPE,
    L_SHAPE,
    O_SHAPE,
    S_SHAPE,
    Z_SHAPE,
}ShapeType;

int board[BOARD_HEIGHT][BOARD_WIDTH];
int shape[4][2];
ShapeType shape_type;
int score;

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void gotoxy(int x, int y)
{
   COORD coord;
   coord.X = x;
   coord.Y = y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void create_board()//initialization of the board
{
    for(int i=0;i<BOARD_WIDTH;i++)
    {
        for(int j=0;j<BOARD_HEIGHT;j++)
        {
            board[i][j]=0;
        }
    }
}

void print_board()
{
   int i;
   for(i=0;i<BOARD_HEIGHT/2;i++)
   {
    printf("\t\t\t\t\t%c",219);
      for(int j=0;j<BOARD_WIDTH;j++)
      {
         if(board[i][j]==0)
         printf(GREY"|"RESET"  ",219,219);
         else if(board[i][j]==1)
         printf(GREY"|"RESET yellowbg"  "RESET,219,219);
         else if(board[i][j]==2)
         printf(GREY"|"RESET redbg"  "RESET,219,219);
         else if(board[i][j]==3)
         printf(GREY"|"RESET bluebg"  "RESET,219,219);
         else if(board[i][j]==4)
         printf(GREY"|"RESET magentabg"  "RESET,219,219);
         else if(board[i][j]==5)
         printf(GREY"|"RESET cyanbg"  "RESET,219,219);
         else if(board[i][j]==6)
         printf(GREY"|"RESET greenbg"  "RESET,219,219);
         else if(board[i][j]==7)
         printf(GREY"|"RESET bright redbg"  "RESET,219,219);
         else if(board[i][j]==8)
         printf(GREY"|"RESET blackbg"  "RESET,219,219);
      }
      printf("|%c|",219);
      printf("\n\t\t\t\t\t"GREY"--------------------------------\n"RESET);
   }
   if(i=BOARD_HEIGHT/2)
   {
    printf("\t\t\t\t\t%c",219);
      for(int j=0;j<BOARD_WIDTH;j++)
      {
         if(board[i][j]==0)
         printf(GREY"|"RESET "  ",219,219);
         else if(board[i][j]==1)
         printf(GREY"|"RESET yellowbg"  "RESET,219,219);
         else if(board[i][j]==2)
         printf(GREY"|"RESET redbg"  "RESET,219,219);
         else if(board[i][j]==3)
         printf(GREY"|"RESET bluebg"  "RESET,219,219);
         else if(board[i][j]==4)
         printf(GREY"|"RESET magentabg"  "RESET,219,219);
         else if(board[i][j]==5)
         printf(GREY"|"RESET cyanbg"  "RESET,219,219);
         else if(board[i][j]==6)
         printf(GREY"|"RESET greenbg"  "RESET,219,219);
         else if(board[i][j]==7)
         printf(GREY"|"RESET bright redbg"  "RESET,219,219);
         else if(board[i][j]==8)
         printf(GREY"|"RESET blackbg"  "RESET,219,219);
      }
      printf("|%c|",219);
      printf("\t\tScore:%d\n\t\t\t\t\t"GREY"---------------------------------\n"RESET,score);
      i++;
   }
   for(i=BOARD_HEIGHT/2+1;i<BOARD_HEIGHT;i++)
   {
    printf("\t\t\t\t\t%c",219);
      for(int j=0;j<BOARD_WIDTH;j++)
      {
         if(board[i][j]==0)
         printf(GREY"|"RESET "  ",219,219);
         else if(board[i][j]==1)
         printf(GREY"|"RESET yellowbg"  "RESET,219,219);
         else if(board[i][j]==2)
         printf(GREY"|"RESET redbg"  "RESET,219,219);
         else if(board[i][j]==3)
         printf(GREY"|"RESET bluebg"  "RESET,219,219);
         else if(board[i][j]==4)
         printf(GREY"|"RESET magentabg"  "RESET,219,219);
         else if(board[i][j]==5)
         printf(GREY"|"RESET cyanbg"  "RESET,219,219);
         else if(board[i][j]==6)
         printf(GREY"|"RESET greenbg"  "RESET,219,219);
         else if(board[i][j]==7)
         printf(GREY"|"RESET bright redbg"  "RESET,219,219);
         else if(board[i][j]==8)
         printf(GREY"|"RESET blackbg"  "RESET,219,219);
      }
      printf("|%c|",219);
      printf("\n\t\t\t\t\t"GREY"---------------------------------\n"RESET);
   }
}

void new_random_shape()//considering the x and y coordinate of the block
{
   shape_type=rand()%7+1;
   switch (shape_type) 
   {
      case T_SHAPE:
         shape[0][0]=BOARD_WIDTH/2;
         shape[0][1]=0;
         shape[1][0]=BOARD_WIDTH/2-1;
         shape[1][1]=1;
         shape[2][0]=BOARD_WIDTH/2+1;
         shape[2][1]=1;
         shape[3][0]=BOARD_WIDTH/2;
         shape[3][1]=1;
         break;
      case I_SHAPE:
         shape[0][0]=BOARD_WIDTH/2;
         shape[0][1]=0;
         shape[1][0]=BOARD_WIDTH/2-1;
         shape[1][1]=0;
         shape[2][0]=BOARD_WIDTH/2+1;
         shape[2][1]=0;
         shape[3][0]=BOARD_WIDTH/2+2;
         shape[3][1]=0;
         break;
      case J_SHAPE:
         shape[0][0]=BOARD_WIDTH/2;
         shape[0][1]=1;
         shape[1][0]=BOARD_WIDTH/2-1;
         shape[1][1]=1;
         shape[2][0]=BOARD_WIDTH/2-1;
         shape[2][1]=0;
         shape[3][0]=BOARD_WIDTH/2+1;
         shape[3][1]=1;
         break;
      case L_SHAPE:
         shape[0][0]=BOARD_WIDTH/2;
         shape[0][1]=1;
         shape[1][0]=BOARD_WIDTH/2-1;
         shape[1][1]=1;
         shape[2][0]=BOARD_WIDTH/2+1;
         shape[2][1]=1;
         shape[3][0]=BOARD_WIDTH/2+1;
         shape[3][1]=0;
         break;
      case O_SHAPE:
         shape[0][0]=BOARD_WIDTH/2-1;
         shape[0][1]=0;
         shape[1][0]=BOARD_WIDTH/2-1;
         shape[1][1]=1;
         shape[2][0]=BOARD_WIDTH/2;
         shape[2][1]=0;
         shape[3][0]=BOARD_WIDTH/2;
         shape[3][1]=1;
         break;
      case S_SHAPE:
         shape[0][0]=BOARD_WIDTH/2;
         shape[0][1]=1;
         shape[1][0]=BOARD_WIDTH/2;
         shape[1][1]=0;
         shape[2][0]=BOARD_WIDTH/2-1;
         shape[2][1]=1;
         shape[3][0]=BOARD_WIDTH/2+1;
         shape[3][1]=0;
         break;
      case Z_SHAPE:
         shape[0][0]=BOARD_WIDTH/2;
         shape[0][1]=1;
         shape[1][0]=BOARD_WIDTH/2;
         shape[1][1]=0;
         shape[2][0]=BOARD_WIDTH/2-1;
         shape[2][1]=0;
         shape[3][0]=BOARD_WIDTH/2+1;
         shape[3][1]=1;
         break;
   }
}

void print_block()//to print different colours for each block
{
   if(shape_type==1)
   {
      for(int i=0;i<4;i++)
      {
      board[shape[i][1]][shape[i][0]]=1;
      } 
   }
   if(shape_type==2)
      {
      for(int i=0;i<4;i++)
      {
      board[shape[i][1]][shape[i][0]]=2;
      } 
   }
   if(shape_type==3)
   {
      for(int i=0;i<4;i++)
      {
      board[shape[i][1]][shape[i][0]]=3;
      } 
   }
   if(shape_type==4)
   {
      for(int i=0;i<4;i++)
      {
      board[shape[i][1]][shape[i][0]]=4;
      } 
   }
   if(shape_type==5)
   {
      for(int i=0;i<4;i++)
      {
      board[shape[i][1]][shape[i][0]]=5;
      } 
   }
   if(shape_type==6)
   {
      for(int i=0;i<4;i++)
      {
      board[shape[i][1]][shape[i][0]]=6;
      } 
   }
   if(shape_type==7)
   {
      for(int i=0;i<4;i++)
      {
      board[shape[i][1]][shape[i][0]]=7;
      } 
   }
}

void clear_block()
{
   for(int i=0;i<4;i++)
   {
      board[shape[i][1]][shape[i][0]]=0;
   }
}

void rotate()//clockwise rotation
{
   float x0,y0;
   if(shape_type==5)
   {
   return;
   }
   if(shape_type==1||shape_type==3||shape_type==4||shape_type==6||shape_type==7)
   {
   x0=shape[0][0];
   y0=shape[0][1];
   }
   if(shape_type==2)
   {
   int sum_x=0,sum_y=0;
   for (int i=0;i<4;i++)
   {
      sum_x+=shape[i][0];
      sum_y+=shape[i][1];
   }
   x0=sum_x/4;
   y0=sum_y/4;
   }
   for (int i=0;i<4;i++) 
   {
   float x=shape[i][0]-x0;
   float y=shape[i][1]-y0;
   shape[i][0]=x0-y;
   shape[i][1]=y0+x;
   }
}

void anti_rotate()//anti-clockwise rotation
{
   float x0,y0;
   if(shape_type==5)
   {
   return;
   }
   if(shape_type==1||shape_type==3||shape_type==4||shape_type==6||shape_type==7)
   {
   x0=shape[0][0];
   y0=shape[0][1];
   }
   if(shape_type==2)
   {
   int sum_x=0,sum_y=0;
   for (int i=0;i<4;i++)
   {
      sum_x+=shape[i][0];
      sum_y+=shape[i][1];
   }
   x0=sum_x/4;
   y0=sum_y/4;
   }
   for (int i=0;i<4;i++) 
   {
   float x=shape[i][0]-x0;
   float y=shape[i][1]-y0;
   shape[i][0]=x0+y;
   shape[i][1]=y0-x;
   }
}

void rotate_shape()
{
   clear_block();
   rotate();
   for(int i=0;i<4;i++) 
   {
      if(shape[i][0]<0||board[shape[i][1]][shape[i][0]]!=0||shape[i][0]>BOARD_WIDTH-1)
      {
         anti_rotate();
      }
    }
    print_block();
}

/*tetrimino can be moved sidewards unless it is stuck by sides of board*/
void move_shape_left()
{
   clear_block();
   for(int i=0;i<4;i++) 
   {
      if(shape[i][0]==0||board[shape[i][1]][shape[i][0]-1]!=0)
      {
         return;
      }
   }
   for(int i=0;i<4;i++) 
   {
      shape[i][0]--;
   }
   print_block();
}

void move_shape_right()
{
   clear_block();
   for(int i=0;i<4;i++) 
   {
      if(shape[i][0]==BOARD_WIDTH-1||board[shape[i][1]][shape[i][0]+1]!=0) 
      {
         return;
      }
   }
   for(int i=0;i<4;i++) 
   {
      shape[i][0]++;
   }
   print_block();
}

void move_shape_down1()/*tetrimino can be moved down unless it is stuck by the bottom of the board or any other block below it*/
{
   clear_block();
   for(int i=0;i<4;i++) 
   {
      if(shape[i][1]==BOARD_HEIGHT-1||board[shape[i][1]+1][shape[i][0]]!=0)
      {
         print_block();
         return;
      }
   }
   for(int i = 0; i < 4; i++)
   {
      shape[i][1]++;
   }
    print_block();
}

int new_block()//when the tetrimino reaches the bottom of the possible board a new tetrimino starts to fall
{
   clear_block();
   for(int i=0;i<4;i++) 
   {
      if(shape[i][1]==BOARD_HEIGHT-1||board[shape[i][1]+1][shape[i][0]]!=0)
      {
         return 1;
      }
   }
    return 0;
}

void sudden_drop()//to hard drop the block to the bottom of the game
{
   while(!new_block())
   {
      move_shape_down1();
   }
   print_block();
}

void cont_dropping()//to increase the difficulty of the game the tetrimino fall continuously per second
{
      if(!new_block())
      {
         gotoxy(0,0);
         move_shape_down1();
         print_board();
         if(score<600)
         Sleep(600);
         else if(score<1200||score>=500)
         Sleep(500);
         else
         Sleep(400);
      }
}

void clear_lines()//one whole row gets filed with blocks the row gets cleared
{
   int n=0;
   for(int i=BOARD_HEIGHT-1;i>=0;i--) 
   {
      int j;
      for(j=0;j<BOARD_WIDTH;j++) 
      {
         if(board[i][j]==0||board[i][j]==8) 
         {
            break;
         }
      }
      if(j==BOARD_WIDTH) 
      {
         for(int k=i;k>0;k--) 
         {
            for(int l=0;l<BOARD_WIDTH;l++) 
            {
               board[k][l]=board[k-1][l];
            }
         }
         for (int l=0;l<BOARD_WIDTH;l++)
         {
            board[0][l]=0;
         }
         i++;
         score+=100;
      }
   }
}

int gameover()//if the block got stuck at the top row,game ends
{
   for(int i=0;i<BOARD_WIDTH;i++) 
   {
      if(board[0][i]!= 0) 
      {
         return 1;
      }
   }
   return 0;
}

void start()//game play
{
   create_board();
   new_random_shape();
   int is_game_paused=0;
   char direction;
   int gameRunning = 1;
   system("cls");
   score=0;
   while(gameRunning)
   {
      print_block();
      print_board();
      if(!_kbhit())
      {
         cont_dropping();
      }
      else
      {
         char key= _getch();
         switch(key) 
         {
            case 'Y':
            case 'y':
               is_game_paused=1;
               printf("\t\t\t\t\t  enter 'y' to continue the game");
               while(is_game_paused)
               {
                  char key1=_getch();
                  if(key1=='y'||key1=='Y')
                  {
                     system("cls");
                     print_board();
                     is_game_paused=0;
                     break;
                  }
               }
               break;
            case 'L':
            case 'l':
            case 75:
               move_shape_left();
               break;
            case 'R':
            case 'r':
            case 77:
               move_shape_right();
               break;
            case 'D':
            case 'd':
            case 80:
               move_shape_down1();
               break;
            case 'A':
            case 'a':
            case 72:
               rotate_shape();
               break;
            case 'S':
            case 's':
            case 32:
               sudden_drop();
               break;
            case 'Q':
            case 'q':
               gameRunning = 0;
               break;
            cont_dropping();
         }
      }
      if(new_block())
      {
         print_block();
         if(!_kbhit())
         {
            new_random_shape();
         }
         else
         {
            char key= _getch();
            switch(key) 
            {
               case 'Y':
               case 'y':
                  is_game_paused=1;
                  printf("\t\t\t\t\t  enter 'y' to continue the game");
                  while(is_game_paused)
                  {
                     char key1=_getch();
                     if(key=='y'||key=='Y')
                     {
                        system("cls");
                        print_board();
                        is_game_paused=0;
                        break;
                     }
                  }
                  break;
               case 'L':
               case 'l':
               case 75:
                  move_shape_left();
                  break;
               case 'R':
               case 'r':
               case 77:
                  move_shape_right();
                  break;
               case 'D':
               case 'd':
               case 80:
                  move_shape_down1();
                  break;
               case 'A':
               case 'a':
               case 72:
                  rotate_shape();
                  break;
               case 'S':
               case 's':
               case ' ':
                  sudden_drop();
                  break;
               case 'Q':
               case 'q':
                  gameRunning = 0;
                  break;
               new_random_shape();
            }
         }
      }
      clear_lines();
      if(gameover())
      {
         gameRunning=0;
         for(int i=BOARD_HEIGHT-1;i>=0;i--)
         {
            system("cls");
            for(int j=0;j<BOARD_WIDTH;j++)
            {
               board[i][j]=8;
            }
            print_board();
         }
      }
      gotoxy(0,0);
   }
   system("cls");
   printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tGameover!!");
   printf("Your Final score is %d",score);
   Sleep(5000);
   return;
}

void tetris()//word tetris on intro board
{
   int tetris[5][21]={0};
   tetris[0][0]=1,tetris[0][1]=1,tetris[0][2]=1,tetris[0][4]=2,tetris[0][5]=2,tetris[0][6]=2,tetris[0][8]=3,tetris[0][9]=3,tetris[0][10]=3,tetris[0][12]=4,tetris[0][13]=4,tetris[0][14]=4,tetris[0][16]=5,tetris[0][18]=6,tetris[0][19]=6,tetris[0][20]=6;
   tetris[1][1]=1,tetris[1][4]=2,tetris[1][9]=3,tetris[1][12]=4,tetris[1][14]=4,tetris[1][16]=5,tetris[1][18]=6;
   tetris[2][1]=1,tetris[2][4]=2,tetris[2][5]=2,tetris[2][6]=2,tetris[2][9]=3,tetris[2][12]=4,tetris[2][13]=4,tetris[2][13]=4,tetris[2][16]=5,tetris[2][18]=6,tetris[2][19]=6,tetris[2][20]=6;
   tetris[3][1]=1,tetris[3][4]=2,tetris[3][9]=3,tetris[3][12]=4,tetris[3][14]=4,tetris[3][16]=5,tetris[3][20]=6;
   tetris[4][1]=1,tetris[4][4]=2,tetris[4][5]=2,tetris[4][6]=2,tetris[4][9]=3,tetris[4][12]=4,tetris[4][14]=4,tetris[4][16]=5,tetris[4][18]=6,tetris[4][19]=6,tetris[4][20]=6;
   for(int i=0;i<5;i++){
      printf("\t\t\t");
      for(int j=0;j<21;j++){
         if(tetris[i][j]==0)
         printf(BLACK"|%c%c"RESET,219,219);
         else if(tetris[i][j]==1)
         printf("|"YELLOW "%c%c"RESET,219,219);
         else if(tetris[i][j]==2)
         printf("|"RED "%c%c"RESET,219,219);
         else if(tetris[i][j]==3)
         printf("|"BLUE "%c%c"RESET,219,219);
         else if(tetris[i][j]==4)
         printf("|"MAGENTA "%c%c"RESET,219,219);
         else if(tetris[i][j]==5)
         printf("|"CYAN "%c%c"RESET,219,219);
         else if(tetris[i][j]==6)
         printf("|"GREEN "%c%c"RESET,219,219);
         else if(tetris[i][j]==7)
         printf("|"DARKRED "%c%c"RESET,219,219);
      }
      printf(BLACK"|"RESET"\n");
   }
}

void tetriminos()//types of tetriminoes
{
   int intro[4][33]={0};
   intro[2][0]=2,intro[2][1]=2,intro[2][2]=2,intro[2][3]=2,intro[2][6]=3,intro[2][7]=3,intro[2][8]=3,intro[2][11]=4,intro[2][17]=7,intro[2][18]=7,intro[2][21]=6,intro[2][22]=6,intro[2][27]=1,intro[2][31]=5,intro[2][32]=5;
   intro[1][6]=3,intro[1][11]=4,intro[1][12]=4,intro[1][13]=4,intro[1][16]=7,intro[1][17]=7,intro[1][22]=6,intro[1][23]=6,intro[1][26]=1,intro[1][27]=1,intro[1][28]=1,intro[1][31]=5,intro[1][32]=5;
   printf("\t");
   for(int i=0;i<100;i++){
      printf("~");
   }
   printf("\n");
   for(int i=0;i<4;i++){
      printf("\t");
      for(int j=0;j<33;j++){
         if(intro[i][j]==0)
         printf(BLACK"|%c%c"RESET,219,219);
         else if(intro[i][j]==1)
         printf("|"YELLOW "%c%c"RESET,219,219);
         else if(intro[i][j]==2)
         printf("|"RED "%c%c"RESET,219,219);
         else if(intro[i][j]==3)
         printf("|"BLUE "%c%c"RESET,219,219);
         else if(intro[i][j]==4)
         printf("|"MAGENTA "%c%c"RESET,219,219);
         else if(intro[i][j]==5)
         printf("|"CYAN "%c%c"RESET,219,219);
         else if(intro[i][j]==6)
         printf("|"GREEN "%c%c"RESET,219,219);
         else if(intro[i][j]==7)
         printf("|"DARKRED "%c%c"RESET,219,219);
      }
      printf(BLACK"|"RESET"\n");
   }
   printf("\t");
   for(int i=0;i<100;i++){
      printf("~");
   }
}

int main()
{
   system("cls");
   hidecursor();
   tetris();//put your terminal window to full screen
   srand(time(0));
   printf("\n\t\t\t\t\t\tGame Tetris!!!\n\n");
   printf("Given below are the 7 types of tetriminos\n\n");
   tetriminos();
   printf("\n\n");
   printf("\nEnter (d to move down, l to move left, r to move right, a to rotate,s to hard drop,y to pause,q to quit) OR\n");
   printf("Enter (%c to move down,<- to move left,-> to move right,%c to rotate,spacebar to hard drop)\n",25,24);
   printf("On clearing each line you earn 100pts. \n"
   "\t\t\t\t\tSmash" YELLOW" Enter"RESET" to start the game");
   if(getch()==13)
   start();
}