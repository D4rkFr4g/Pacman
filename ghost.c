#include "ghost.h"

#define mapW 28
#define mapH 31


//------------------------------------------------------------------------------
void debug(GHOST* ghost)
{
   int choice = 0;
          
   if (kbhit())
   {
      choice = getch();
        
      if (choice == 49)
         ghost->phantom = ghost->phantom + 1;
      if (ghost->phantom == 2)
         ghost->phantom = 0;
   }
}
//------------------------------------------------------------------------------
void ghostCheckDirectionY(std::vector<std::vector<int>>& map, GHOST* ghost, PM pacman) // Original
{
   //direction 1 = N, 2 = E, 3 = S, 4 = W
   int canMove = 0;
   int ghostSpeed = 5;
   int x;
   int y;
     
   if (ghost->phantom == 0)
   {
      x = pacman.x;
      y = pacman.y;
   }
   if (ghost->phantom == 1)
   {
      x = ghost->startx;
      y = ghost->starty;    
   }
   if (ghost->time == ghostSpeed)
   { 
      map[ghost->x][ghost->y] = ghost->temp2;
     
      if (ghost->direction == 1)
      {
         if (map[ghost->x][ghost->y-1] == 5)
         {
            if (map[ghost->x+1][ghost->y] !=5)
               ghost->direction = 2;
            else if (map[ghost->x-1][ghost->y] !=5)
               ghost->direction = 4;
         }
      }
      else if (ghost->direction == 3)
      {
         if (map[ghost->x][ghost->y+1] == 5)
         {
            if (map[ghost->x+1][ghost->y] !=5)
               ghost->direction = 2;
            else if (map[ghost->x-1][ghost->y] !=5)
               ghost->direction = 4;
         }     
      }
     
      if (map[ghost->x-1][ghost->y] == 5)
      {
	      if (map[ghost->x+1][ghost->y] != 5)
            ghost->direction = 2;
      }
      if (map[ghost->x+1][ghost->y] == 5)
      {
	      if (map[ghost->x-1][ghost->y] !=5)
            ghost->direction = 4;
      }
      if (ghost->y < y)  // If ghost is below  - Go South
      {
	      if (map[ghost->x][ghost->y+1] != 5)
		      ghost->direction = 3;
      }
      else if (ghost->y > y) //If ghost is above - Go North
      {
	      if (map[ghost->x][ghost->y-1] != 5)
		      ghost->direction = 1;
      }
      /*
      printf("\nGhost->direction = %d", ghost->direction);
      printf("\n");
      sleep(500);
      */
     
   }//End of if (ghost->time == ghostSpeed) 

   if (ghost->y == y)
      ghost->flip = 2;
     
}
//------------------------------------------------------------------------------
void ghostCheckDirectionX(std::vector<std::vector<int>>& map, GHOST* ghost, PM pacman)
{
   //direction 1 = N, 2 = E, 3 = S, 4 = W
   int canMove = 0;
   int ghostSpeed = 5;

   int x;
   int y;
     
   if (ghost->phantom == 0)
   {
      x = pacman.x;
      y = pacman.y;
   }
   if (ghost->phantom == 1)
   {
      x = ghost->startx;
      y = ghost->starty;
   } 

   if (ghost->time == ghostSpeed)
   { 
      map[ghost->x][ghost->y] = ghost->temp2;
     
      if (ghost->direction == 2) // If going ->
      {
         if (map[ghost->x+1][ghost->y] == 5)
         {
            if (map[ghost->x][ghost->y-1] !=5)
               ghost->direction = 1;
            else if (map[ghost->x][ghost->y+1] !=5)
               ghost->direction = 3;
         }
      }
      else if (ghost->direction == 4)
      {
         if (map[ghost->x-1][ghost->y] == 5)
         {
            if (map[ghost->x][ghost->y-1] !=5)
               ghost->direction = 1;
            else if (map[ghost->x][ghost->y+1] !=5)
               ghost->direction = 3;
         }     
      }
     
      if (map[ghost->x][ghost->y-1] == 5)
      {
	      if (map[ghost->x][ghost->y+1] != 5)
            ghost->direction = 3;
      }
      if (map[ghost->x][ghost->y+1] == 5)
      {
	      if (map[ghost->x][ghost->y-1] !=5)
            ghost->direction = 1;
      }

      if (ghost->x < x)  // If ghost is below  - Go South
      {
	      if (map[ghost->x+1][ghost->y] != 5)
		      ghost->direction = 2;
      }
      else if (ghost->x > x) //If Ghost is above - Go North
      {
	      if (map[ghost->x-1][ghost->y] != 5)
		      ghost->direction = 4;
      }
      /*
      printf("\nGhost->direction = %d", ghost->direction);
      printf("\n");
      */

   }//End of if (ghost->time == ghostSpeed) 

   if (ghost->x == x)
      ghost->flip = 1;

}
//------------------------------------------------------------------------------
void moveGhost(std::vector<std::vector<int>>& map, GHOST* ghost)
{
   //1 = N, 2 = E, 3 = S, 4 = W
   int temp = 0;
   int ghostSpeed = 5;

   //Replaces Original Spot 
    
   if (ghost->time == ghostSpeed)
   {   
      map[ghost->x][ghost->y] = ghost->temp2;
     
      switch (ghost->direction)
      {
            case 1: ghost->y = ghost->y - 1;
                  break;
            case 2: ghost->x = ghost->x + 1;
                  break;
            case 3: ghost->y = ghost->y + 1;   
                  break;
            case 4: ghost->x = ghost->x - 1;
                  break;
      }

      ghost->temp = map[ghost->x][ghost->y];
      ghost->temp2 = ghost->temp;
      //printf("\nghost->x = %d\nghost->y = %d\nghost->temp = %d\nghost->temp2 = %d", ghost->x, ghost->y, ghost->temp, ghost->temp2);
      //printf("\n");
      //system("pause");
     
      //Sets the boundaries for the ghost Kinda redunant since the ghost can't move past a wall.
      if (ghost->x >= mapW)
         ghost->x = mapW - 1;
      if (ghost->x <= 0)
         ghost->x = 0;
      if (ghost->y >= mapH)
         ghost->y = mapH - 1;
      if (ghost->y <= 0)
         ghost->y = 0;

      map[ghost->x][ghost->y] = 4;   // Places ghost in the next spot
   }

   ghost->time = ghost->time + 1;
   if (ghost->time > ghostSpeed)
      ghost->time = 0;

}//End of void moveGhost(std::vector<std::vector<int>>& map, GHOST* ghost,int* ghostTemp, int* ghostTime)
//------------------------------------------------------------------------------             
void ghostWallWalk(std::vector<std::vector<int>>& map, GHOST* ghost, WALLWALK wallhole)
{
   //   1 = N, 2 = E, 3 = S, 4 = W
     
   int x=0;
   int y=0;
     
   x = ghost->x;
   y = ghost->y;
     
   switch (ghost->direction)
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
      map[ghost->x][ghost->y] = 0;
      ghost->x = wallhole.x2;
      ghost->y = wallhole.y2;
      map[ghost->x][ghost->y] = 4;     
   }
     
   if (x == wallhole.x2 && y == wallhole.y2)
   { 
      map[ghost->x][ghost->y] = 0;
      ghost->x = wallhole.x;
      ghost->y = wallhole.y;
      map[ghost->x][ghost->y] = 4;
   }
}
//------------------------------------------------------------------------------
void checkDeath(std::vector<std::vector<int>>& map, GHOST* ghost, PM* pacman, int *gameOver)
{
   if (ghost->x == pacman->x && ghost->y == pacman->y && ghost->phantom == 0)
   {
      pacman->lives = pacman->lives - 1;
        
      if (pacman->lives > 0)
      {            
         printf("\nYou Got Dead!!!");
         printf("\n%d Lives Left", pacman->lives);
         printf("\n\n\n");
         system("pause");
        
         map[pacman->x][pacman->y] = 0;
         pacman->x = pacman->startx;
         pacman->y = pacman->starty;
        
         map[ghost->x][ghost->y] = 0;
         ghost->temp = 0;
         ghost->temp2 = 0;
         ghost->x = ghost->startx;
         ghost->y = ghost->starty;
         ghost->timer = 0;
      }
   }
     
   if (pacman->lives == 0)
      *gameOver = 1;

}
//------------------------------------------------------------------------------
void phantomTimer(GHOST* ghost, int* phantomTime)
{
   *phantomTime = *phantomTime + 1;
   // printf("\n*phantomTime = %d", *phantomTime);
     
   if (*phantomTime == 150)
   {
      *phantomTime = 0;
      ghost->phantom = 0;                 

      // printf("\nResetting Ghost\n");
      // system("pause");
   }
}
//------------------------------------------------------------------------------
void ghostTimer(std::vector<std::vector<int>>& map, GHOST* ghost)
{
   ghost->timer = ghost->timer + 1;

   //printf("\nghost->timer = %d", ghost->timer);     
   if (ghost->timer == 50)
   {
      map[ghost->x][ghost->y] = 0;
      ghost->x = 13;
      ghost->y = 11;
   }     
}
