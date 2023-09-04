#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

// linux version :
// #include <termios.h>

// windows version :
#include <windows.h> 
#include <conio.h>  

typedef struct
{
  char nickname[20];
  int posx;
  int posy;
  int **terrain;
  int rows;
  int columns;
  float explodedBombs;
  float score;
  bool alive;
} bm; // bomberman

typedef struct
{
  int posx;
  int posy;
} obstacle;

void *read_keyboard(void *arg);
void read_terrain(char *file_name, bm *bm);
void print_terrain(bm bm);
void place_bm(bm *bm);
void place_obstacles(obstacle *obstacle, bm *bm);
void register_score(bm bm);
