#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <winsock2.h>
#include <windows.h>
#include <conio.h>

typedef struct
{
	char nickname[20];
	int posx;
	int posy;
	int terrain[11][65];
	int bombs[11][65];
	int rows;
	int columns;
	float explodedBombs;
	float score;
	bool alive;
} bm; // bomberman

typedef struct
{
	bm *bm1;
	bm *bm2;
} bms; // bombermans

typedef struct
{
	int posx;
	int posy;
} obstacle;

void *read_keyboard(void *arg);
void read_terrain(char *fichier, bm *bm);
void place_bm(bm *bm);
