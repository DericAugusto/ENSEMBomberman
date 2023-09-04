#include "definitions.h"
pthread_mutex_t dmutex = PTHREAD_MUTEX_INITIALIZER;

void read_terrain(char *fichier, bm *bm)
{
  char ch;
  FILE *f;

  bm->rows = 11;
  bm->columns = 65;

  // setting terrain matrix size
  bm->terrain = (int **)malloc(bm->rows * sizeof(int *));
  for (int i = 0; i < bm->rows; i++)
  {
    bm->terrain[i] = (int *)malloc(bm->columns * sizeof(int));
  }
  
  // setting bombs matrix size
  bm->bombs = (int **)malloc(bm->rows * sizeof(int *));
  for (int i = 0; i < bm->rows; i++)
  {
    bm->bombs[i] = (int *)malloc(bm->columns * sizeof(int));
  }

  // registering read map to the terrain matrix
  int i = 0;
  int j = 0;
  f = fopen(fichier, "r");
  while ((ch = fgetc(f)) != EOF)
  {

    if (ch == '#')
    {
      bm->terrain[i][j] = 1;
    }
    else if (ch == ' ')
    {
      bm->terrain[i][j] = 0;
    }
    else if (ch == 'o')
    {
      bm->terrain[i][j] = 0;
    }

    j++;

    if (j == bm->columns)
    {
      j = 0;
      i++;
    }
  }

  fclose(f);
}

void clearScreen()
{
  HANDLE hOut;
  COORD Position;

  hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  Position.X = 0;
  Position.Y = 0;
  SetConsoleCursorPosition(hOut, Position);
}

void place_bm(bm *bm)
{
  int x, y;
  do
  {
    x = (int)(rand() % (bm->rows));
    y = (int)(rand() % (bm->columns));
  } while (bm->terrain[x][y] == 1);
  bm->posx = x;
  bm->posy = y;
  bm->terrain[x][y] = 2;
}

void place_obstacles(obstacle *obstacle, bm *bm)
{
  int x, y;
  do
  {
    x = (int)(rand() % (bm->rows));
    y = (int)(rand() % (bm->columns) - 1);
  } while (bm->terrain[x][y] == 1);
  obstacle->posx = x;
  obstacle->posy = y;
  bm->terrain[x][y] = 3;
}
