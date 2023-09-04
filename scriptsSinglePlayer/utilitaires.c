#include "definitions.h"
pthread_mutex_t dmutex = PTHREAD_MUTEX_INITIALIZER;

void read_terrain(char *file_name, bm *bm)
{

  char ch;
  FILE *f;

  bm->rows = 11;
  bm->columns = 65;

  bm->terrain = (int **)malloc(bm->rows * sizeof(int *));
  for (int i = 0; i < bm->rows; i++)
  {
    bm->terrain[i] = (int *)malloc(bm->columns * sizeof(int));
  }
  int i = 0;
  int j = 0;

  f = fopen(file_name, "r");

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

void print_terrain(bm bm)
{
  int i, j;
  clearScreen();

  printf("                    ");
  for (i = 0; i < bm.rows; i++)
  {
    for (j = 0; j < bm.columns; j++)
    {
      if (bm.terrain[i][j] == 0)
        printf("%c", ' ');
      else if (bm.terrain[i][j] == 1)
        printf("%c", '#');
      else if (bm.terrain[i][j] == 2)
        printf("%c", 'B');
      else if (bm.terrain[i][j] == 3)
        printf("%c", 'x');
      else if (bm.terrain[i][j] == 4)
      {
        if ((i != bm.posx) || (j != bm.posy))
          printf("%c", 'o');
        else
          printf("%c", 'B');
      }
    }
    printf("\n                    ");
  }
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

void register_score(bm bm)
{
  FILE *score_file = NULL;
  score_file = fopen("scores.txt", "a");
  char *buffer[256];
  time_t timestamp = time(NULL);
  strftime(buffer, sizeof(buffer), "%x. %X.", localtime(&timestamp));
  if (score_file != NULL)
  {

    fprintf(score_file, "%f", ((bm.score) / ((bm.explodedBombs) * 4)));
    fputs(" ", score_file);

    fputs(bm.nickname, score_file);
    fputs(" ", score_file);

    fputs(buffer, score_file);
    fputs("\n", score_file);
    fclose(score_file); 
  }
}

