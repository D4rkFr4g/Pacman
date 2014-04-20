#include "paclib.h"

#define mapW 28
#define mapH 31


//------------------------------------------------------------------------------
void loadLvl1Array(std::vector<std::vector<int>>& map, PM* pacman, GHOST* ghost, WALLWALK* wallhole)
{
   int dataIn;
   int loader = 0;
   FILE* fpData;

   int size = mapW * mapH;
   int x = 0;
   int y = 0;
   int wall = 1;
  
   ghost->timer = 0;  
  
   if (pacman->level == 1)
   {
      if (!(fpData = fopen ("lvlone.dat", "r")))
         printf("Error opening file\n") , exit (100);
   }
  
   if (pacman->level == 2)
   {
      if (!(fpData = fopen ("lvltwo.dat", "r")))
         printf("Error opening file\n") , exit (100);
   } 
     
   if (pacman->level == 3)
   {
      if (!(fpData = fopen ("lvlthree.dat", "r")))
         printf("Error opening file\n") , exit (100);
   } 
 
   while (loader < size)
   {
      for (y = 0; y < mapH; y++)
      {
         for (x = 0; x < mapW; x++)
         {
            if (fscanf(fpData, "%d", &dataIn) != EOF)
            {
               // if (loader = 500)
               // {printf("\n%d", dataIn); system("pause");}
                   
               if (dataIn >= 0)
               {
                  map[x][y] = dataIn;

                  loader++;
                  if (map[x][y] == 3)
                  {
                     pacman->x = x; 
                     pacman->y = y;
                     pacman->startx = x; 
                     pacman->starty = y;
                  }
                      
                  if (map[x][y] == 4)
                  {
                     ghost->x = x;
                     ghost->y = y;
                     ghost->startx = x;
                     ghost->starty = y;
                  }
                      
                  if (map[x][y] == 8)
                  {
                     if (wall == 1)
                     {
                        wallhole->x = x;
                        wallhole->y = y;
                        wall = 2;
                     }
                     else
                     {
                        wallhole->x2 = x;
                        wallhole->y2 = y;
                     }
                  }

                  //printf("%d ", dataIn);
               }
            }
         }
      //printf("\n");
      }
   }

   //-----Debug Code--------------------------------------
   // Verifies last digit from file made it into the array
   //-----------------------------------------------------
   //  printf("\n%d", map[mapW-1][mapH-1]);
   //  system("pause");   
   //-----------------------------------------------------
}//End of void loadLvl1Array(int map[][])
//------------------------------------------------------------------------------
void printArray(std::vector<std::vector<int>>& map, PM pacman, GHOST ghost)
{
   int x = 0;
   int y = 0;

   printf("\n\n\n");

   for (y = 0; y < mapH; y++)
   {
      for (x = 0; x < mapW; x++)
      {
         //printf("%d ", x);
         //printf("%d ", map[x][y]);
               
         if (map[x][y] == 0)
            printf("  ");
         else if (map[x][y] == 1)
            printf(". ");
         else if (map[x][y] == 2)
            printf("@ ");
         else if (map[x][y] == 3)
         {
            if (pacman.face == 0)
               printf("C ");
            else if (pacman.face == 1)
               printf("O ");
         }
         else if (map[x][y] == 4)
         {
            if (ghost.phantom == 0)
               printf("$ ");
            else if (ghost.phantom == 1)
               printf("& ");
         }
         else if (map[x][y] == 5)
            printf("# ");
         else if (map[x][y] == 6)
            printf("  ");
         else if (map[x][y] == 7)
            printf("- ");
         else if (map[x][y] == 8)
            printf("  ");
      }
      
      printf(" \n");
   }
}//End of void printArray()
//------------------------------------------------------------------------------
void printDebug(std::vector<std::vector<int>>& map)
{
   int x = 0;
   int y = 0;
     
   printf("\n\n\n");
     
   for (y = 0; y < mapH; y++)
   {
      for (x = 0; x < mapW; x++)
         printf("%d ", map[x][y]);
      
      printf(" \n");
   }
}//End of void printDebug(int map[][])
//------------------------------------------------------------------------------
void pickDirection(PM *pacman, int *debugMode)
{
   int choice = 0;
     
   if (kbhit())
   {
      printf ("\n");
      choice = getch();
        
      //***********************
      //**** Debug Code *******
      //***********************
      //Displays key press number
      //*************************
        
      //printf("\nchoice = %d", choice);
      //system("pause");
      //***********************
   }
     
   if (choice == 72)
      pacman->direction = 1;
   if (choice == 77)
      pacman->direction = 2;
   if (choice == 80)
      pacman->direction = 3;
   if (choice == 75)
      pacman->direction = 4;

   if (choice == 96)
   {
      *debugMode = *debugMode + 1; 
      
      if (*debugMode == 2)
      {
         *debugMode = 0;
      }
   }//printDebug(M);}
     
   if (choice == 112)
   {
      printf("\nGame Paused");
      while (getch() != 112);
   }
}//End of void pickDirection (PM *PacmanDirection, int *debugMode)
//------------------------------------------------------------------------------
void movePacman(std::vector<std::vector<int>>& map, PM* pacman)
{
   //1 = N, 2 = E, 3 = S, 4 = W
     
   map[pacman->x][pacman->y] = 0; //Leaves the previous Pacman spot empty
     
   switch (pacman->direction)
   {
      case 1: pacman->y = pacman->y - 1;
            break;
      case 2: pacman->x = pacman->x + 1;
            break;
      case 3: pacman->y = pacman->y + 1;
            break;
      case 4: pacman->x = pacman->x - 1;
            break;
   }
     
   //Sets the boundaries for pacman   //Might cause an issue in the wall walk
   if (pacman->x >= mapW)
      pacman->x = mapW - 1;
   if (pacman->x <= 0)
      pacman->x = 0;
   if (pacman->y >= mapH)
      pacman->y = mapH - 1;
   if (pacman->y <= 0)
      pacman->y = 0;
        
   map[pacman->x][pacman->y] = 3;   // Places pacman in the next spot

}
//-------------------------------------------------------------------------------------
void checkDirection(std::vector<std::vector<int>>& map, PM pacman, int *canMove, int *pacmanface)
{
   //   1 = N, 2 = E, 3 = S, 4 = W
     
   switch (pacman.direction)
   {           
      case 1: pacman.y = pacman.y - 1;
            break;
      case 2: pacman.x = pacman.x + 1;
            break;
      case 3: pacman.y = pacman.y + 1;
            break;
      case 4: pacman.x = pacman.x - 1;
            break;       
   }
     
   if (pacman.y < mapH && pacman.x < mapW && pacman.y >= 0 && pacman.x >=0)
   {
      if (map[pacman.x][pacman.y] != 5 && map[pacman.x][pacman.y] != 7)
      {
         *canMove = 1;
           
         if (pacman.direction != 0)
         {
            *pacmanface = *pacmanface + 1;
            if(*pacmanface == 2)
               *pacmanface = 0;
         }
      }
      else
         *canMove = 0;
   }
   else
      *canMove = 0;
     
}//End of void checkDirection ( int map[][], int *PacmanDirection, int *canMove)
//------------------------------------------------------------------------------
void printHeader(int score, int lives)
{
   printf("\n\t      **** Zane's PACMAN ****");
   printf("\n\n\tScore = %d\t\tLives = %d", score, lives);    
}
//------------------------------------------------------------------------------
void wallWalk(std::vector<std::vector<int>>& map, PM* pacman, WALLWALK wallhole)
{
   //   1 = N, 2 = E, 3 = S, 4 = W
     
   int x=0;
   int y=0;
     
   x = pacman->x;
   y = pacman->y;
     
   switch (pacman->direction)
   {           
      case 1: y = y - 1;
            break;
      case 2: x = x + 1;
            break;
      case 3: y = y + 1;
            break;
      case 4: x = x - 1;
            break;       
   }
     
   if (x == wallhole.x && y == wallhole.y)
   { 
      map[pacman->x][pacman->y] = 0;
      pacman->x = wallhole.x2;
      pacman->y = wallhole.y2;
      map[pacman->x][pacman->y] = 3;     
   }
     
   if (x == wallhole.x2 && y == wallhole.y2)
   { 
      map[pacman->x][pacman->y] = 0;
      pacman->x = wallhole.x;
      pacman->y = wallhole.y;
      map[pacman->x][pacman->y] = 3;
   } 
}
//------------------------------------------------------------------------------
void checkScore(std::vector<std::vector<int>>& map, PM pacman, int *score, GHOST* ghost, int* phantomTime)
{
   //   1 = N, 2 = E, 3 = S, 4 = W

          
   switch (pacman.direction)
   {           
      case 1: pacman.y = pacman.y - 1;
            break;
      case 2: pacman.x = pacman.x + 1;
            break;
      case 3: pacman.y = pacman.y + 1;
            break;
      case 4: pacman.x = pacman.x - 1;
            break;       
   }
     
   if (map[pacman.x][pacman.y] == 1)  // Dots
   {
      *score = *score + 10;
   }
   if (map[pacman.x][pacman.y] == 2)  // Power-ups
   {
      *score = *score + 20;
      ghost->phantom = 1;
      *phantomTime = 0;
   }
   if (map[pacman.x][pacman.y] == 4 && ghost->phantom == 1)  // Phantom Ghosts
   {
      *score = *score + 50;
      ghost->x = ghost->startx;
      ghost->y = ghost->starty;
      ghost->temp = 0;
      ghost->temp2 = 0;
      ghost->phantom = 0;
      ghost->timer = 0;
   }
   if (map[pacman.x][pacman.y] == 8)  // Fruit
      *score = *score + 50;

}
//------------------------------------------------------------------------------
void checkLvlOver(std::vector<std::vector<int>>& map, int *gameOver, PM* pacman, int* nextLevel)
{
   int x;
   int y;
   int found = 0;
     
   for (x = 0; x < mapW; x++)
   {
      for (y = 0; y < mapH; y++)
      {
            if (map[x][y] == 1 || map[x][y] == 2)
               found = 1;
      }
   }
     
   if (!found)
   {
      Sleep(100);
      printf("\n\n**** Level Compelete ****");
      pacman->level = pacman->level + 1;
      
      if (pacman->level > 3)
         pacman->level = 1;

      *gameOver = 1;
      *nextLevel = 1;
   }
}
//------------------------------------------------------------------------------
void printLogo()
{
   system("cls");
     
   printf("\n\t\t\t****** Melchomedia Presents ******");
   printf("\n\n\n");
   printf("\n\t*******************************************************************"); 
   printf("\n\t*                                                                 *");        
   printf("\n\t*    P P       A      C C C         MM   MM      A      N    N    *");
   printf("\n\t*    P   P    A A     C             M M M M     A A     NN   N    *");
   printf("\n\t*    P P     A   A    C      = = =  M  M  M    A   A    N N  N    *");
   printf("\n\t*    P      A  A  A   C      = = =  M     M   A  A  A   N  N N    *");
   printf("\n\t*    P      A     A   C C C         M     M   A     A   N   NN    *");
   printf("\n\t*                                                                 *");
   printf("\n\t*******************************************************************");
   printf("\n\n");
     
   printf("\nControls");
   printf("\n--------");
   printf("\n");
   printf("\nMove  - Arrow Keys");
   printf("\nPause - P key");
   printf("\nArray - ` key");
     
   printf("\n\n");
   printf("\n\t\t\t");
   system("pause");
}

