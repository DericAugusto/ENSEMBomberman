#include "definitions.h"
static pthread_mutex_t dmutex = PTHREAD_MUTEX_INITIALIZER;

void *read_keyboard(void *arg)
{
  bm *pl = (bm *)arg;
  char c;
  boolean bomb = false;
  while (1)
  {
    if (pl->alive == false)
      break;
    if (_kbhit)
    {
      c = _getch();
      pthread_mutex_lock(&dmutex);

      // going up
      if (c == 'z')
      {
        if (pl->terrain[pl->posx - 1][pl->posy] == 0)
        {
          if (pl->terrain[pl->posx][pl->posy] != 4)
          {
            pl->terrain[pl->posx][pl->posy] = 0;
          }
          pl->terrain[pl->posx - 1][pl->posy] = 2;
          pl->posx = pl->posx - 1;
        }
      }

      // going down
      else if (c == 's')
      {
        if (pl->terrain[pl->posx + 1][pl->posy] == 0)
        {
          if (pl->terrain[pl->posx][pl->posy] != 4)
          {
            pl->terrain[pl->posx][pl->posy] = 0;
          }
          pl->terrain[pl->posx + 1][pl->posy] = 2;
          pl->posx = pl->posx + 1;
        }
      }

      // going right
      else if (c == 'd')
      {
        if (pl->posx == 5 && pl->posy == 63)
        {
          pl->terrain[pl->posx][pl->posy] = 0;
          pl->posx = 5;
          pl->posy = -1;
          pl->terrain[pl->posx][pl->posy] = 2;
        }

        if (pl->terrain[pl->posx][pl->posy + 1] == 0)
        {
          if (pl->terrain[pl->posx][pl->posy] != 4)
          {
            pl->terrain[pl->posx][pl->posy] = 0;
          }
          pl->terrain[pl->posx][pl->posy + 1] = 2;
          pl->posy = pl->posy + 1;
        }
      }

      // going left
      else if (c == 'q')
      {
        if (pl->posx == 5 && pl->posy == 0)
        {
          pl->terrain[pl->posx][pl->posy] = 0;
          pl->posx = 5;
          pl->posy = 64;
          pl->terrain[pl->posx][pl->posy] = 2;
        }

        if (pl->terrain[pl->posx][pl->posy - 1] == 0)
        {
          if (pl->terrain[pl->posx][pl->posy] != 4)
          {
            pl->terrain[pl->posx][pl->posy] = 0;
          }

          pl->terrain[pl->posx][pl->posy - 1] = 2;
          pl->posy = pl->posy - 1;
        }
      }

      // dropping bomb
      else if (c == ' ')
      {
        pl->terrain[pl->posx][pl->posy] = 4;
        pl->explodedBombs++;
      }

      pthread_mutex_unlock(&dmutex);
    }
  }
}

void *read_keyboard2(void *arg)
{
  bm *pl = (bm *)arg;
  char c;
  boolean bomb = false;
  while (1)
  {
    if (pl->alive == false)
      break;
    if (_kbhit)
    {
      c = _getch();
      pthread_mutex_lock(&dmutex);

      // going up
      if (c == 'i')
      {
        if (pl->terrain[pl->posx - 1][pl->posy] == 0)
        {
          if (pl->terrain[pl->posx][pl->posy] != 4)
          {
            pl->terrain[pl->posx][pl->posy] = 0;
          }
          pl->terrain[pl->posx - 1][pl->posy] = 2;
          pl->posx = pl->posx - 1;
        }
      }

      // going down
      else if (c == 'k')
      {
        if (pl->terrain[pl->posx + 1][pl->posy] == 0)
        {
          if (pl->terrain[pl->posx][pl->posy] != 4)
          {
            pl->terrain[pl->posx][pl->posy] = 0;
          }
          pl->terrain[pl->posx + 1][pl->posy] = 2;
          pl->posx = pl->posx + 1;
        }
      }

      // going left
      else if (c == 'l')
      {
        if (pl->terrain[pl->posx][pl->posy + 1] == 0)
        {
          if (pl->terrain[pl->posx][pl->posy] != 4)
          {
            pl->terrain[pl->posx][pl->posy] = 0;
          }
          pl->terrain[pl->posx][pl->posy + 1] = 2;
          pl->posy = pl->posy + 1;
        }
      }

      // going right
      else if (c == 'j')
      {
        if (pl->terrain[pl->posx][pl->posy - 1] == 0)
        {
          if (pl->terrain[pl->posx][pl->posy] != 4)
          {
            pl->terrain[pl->posx][pl->posy] = 0;
          }

          pl->terrain[pl->posx][pl->posy - 1] = 2;
          pl->posy = pl->posy - 1;
        }
      }

      // dropping bomb
      else if (c == ' ')
      {
        pl->terrain[pl->posx][pl->posy] = 4;
        pl->explodedBombs++;
      }

      pthread_mutex_unlock(&dmutex);
    }
  }
}

void *winning_condition(void *arg)
{
  bm *bomberman = (bm *)arg;

  while (1)
  {
    pthread_mutex_lock(&dmutex);
    if (bomberman->alive == false)
      break;

    print_terrain(*bomberman);
    if (bomberman->explodedBombs != 0.0000000)
    {
      printf("\n                    ");
      printf("Score %f", ((bomberman->score) / ((bomberman->explodedBombs) * 4)));
      printf("\n                    ");
      printf("%d exploded bombs", (int)bomberman->explodedBombs);
    }
    else
    {
      printf("\n                    ");
      printf("Score %f", 0.00000000);
      printf("\n                    ");
      printf("%d exploded bombs", (int)bomberman->explodedBombs);
    } 
    pthread_mutex_unlock(&dmutex);
    Sleep(300);
  }
}

void *bombs_engine(void *arg)
{
  bm *bomberman = (bm *)arg;

  while (1)
  {

    pthread_mutex_lock(&dmutex);
    for (int i = 0; i < bomberman->rows; i++)
    {
      for (int j = 0; j < bomberman->columns; j++)
      {
        if (bomberman->terrain[i][j] == 4)
        {
          pthread_mutex_unlock(&dmutex);
          Sleep(4000);
          pthread_mutex_lock(&dmutex);
          if (bomberman->terrain[i + 1][j] == 3)
          {
            bomberman->terrain[i + 1][j] = 0;
            bomberman->score++;
          }

          if (bomberman->terrain[i - 1][j] == 3)
          {
            bomberman->terrain[i - 1][j] = 0;
            bomberman->score++;
          }

          if (bomberman->terrain[i][j + 1] == 3)
          {

            bomberman->terrain[i][j + 1] = 0;
            bomberman->score++;
          }
          if (bomberman->terrain[i][j - 1] == 3)
          {
            bomberman->terrain[i][j - 1] = 0;
            bomberman->score++;
          }

          if (bomberman->terrain[i + 1][j] == 2)
          {
            bomberman->terrain[i + 1][j] = 0;
            bomberman->alive = false;
          }

          if (bomberman->terrain[i - 1][j] == 2)
          {
            bomberman->terrain[i - 1][j] = 0;
            bomberman->alive = false;
          }

          if (bomberman->terrain[i][j + 1] == 2)
          {

            bomberman->terrain[i][j + 1] = 0;
            bomberman->alive = false;
          }
          if (bomberman->terrain[i][j - 1] == 2)
          {
            bomberman->terrain[i][j - 1] = 0;
            bomberman->alive = false;
          }

          if ((i == bomberman->posx) && (j == bomberman->posy))
          {
            bomberman->alive = false;
          }
          bomberman->terrain[i][j] = 0;
        }
      }
    }
    pthread_mutex_unlock(&dmutex);
  }
}


int main()
{
  system("cls");

  bm bm1;

  printf("\n\nName of the player: ");
  scanf("%s", &bm1.nickname);

  bm1.alive = true;
  bm1.score = 0.00000000;
  bm1.explodedBombs = 0.00000000;

  obstacle obstacle;
  pthread_t th_keyboard, th_winning_engine, th_bombs_engine; 

  srand(time(0));
  read_terrain("map.txt", &bm1);
  place_bm(&bm1);
  for (int i = 0; i < 50; i++)
    place_obstacles(&obstacle, &bm1);
  print_terrain(bm1);

  pthread_create(&th_bombs_engine, NULL, bombs_engine, &bm1);
  pthread_create(&th_winning_engine, NULL, winning_condition, &bm1);
  pthread_create(&th_keyboard, NULL, read_keyboard, &bm1);

  pthread_join(th_winning_engine, NULL);

  // aqui
  
  register_score(bm1);

  return 0;
}
