#include "definitions.h"
static pthread_mutex_t dmutex = PTHREAD_MUTEX_INITIALIZER;

void *read_keyboard(void *arg)
{
  bms *pl = (bms *)arg; // player
  char c;

  while (1)
  {

    if (_kbhit)
    {
      c = _getch();
      pthread_mutex_lock(&dmutex);

      // player 1 ----------------------------
      // player 1 going up
      if (c == 'w')
      {
        // if the way its empty
        if (pl->bm1->terrain[pl->bm1->posx - 1][pl->bm1->posy] == 0)
        {
          // if there's no bomb, the place left behind will be empty
          if (pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy] != 4)
          {
            pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy] = 0;
          }
          pl->bm1->terrain[pl->bm1->posx - 1][pl->bm1->posy] = 2;
          pl->bm1->posx = pl->bm1->posx - 1;
        }
      }

      // player 1 going down
      else if (c == 's')
      {
        if (pl->bm1->terrain[pl->bm1->posx + 1][pl->bm1->posy] == 0)
        {
          if (pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy] != 4)
          {
            pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy] = 0;
          }
          pl->bm1->terrain[pl->bm1->posx + 1][pl->bm1->posy] = 2;
          pl->bm1->posx = pl->bm1->posx + 1;
        }
      }

      // player 1 going right
      else if (c == 'd')
      {
        // to pass lateral tunel
        if (pl->bm1->posx == 5 && pl->bm1->posy == 63)
        {
          pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy] = 0;
          pl->bm1->posx = 5;
          pl->bm1->posy = -1;
          pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy] = 2;
        }

        if (pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy + 1] == 0)
        {
          if (pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy] != 4)
          {
            pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy] = 0;
          }
          pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy + 1] = 2;
          pl->bm1->posy = pl->bm1->posy + 1;
        }
      }

      // player 1 going left 
      else if (c == 'a')
      {
        if (pl->bm1->posx == 5 && pl->bm1->posy == 0)
        {
          pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy] = 0;
          pl->bm1->posx = 5;
          pl->bm1->posy = 64;
          pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy] = 2;
        }

        if (pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy - 1] == 0)
        {
          if (pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy] != 4)
          {
            pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy] = 0;
          }

          pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy - 1] = 2;
          pl->bm1->posy = pl->bm1->posy - 1;
        }
      }

      // player 1 dropping bomb
      else if (c == ' ')
      {
        pl->bm1->terrain[pl->bm1->posx][pl->bm1->posy] = 4;
        pl->bm1->explodedBombs++;
        pl->bm1->bombs[pl->bm1->posx][pl->bm1->posy] = 1;
      }

      // player 2 ----------------------------
      // player 2 going up
      if (c == 'i')
      {
        if (pl->bm2->terrain[pl->bm2->posx - 1][pl->bm2->posy] == 0)
        {
          if (pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy] != 4)
          {
            pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy] = 0;
          }
          pl->bm2->terrain[pl->bm2->posx - 1][pl->bm2->posy] = 2;
          pl->bm2->posx = pl->bm2->posx - 1;
        }
      }

      // player 2 going down
      else if (c == 'k')
      {
        if (pl->bm2->terrain[pl->bm2->posx + 1][pl->bm2->posy] == 0)
        {
          if (pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy] != 4)
          {
            pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy] = 0;
          }
          pl->bm2->terrain[pl->bm2->posx + 1][pl->bm2->posy] = 2;
          pl->bm2->posx = (pl->bm2->posx) + 1;
        }
      }

      // player 2 going left
      else if (c == 'l')
      {
        if (pl->bm2->posx == 5 && pl->bm2->posy == 63)
        {
          pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy] = 0;
          pl->bm2->posx = 5;
          pl->bm2->posy = -1;
          pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy] = 2;
        }

        if (pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy + 1] == 0)
        {
          if (pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy] != 4)
          {
            pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy] = 0;
          }
          pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy + 1] = 2;
          pl->bm2->posy = pl->bm2->posy + 1;
        }
      }

      // player 2 going right
      else if (c == 'j')
      {
        if (pl->bm2->posx == 5 && pl->bm2->posy == 0)
        {
          pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy] = 0;
          pl->bm2->posx = 5;
          pl->bm2->posy = 64;
          pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy] = 2;
        }

        if (pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy - 1] == 0)
        {
          if (pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy] != 4)
          {
            pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy] = 0;
          }

          pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy - 1] = 2;
          pl->bm2->posy = pl->bm2->posy - 1;
        }
      }

      // player 2 dropping bomb
      else if (c == 'o')
      {
        pl->bm2->terrain[pl->bm2->posx][pl->bm2->posy] = 4;
        pl->bm2->explodedBombs++;
        pl->bm2->bombs[pl->bm2->posx][pl->bm2->posy] = 1;
      }

      pthread_mutex_unlock(&dmutex);
    }
  }
}

void print_terrain(bms *pl)
{
  int i, j;
  clearScreen();

  printf("                    ");
  for (i = 0; i < pl->bm1->rows; i++)
  {
    for (j = 0; j < pl->bm1->columns; j++)
    {
      if (pl->bm1->terrain[i][j] == 0)
        printf("%c", ' ');
      else if (pl->bm1->terrain[i][j] == 1)
        printf("%c", '#');
      else if (pl->bm1->terrain[i][j] == 2)
        printf("%c", 'B');
      else if (pl->bm1->terrain[i][j] == 3)
        printf("%c", 'x');
      else if (pl->bm1->terrain[i][j] == 4)
      {
        if (((i == (pl->bm1->posx)) && (j == (pl->bm1->posy))) || ((i == (pl->bm2->posx)) && (j == (pl->bm2->posy))))
          printf("%c", 'B');
        else
          printf("%c", 'o');
      }
    }
    printf("\n                    ");
  }
  printf("\n\n\n");

  printf("                    Player 1: %s\n", &pl->bm1->nickname);
  printf("                    %d exploded bombs\n", (int)pl->bm1->explodedBombs);
  printf("                    Score: %f\n\n", pl->bm1->score);

  printf("                    Player 2: %s\n", &pl->bm2->nickname);
  printf("                    %d exploded bombs\n", (int)pl->bm2->explodedBombs);
  printf("                    Score: %f\n", pl->bm2->score);
}

void *winning_condition(void *arg)
{
  bms *pl = (bms *)arg;

  while (1)
  {
    if (pl->bm1->alive == false)
    {
      system("cls");
      printf("\n\n                    The game is over.\n\n");
      printf("                    ");
      printf("%s won the match!\n\n\n\n", pl->bm2->nickname);
      break;
    }
    if (pl->bm2->alive == false)
    {
      system("cls");
      printf("\n\n                    The game is over.\n\n");
      printf("                    ");
      printf("%s won the match!\n\n\n\n", pl->bm1->nickname);
      break;
    }

    print_terrain(pl);

    Sleep(300);
  }
}

void *exchange_info_terrain(void *arg)
{

  while (1)
  {

    pthread_mutex_unlock(&dmutex);
    bms *pl = (bms *)arg;
    for (int i = 0; i < pl->bm1->rows; i++)
    {
      for (int j = 0; j < pl->bm1->columns; j++)
      {

        if ((pl->bm1->terrain[i][j] == 2) && (pl->bm2->terrain[i][j] == 0) && (i == pl->bm1->posx) && (j == pl->bm1->posy))
        {
          pl->bm2->terrain[i][j] = 2;
        }
        if ((pl->bm1->terrain[i][j] == 2) && (pl->bm2->terrain[i][j] == 0))
        {
          pl->bm1->terrain[i][j] = 0;
        }
        if ((pl->bm1->terrain[i][j] == 0) && (pl->bm2->terrain[i][j] == 2) && (i == pl->bm2->posx) && (j == pl->bm2->posy))
        {
          pl->bm1->terrain[i][j] = 2;
        }
        if ((pl->bm1->terrain[i][j] == 0) && (pl->bm2->terrain[i][j] == 2))
        {
          pl->bm1->terrain[i][j] = 0;
        }
        if ((pl->bm1->terrain[i][j] == 4) || (pl->bm2->terrain[i][j] == 4))
        {
          pl->bm1->terrain[i][j] = 4;
          pl->bm2->terrain[i][j] = 4;
        }

        if ((pl->bm1->terrain[i][j] == 0) || (pl->bm2->terrain[i][j] == 0))
        {
          pl->bm1->terrain[i][j] = 0;
          pl->bm2->terrain[i][j] = 0;
        }

        pthread_mutex_unlock(&dmutex);
      }
    }
  }
}

void *bombs_engine(void *arg)
{
  bms *pl = (bms *)arg;

  while (1)
  {

    pthread_mutex_lock(&dmutex);
    for (int i = 0; i < pl->bm1->rows; i++)
    {
      for (int j = 0; j < pl->bm1->columns; j++)
      {
        // if there's a bomb in that spot
        if (pl->bm1->terrain[i][j] == 4)
        {
          // if the bomb was placed by the player 1
          if (pl->bm1->bombs[i][j] == 1){

            pthread_mutex_unlock(&dmutex);
            Sleep(4000);
            pthread_mutex_lock(&dmutex);

            // checking terrain
            if (pl->bm1->terrain[i + 1][j] == 3)
            {
              pl->bm1->terrain[i + 1][j] = 0;
              pl->bm1->score++;
            }
            if (pl->bm1->terrain[i - 1][j] == 3)
            {
              pl->bm1->terrain[i - 1][j] = 0;
              pl->bm1->score++;
            }
            if (pl->bm1->terrain[i][j + 1] == 3)
            {
              pl->bm1->terrain[i][j + 1] = 0;
              pl->bm1->score++;
            }
            if (pl->bm1->terrain[i][j - 1] == 3)
            {
              pl->bm1->terrain[i][j - 1] = 0;
              pl->bm1->score++;
            }

            // player 1 killed by bomb
            if ((pl->bm1->posx == i + 1) && (pl->bm1->posy == j))
            {
              pl->bm1->terrain[i + 1][j] = 0;
              pl->bm1->alive = false;
            }
            if ((pl->bm1->posx == i - 1) && (pl->bm1->posy == j))
            {
              pl->bm1->terrain[i - 1][j] = 0;
              pl->bm1->alive = false;
            }
            if ((pl->bm1->posx == i) && (pl->bm1->posy == j + 1))
            {
              pl->bm1->terrain[i][j + 1] = 0;
              pl->bm1->alive = false;
            }
            if ((pl->bm1->posx == i) && (pl->bm1->posy == j - 1))
            {
              pl->bm1->terrain[i][j - 1] = 0;
              pl->bm1->alive = false;
            }

            // player 2 killed by bomb
            if ((pl->bm2->posx == i + 1) && (pl->bm2->posy == j))
            {
              pl->bm2->terrain[i + 1][j] = 0;
              pl->bm2->alive = false;
            }
            if ((pl->bm2->posx == i - 1) && (pl->bm2->posy == j))
            {
              pl->bm2->terrain[i - 1][j] = 0;
              pl->bm2->alive = false;
            }
            if ((pl->bm2->posx == i) && (pl->bm2->posy == j + 1))
            {
              pl->bm2->terrain[i][j + 1] = 0;
              pl->bm2->alive = false;
            }
            if ((pl->bm2->posx == i) && (pl->bm2->posy == j - 1))
            {
              pl->bm2->terrain[i][j - 1] = 0;
              pl->bm2->alive = false;
            }

            // player 1 and 2 killed on top of the bomb
            if ((i == pl->bm1->posx) && (j == pl->bm1->posy))
            {
              pl->bm1->alive = false;
            }
            pl->bm1->terrain[i][j] = 0;
            if ((i == pl->bm2->posx) && (j == pl->bm2->posy))
            {
              pl->bm2->alive = false;
            }
            pl->bm2->terrain[i][j] = 0;

          // the bomb was placed by the player 2
          } else {

            pthread_mutex_unlock(&dmutex);
            Sleep(4000);
            pthread_mutex_lock(&dmutex);

            // checking terrain
            if (pl->bm2->terrain[i + 1][j] == 3)
            {
              pl->bm2->terrain[i + 1][j] = 0;
              pl->bm2->score++;
            }
            if (pl->bm2->terrain[i - 1][j] == 3)
            {
              pl->bm2->terrain[i - 1][j] = 0;
              pl->bm2->score++;
            }
            if (pl->bm2->terrain[i][j + 1] == 3)
            {
              pl->bm2->terrain[i][j + 1] = 0;
              pl->bm2->score++;
            }
            if (pl->bm2->terrain[i][j - 1] == 3)
            {
              pl->bm2->terrain[i][j - 1] = 0;
              pl->bm2->score++;
            }

            // player 1 killed by bomb
            if ((pl->bm1->posx == i + 1) && (pl->bm1->posy == j))
            {
              pl->bm1->terrain[i + 1][j] = 0;
              pl->bm1->alive = false;
            }
            if ((pl->bm1->posx == i - 1) && (pl->bm1->posy == j))
            {
              pl->bm1->terrain[i - 1][j] = 0;
              pl->bm1->alive = false;
            }
            if ((pl->bm1->posx == i) && (pl->bm1->posy == j + 1))
            {
              pl->bm1->terrain[i][j + 1] = 0;
              pl->bm1->alive = false;
            }
            if ((pl->bm1->posx == i) && (pl->bm1->posy == j - 1))
            {
              pl->bm1->terrain[i][j - 1] = 0;
              pl->bm1->alive = false;
            }

            // player 2 killed by bomb
            if ((pl->bm2->posx == i + 1) && (pl->bm2->posy == j))
            {
              pl->bm2->terrain[i + 1][j] = 0;
              pl->bm2->alive = false;
            }
            if ((pl->bm2->posx == i - 1) && (pl->bm2->posy == j))
            {
              pl->bm2->terrain[i - 1][j] = 0;
              pl->bm2->alive = false;
            }
            if ((pl->bm2->posx == i) && (pl->bm2->posy == j + 1))
            {
              pl->bm2->terrain[i][j + 1] = 0;
              pl->bm2->alive = false;
            }
            if ((pl->bm2->posx == i) && (pl->bm2->posy == j - 1))
            {
              pl->bm2->terrain[i][j - 1] = 0;
              pl->bm2->alive = false;
            }

            // player 1 and 2 killed on top of the bomb
            if ((i == pl->bm1->posx) && (j == pl->bm1->posy))
            {
              pl->bm1->alive = false;
            }
            pl->bm1->terrain[i][j] = 0;
            if ((i == pl->bm2->posx) && (j == pl->bm2->posy))
            {
              pl->bm2->alive = false;
            }
            pl->bm2->terrain[i][j] = 0;

          }
        }
      }
    }
    pthread_mutex_unlock(&dmutex);
  }
}

void exchange_info_obstacles(bms *bms)
{

  for (int i = 0; i < (bms->bm1->rows); i++)
  {
    for (int j = 0; j < (bms->bm1->columns); j++)
    {
      if (bms->bm1->terrain[i][j] == 3)
        bms->bm2->terrain[i][j] = 3;
    }
  }
}

int main()
{
  system("cls");

  // starting game
  bm bm1;
  bm bm2;
  bms bms;
  bms.bm1 = &bm1;
  bms.bm2 = &bm2;
  bm1.alive = true;
  bm2.alive = true;
  bm1.score = 0.000000000;
  bm1.explodedBombs = 0.00000000;
  bm2.score = 0.000000000;
  bm2.explodedBombs = 0.00000000;
  
  printf("\n\nEnter the name of the first player: ");
  scanf("%s", &bm1.nickname);
  printf("\nEnter the name of the second player: ");
  scanf("%s", &bm2.nickname);
  system("cls");

  obstacle obstacle;
  pthread_t th_keyboard, th_winning_engine, th_bombs_engine, th_ex_info;

  srand(time(0));

  read_terrain("map.txt", &bm1);
  read_terrain("map.txt", &bm2);

  place_bm(&bm1);
  place_bm(&bm2);

  for (int i = 0; i < 50; i++) place_obstacles(&obstacle, &bm1);
  
  exchange_info_obstacles(&bms);

  pthread_create(&th_winning_engine, NULL, winning_condition, &bms);
  pthread_create(&th_keyboard, NULL, read_keyboard, &bms);
  pthread_create(&th_bombs_engine, NULL, bombs_engine, &bms);
  pthread_create(&th_ex_info, NULL, exchange_info_terrain, &bms);
  pthread_join(th_winning_engine, NULL);

  system('PAUSE');

  return 0;
}
