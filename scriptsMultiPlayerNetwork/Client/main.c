#include "definitions.h"

#pragma comment(lib, "ws2_32.lib") // Winsock Library

#define SERVER "127.0.0.1" // ip address of udp server
#define BUFLEN 512         // Max length of buffer
#define PORT 8888
#define PORT1 8889 // port on which incoming data is listened to

static pthread_mutex_t dmutex = PTHREAD_MUTEX_INITIALIZER;

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

  printf("                    Player 1: %s\n", &pl->bm2->nickname);
  printf("                    %d exploded bombs\n", (int)pl->bm2->explodedBombs);
  printf("                    Score: %f\n\n", pl->bm2->score);

  printf("                    Player 2: %s\n", &pl->bm1->nickname);
  printf("                    %d exploded bombs\n", (int)pl->bm1->explodedBombs);
  printf("                    Score: %f\n", pl->bm1->score);
}

void *read_keyboard(void *arg)
{
  bm *bm2 = (bm *)arg;
  char c;
  boolean bomb = false;

  while (1)
  {
    if (bm2->alive == false)
      break;
    if (_kbhit)
    {
      c = _getch();
      pthread_mutex_lock(&dmutex);

      // player 2 ----------------------------
      // player 2 going up
      if (c == 'w')
      {
        // if the way its empty
        if (bm2->terrain[bm2->posx - 1][bm2->posy] == 0)
        {
          // if there's no bomb, the place left behind will be empty
          if (bm2->terrain[bm2->posx][bm2->posy] != 4)
          {
            bm2->terrain[bm2->posx][bm2->posy] = 0;
          }
          bm2->terrain[bm2->posx - 1][bm2->posy] = 2;
          bm2->posx = bm2->posx - 1;
        }
      }

      // player 2 going down
      else if (c == 's')
      {

        if (bm2->terrain[bm2->posx + 1][bm2->posy] == 0)
        {
          if (bm2->terrain[bm2->posx][bm2->posy] != 4)
          {
            bm2->terrain[bm2->posx][bm2->posy] = 0;
          }
          bm2->terrain[bm2->posx + 1][bm2->posy] = 2;
          bm2->posx = bm2->posx + 1;
        }
      }

      // player 2 going right
      else if (c == 'd')
      {
        // to pass lateral tunel
        if (bm2->posx == 5 && bm2->posy == 63)
        {
          bm2->terrain[bm2->posx][bm2->posy] = 0;
          bm2->posx = 5;
          bm2->posy = -1;
          bm2->terrain[bm2->posx][bm2->posy] = 2;
        }

        if (bm2->terrain[bm2->posx][bm2->posy + 1] == 0)
        {
          if (bm2->terrain[bm2->posx][bm2->posy] != 4)
          {
            bm2->terrain[bm2->posx][bm2->posy] = 0;
          }
          bm2->terrain[bm2->posx][bm2->posy + 1] = 2;
          bm2->posy = bm2->posy + 1;
        }
      }

      // player 2 going left
      else if (c == 'a')
      {
        if (bm2->posx == 5 && bm2->posy == 0)
        {
          bm2->terrain[bm2->posx][bm2->posy] = 0;
          bm2->posx = 5;
          bm2->posy = 64;
          bm2->terrain[bm2->posx][bm2->posy] = 2;
        }

        if (bm2->terrain[bm2->posx][bm2->posy - 1] == 0)
        {
          if (bm2->terrain[bm2->posx][bm2->posy] != 4)
          {
            bm2->terrain[bm2->posx][bm2->posy] = 0;
          }

          bm2->terrain[bm2->posx][bm2->posy - 1] = 2;
          bm2->posy = bm2->posy - 1;
        }
      }

      // player 2 dropping bomb
      else if (c == ' ')
      {
        bm2->terrain[bm2->posx][bm2->posy] = 4;
        bm2->explodedBombs++;
        bm2->bombs[bm2->posx][bm2->posy] = 1;
      }

      pthread_mutex_unlock(&dmutex);
    }
  }
}

void *winning_condition(void *arg)
{
  bms *pl = (bms *)arg;

  while (1)
  {
    pthread_mutex_lock(&dmutex);
    if (pl->bm1->alive == false)
    {
      system("cls");
      printf("\n\n                    The game is over.\n\n");
      printf("                    ");
      printf("%s won the match!\n\n\n\n", pl->bm1->nickname);
      break;
    }
    if (pl->bm2->alive == false)
    {
      system("cls");
      printf("\n\n                    The game is over.\n\n");
      printf("                    ");
      printf("%s won the match!\n\n\n\n", pl->bm2->nickname);
      break;
    }

    print_terrain(pl);

    pthread_mutex_unlock(&dmutex);

    Sleep(300);
  }
}

void *exchange_info_terrain(void *arg)
{

  int i, j;
  bms *pls = (bms *)arg;

  while (1)
  {

    pthread_mutex_lock(&dmutex);
    for (i = 0; i < pls->bm1->rows; i++)
    {
      for (j = 0; j < pls->bm1->columns; j++)
      {
        if (((pls->bm1->terrain[i][j] == 2) && (pls->bm2->terrain[i][j] == 0)) && ((i == pls->bm2->posx) && (j == pls->bm2->posy)))
        {
          pls->bm1->terrain[i][j] = 2;
        }
        if (((pls->bm1->terrain[i][j] == 0) && (pls->bm2->terrain[i][j] == 2)) && ((i == pls->bm2->posx) && (j == pls->bm2->posy)))
        {
          pls->bm1->terrain[i][j] = 2;
        }
        if (((pls->bm1->terrain[i][j] == 2) && (pls->bm2->terrain[i][j] == 0)) && ((i != pls->bm2->posx) || (j != pls->bm2->posy)) && ((i != pls->bm1->posx) || (j != pls->bm1->posy)))
        {
          pls->bm1->terrain[i][j] = 0;
        }

        if ((pls->bm1->terrain[i][j] == 4) && (pls->bm2->terrain[i][j] == 0))
          pls->bm2->terrain[i][j] = 4;

        if ((pls->bm1->terrain[i][j] == 0) && (pls->bm2->terrain[i][j] == 4))
          pls->bm1->terrain[i][j] = 4;
        if ((pls->bm1->terrain[i][j] == 3) && (pls->bm2->terrain[i][j] == 0))
          pls->bm1->terrain[i][j] = 0;
        if ((pls->bm1->terrain[i][j] == 0) && (pls->bm2->terrain[i][j] == 3))
          pls->bm2->terrain[i][j] = 0;
      }
    }
    pthread_mutex_unlock(&dmutex);
  }
}

void *bombs_engine(void *arg)
{
  bms *pl = (bm *)arg;

  while (1)
  {
    pthread_mutex_lock(&dmutex);
    int i, j;
    for (i = 0; i < pl->bm1->rows; i++)
    {
      for (j = 0; j < pl->bm1->columns; j++)
      {
        // if there's a bomb in the terrain
        if (pl->bm1->terrain[i][j] == 4)
        {
          pthread_mutex_unlock(&dmutex);
          Sleep(4000);
          pthread_mutex_lock(&dmutex);
          // if ther's a barrier 
          //below
          if (pl->bm1->terrain[i + 1][j] == 3)
          {
            pl->bm1->terrain[i + 1][j] = 0;
            pl->bm1->score++;
          }
          // above
          if (pl->bm1->terrain[i - 1][j] == 3)
          {
            pl->bm1->terrain[i - 1][j] = 0;
            pl->bm1->score++;
          }
          // on the left
          if (pl->bm1->terrain[i][j + 1] == 3)
          {
            pl->bm1->terrain[i][j + 1] = 0;
            pl->bm1->score++;
          }
          // on the right
          if (pl->bm1->terrain[i][j - 1] == 3)
          {
            pl->bm1->terrain[i][j - 1] = 0;
            pl->bm1->score++;
          }
          
          // if the's a bomberman
          // below
          if (pl->bm1->terrain[i + 1][j] == 2)
          {
            pl->bm1->terrain[i + 1][j] = 0;
            pl->bm1->alive = false;
          }
          // above
          if (pl->bm1->terrain[i - 1][j] == 2)
          {
            pl->bm1->terrain[i - 1][j] = 0;
            pl->bm1->alive = false;
          }
          // on the right
          if (pl->bm1->terrain[i][j + 1] == 2)
          {
            pl->bm1->terrain[i][j + 1] = 0;
            pl->bm1->alive = false;
          }
          // on the left
          if (pl->bm1->terrain[i][j - 1] == 2)
          {
            pl->bm1->terrain[i][j - 1] = 0;
            pl->bm1->alive = false;
          }
          // on the top of the bomb
          if ((i == pl->bm1->posx) && (j == pl->bm1->posy))
          {
            pl->bm1->alive = false;
          }
          pl->bm1->terrain[i][j] = 0;
        }
      }
    }
    pthread_mutex_unlock(&dmutex);
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

  printf("\nEnter the name of the second player: ");
  scanf("%s", &bm1.nickname);

  bm1.alive = true;
  bm2.alive = true;
  bm1.score = 0.00000000;
  bm1.explodedBombs = 0.00000000;

  obstacle obstacle;
  pthread_t th_keyboard, th_winning_engine, th_bombs_engine, th_exchange_info;

  read_terrain("map.txt", &bm1);
  read_terrain("map.txt", &bm2);

  place_bm(&bm1);

  int i;
  for (i = 0; i < 50; i++) place_obstacle(&obstacle, &bm1);

  bm1.terrain[3][64] = 0;
  bm1.terrain[6][64] = 0;
  bm1.terrain[9][64] = 0;

  pthread_create(&th_bombs_engine, NULL, bombs_engine, &bms);
  pthread_create(&th_winning_engine, NULL, winning_condition, &bms);
  pthread_create(&th_keyboard, NULL, read_keyboard, &bm1);
  pthread_create(&th_exchange_info, NULL, exchange_info_terrain, &bms);

  struct sockaddr_in si_other;
  int s, slen = sizeof(si_other);
  char buf[BUFLEN];
  char message[BUFLEN];
  WSADATA wsa;

  // Initialise winsock
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
  {
    printf("Failed. Error Code : %d", WSAGetLastError());
    exit(EXIT_FAILURE);
  }

  // create socket
  if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
  {
    printf("socket() failed with error code : %d", WSAGetLastError());
    exit(EXIT_FAILURE);
  }

  // setup address structure
  memset((char *)&si_other, 0, sizeof(si_other));
  si_other.sin_family = AF_INET;
  si_other.sin_port = htons(PORT);
  si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
  int x;

  // start communication
  while (1)
  {
    // sending and receiving message
    sendto(s, &bm1, sizeof(bm1), 0, (struct sockaddr *)&si_other, slen);
    Sleep(10);
    recvfrom(s, &bm2, sizeof(bm2), 0, (struct sockaddr *)&si_other, &slen);
    Sleep(10);
  }
  closesocket(s);
  WSACleanup();

  // start communication
  pthread_join(th_winning_engine, NULL);

  return 0;
}
