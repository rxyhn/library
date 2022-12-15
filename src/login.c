#include "../lib/header.h"
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

void welcomePage() {
  system(clear);
  gotoxy(20, 2);
  printf("============================================");
  gotoxy(20, 4);
  printf("---=            Welcome to              =---");
  gotoxy(20, 6);
  printf("---=     Library Management System      =---");
  gotoxy(20, 8);
  printf("---=         Binus Universitry          =---");
  gotoxy(20, 10);
  printf("============================================");
  gotoxy(25, 12);
  printf("press any key to continue...");
  getchar();
}

void adminLogin() {
  system(clear);

  char username[50];
  char password[50];

  FILE *fp;

  struct users user;

  fp = fopen("docs/users.txt", "r");
  if (fp == NULL) {
    printf("ERROR OPENING FILE");
  }

  gotoxy(20, 2);
  printf("============================================");
  gotoxy(36, 4);
  printf("Admin Login ");
  gotoxy(20, 6);
  printf("============================================");

  gotoxy(22, 8);
  printf("---= Username :   ");
  scanf("%s", username);

  gotoxy(22, 10);
  printf("---= Password :   ");
  scanf("%s", password);

  while (fscanf(fp, "%d %s %s %d", &user.ID, user.username, user.password,
                &user.role) != EOF) {
    if (!strcmp(username, user.username) && !strcmp(password, user.password) &&
        user.role == 1) {
      adminPanel();
    }
  }

  gotoxy(22, 12);
  printf("Username or password is wrong. Try again.");
  sleep(1);
  adminLogin();

  fclose(fp);
}

void userOptions() {
  int choice;

  headerLMS("User Menu");

  gotoxy(22, 11);
  printf("----= 1. Login   ");

  gotoxy(22, 13);
  printf("----= 2. Register   ");

  gotoxy(22, 15);
  printf("----= 0. Close Program   ");

  gotoxy(20, 17);
  printf("============================================");

  gotoxy(22, 19);
  printf("----= Console :   ");
  scanf("%d", &choice);

  switch (choice) {

  case 1:
    userLogin();
    break;

  case 2:
    userRegistration();
    break;

  case 0:
    system(clear);
    gotoxy(15, 8);
    printf("---= Thank you for using this app. Have a nice Day :) =---");
    gotoxy(15, 16);
    puts("\n");
    exit(0);
    break;
  }
}

void userLogin() {
  system(clear);

  char username[50];
  char password[50];

  FILE *fp;
  struct users user;

  fp = fopen("docs/users.txt", "r");
  if (fp == NULL) {
    printf("ERROR OPENING FILE");
  }

  gotoxy(20, 2);
  printf("============================================");
  gotoxy(36, 4);
  printf("User Login ");
  gotoxy(20, 6);
  printf("============================================");

  gotoxy(22, 8);
  printf("---= Username :   ");
  scanf("%s", username);

  gotoxy(22, 10);
  printf("---= Password :   ");
  scanf("%s", password);

  while (fscanf(fp, "%d %s %s %d", &user.ID, user.username, user.password,
                &user.role) != EOF) {
    if (!strcmp(username, user.username) && !strcmp(password, user.password)) {
      userPanel();
    }
  }

  gotoxy(22, 12);
  printf("Username or password is wrong. Try again.");
  sleep(1);
  userLogin();

  fclose(fp);
}

void userRegistration() {
  FILE *fp;
  struct users user;

  fp = fopen("docs/users.txt", "a");

  system(clear);

  gotoxy(20, 2);
  printf("============================================");
  gotoxy(32, 4);
  printf("User Register Form ");
  gotoxy(20, 6);
  printf("============================================");

  gotoxy(22, 8);
  printf("---= Username   :   ");
  scanf("%s", user.username);
  getchar();

  gotoxy(22, 10);
  printf("---= Password   :   ");
  scanf("%s", user.password);
  getchar();

  user.ID = countLines(fopen("docs/users.txt", "r"));
  user.role = 2;

  if (isUsernameExists(fopen("docs/users.txt", "r"), user.username)) {
    userRegistration();
  } else {
    system(clear);
    gotoxy(30, 12);
    printf("User registered.\n");
    sleep(1);
  }

  fprintf(fp, "%d %s %s %d\n", user.ID, user.username, user.password,
          user.role);
  fclose(fp);

  userOptions();
}
