#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_txt(char *filename, int indentation)
{
  char line[1000];

  FILE *fp = fopen(filename, "r");
  while (fgets(line, sizeof(line), fp)) 
  {
    for (int i = 0; i < indentation; i++) 
    {
      printf(" ");
    }
    printf("%s", line);
  }

  fclose(fp);
}

int main()
{
  system("cls");

  // open screen
  printf("\n\n\n\n");
  print_txt("ensem.txt", 15);
  print_txt("title.txt", 2);
  printf("\n\n\n\n");
  print_txt("bomberman.txt", 10);
  printf("\n\n\n\n          Made by Deric Augusto Franca de Sales.");
  printf("\n\n\n\n");
  char user_input;
  do {
    user_input = getchar();
  } while (user_input != '\n');
  system("cls");

  // second screen
  printf("Do you wanna play as single or multiplayer?\n\n");
  do {
    printf("type 1 for single or 2 for multiplayer : ");
    scanf("%d", &user_input);
    if (user_input != 1 && user_input != 2)
    {
      printf("\nInvalid input!\n\n");
      while (getchar() != '\n');  // clear input buffer
    }
  } while (user_input != 1 && user_input != 2);

  if (user_input == 1)
  {
    system("cls");
    printf("mode single player selected.\n");
    sleep(2);
    system("cd ..\\scriptsSinglePlayer && game.exe");
  } else {
    system("cls");
    printf("mode multiplayer player selected.\n\n");
    printf("do you want to play locally or online?\n\n");
    
    do {
      printf("\n\ntype 1 for locally and 2 for online : ");
      scanf("%d", &user_input);
      if (user_input != 1 && user_input != 2)
      {
        printf("\nInvalid input!\n\n");
        while (getchar() != '\n');  // clear input buffer
      }
    } while (user_input != 1 && user_input != 2);

   if (user_input == 1)
   {
    system("cls");
    printf("mode local multiplayer selected.\n");
    sleep(2);
    system("cd ..\\scriptsMultiPlayer && game.exe");
   } else {
    system("cls");
    printf("mode network multiplayer selected.\n");
    sleep(2);
    system("network_run.bat");
    printf("You are currently playing in the network mode.\n");
    }
  }

  return 0;
}