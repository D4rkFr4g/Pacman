#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <conio.h>

#ifndef PM_STRUCTS
#define PM_STRUCTS
typedef struct
{
      int x;
      int y;
      int direction;
      int phantom;
      int temp;
      int temp2;
      int time;
      int out;
      int startx;
      int starty;
      int flip;
      int timer;  
}GHOST;

typedef struct
{
      int x;
      int y;
      int direction;
      int face;
      int startx;
      int starty;
      int lives;
      int level;
}PM;

typedef struct
{
      int x;
      int y;
      int x2;
      int y2;          
}WALLWALK;
#endif

void ghostCheckDirectionX(std::vector<std::vector<int>>& map, GHOST* ghost, PM pacman);

void ghostCheckDirectionY(std::vector<std::vector<int>>& map, GHOST* ghost, PM pacman);

void moveGhost(std::vector<std::vector<int>>& map, GHOST* ghost);

void ghostWallWalk(std::vector<std::vector<int>>& map, GHOST* ghost, WALLWALK wallhole);

void checkDeath(std::vector<std::vector<int>>& map, GHOST* ghost, PM* pacman, int *gameOver); 

void debug(GHOST* ghost);

void phantomTimer(GHOST* ghost, int* phantomTime);

void ghostTimer(std::vector<std::vector<int>>& map, GHOST* ghost);
