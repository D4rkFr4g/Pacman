#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <Windows.h>
#include "ghost.h"
#include "paclib.h"

#define mapW 28
#define mapH 31


int main()
{
   //-------------Variable Declaration----------------------------  
   
   //int map[mapW][mapH] = {0};
   std::vector<std::vector<int>> map;
   map.resize(mapW);
   for (int i = 0; i < mapW; i++)
      map[i].resize(mapH);

   int debugMode = 0;

   int gameOver = 0;
   int gameAgain = 1;
   char choice = 'n';
   int canMove = 0;
   int score = 0;
   int nextLevel = 0;
   int phantomTime = 0;


   PM pacman;
   GHOST ghost;
   WALLWALK wallhole;

   pacman.direction = 0;
   pacman.face = 0;
   pacman.x = 0;
   pacman.y = 0;
   pacman.lives = 3;
   pacman.level = 1;

   ghost.direction = 2;
   ghost.temp = 0;
   ghost.temp2 = 0;
   ghost.flip = 1;
   ghost.phantom = 0;
   ghost.timer = 0;
   ghost.time = 0;


   //-------------Main Code---------------------------------------

   loadLvl1Array(map, &pacman, &ghost, &wallhole);

   printLogo();

   while (gameAgain)
   {

      while (!gameOver)
      {

      pacman.direction = 0; //Resets direction, so extra moves aren't made when !kbhit()

      system("cls");

      //debug(&ghost);
      //printf("\nGhost.phantom = %d", ghost.phantom);

      printHeader(score, pacman.lives);
      if (!debugMode)
         printArray(map, pacman, ghost);
      else if (debugMode)
         printDebug(map);

      if (nextLevel == 1)
         system("pause"); nextLevel = 0;

      checkLvlOver(map, &gameOver, &pacman, &nextLevel);

      pickDirection(&pacman, &debugMode);

      checkDirection(map, pacman, &canMove, &pacman.face);

      if (ghost.flip == 1)
         ghostCheckDirectionY(map, &ghost, pacman);
      else if (ghost.flip == 2)
         ghostCheckDirectionX(map, &ghost, pacman);

      wallWalk(map, &pacman, wallhole);
      ghostWallWalk(map, &ghost, wallhole);

      checkScore(map, pacman, &score, &ghost, &phantomTime);

      if (canMove)
         movePacman(map, &pacman);

      moveGhost(map, &ghost);
      ghostTimer(map, &ghost);

      if (ghost.phantom == 1)
         phantomTimer(&ghost, &phantomTime);

      checkDeath(map, &ghost, &pacman, &gameOver);

      Sleep(20);

      }//End of while (!gameOver)

      if (!nextLevel)
      {
         system("cls");
         printf("\n\n\n\n\n\n\n\n\n\n\n\n");
         printf("\n\t\t***********************");
         printf("\n\t\t*      GAME OVER      *");
         printf("\n\t\t***********************");
         printf("\n\n\n");
         printf("\nWould you like to play again? y/n ");
         scanf(" %c", &choice);

         if (choice == 'n' || choice == 'N'){gameAgain = 0;}
         else if (choice == 'y' || choice == 'Y')
         {
              gameAgain = 1;
              gameOver = 0;
              ghost.time = 0;
              ghost.timer = 0;
              ghost.temp = 0;
              ghost.temp2 = 0;
              loadLvl1Array(map, &pacman, &ghost, &wallhole);
              pacman.lives = 3;
              pacman.level = 1;
              score = 0;
      
         }
      }//End of if (!nextLevel)

      if (nextLevel)
      {
           gameOver = 0;
           loadLvl1Array(map, &pacman, &ghost, &wallhole);
      }

   }//End of while (gameAgain);
  	
}// End of Main()
