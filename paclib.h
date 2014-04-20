#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <conio.h>
#include <Windows.h>

#ifndef PM_STRUCTS
#define PM_STRUCTS
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
      int x2;
      int y2;          
}WALLWALK;
#endif

void loadLvl1Array(std::vector<std::vector<int>>& map, PM* pacman, GHOST* ghost, WALLWALK* wallhole);

void printArray(std::vector<std::vector<int>>& map, PM pacman, GHOST ghost);

void printDebug(std::vector<std::vector<int>>& map);

void pickDirection(PM *pacman, int *debugMode);

void checkDirection(std::vector<std::vector<int>>& map, PM pacman, int *canMove, int* pacmanFace);

void movePacman(std::vector<std::vector<int>>& map, PM* pacman);

void printHeader(int score, int lives);

void wallWalk(std::vector<std::vector<int>>& map, PM* pacman, WALLWALK wallhole);

void checkScore(std::vector<std::vector<int>>& map, PM pacman, int *score, GHOST* ghost, int* phantomTime);

void checkLvlOver(std::vector<std::vector<int>>& map, int *gameOver, PM* pacman, int* nextLevel);

void printLogo();

