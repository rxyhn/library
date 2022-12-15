#include "header.h"
#ifdef _WIN32
#include <Windows.h>
#define clear "cls"
#else
#include <unistd.h>
#define clear "clear"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 65536

void gotoxy(int x, int y) { printf("\033[%d;%dH", y, x); }

int countLines(FILE *file) {
  char buf[BUF_SIZE];
  int counter = 0;
  for (;;) {
    size_t res = fread(buf, 1, BUF_SIZE, file);
    if (ferror(file))
      return -1;

    int i;
    for (i = 0; i < res; i++)
      if (buf[i] == '\n')
        counter++;

    if (feof(file))
      break;
  }

  return counter;
}

int isUsernameExists(FILE *file, char username[]) {
  struct users temp;

  while (fscanf(file, "%d %s %s %d", &temp.ID, temp.username, temp.password,
                &temp.role) != EOF) {
    printf("%s %s\n", temp.username, username);
    if (!strcmp(temp.username, username)) {
      system(clear);
      gotoxy(20, 12);
      printf("Username already exists. Please try again.\n");
      sleep(1);
      return 1;
    }
  }
  fclose(file);
  return 0;
}

int isIDExists(FILE *file, int ID) {
  struct users temp;

  while (fscanf(file, "%d %s %s %d", &temp.ID, temp.username, temp.password,
                &temp.role) != EOF) {
    if (temp.ID == ID) {
      system(clear);
      gotoxy(20, 12);
      printf("ID already exists. Please try again.\n");
      sleep(1);
      return 1;
    }
  }
  fclose(file);
  return 0;
}

void headerLMS(char str[]) {
  system(clear);
  gotoxy(20, 2);
  printf("============================================");
  gotoxy(29, 4);
  printf("Library Management System ");
  gotoxy(34, 5);
  printf("Binus University ");
  gotoxy(20, 7);
  printf("============================================");
  gotoxy(37, 9);
  printf("%s", str);
}