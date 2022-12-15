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

void addUser() {

  int rep = listUsers();

  struct users user;
  memset(&user, 0, sizeof user);

  FILE *fp;
  fp = fopen("docs/users.txt", "a");
  if (fp == NULL) {
    system(clear);
    printf("File doesn't exists.");
    sleep(1);
    userManagement();
  }
  // printf("%d %s %s %d\n", user.ID, user.username, user.password, user.role);

  // increment ID
  struct users temp;
  FILE *fp2;
  fp2 = fopen("docs/users.txt", "r");
  int maxID = 0;
  while (fscanf(fp2, "%d %s %s %d", &temp.ID, temp.username, temp.password,
                &temp.role) != EOF) {
    if (temp.ID > maxID) {
      maxID = temp.ID;
    }
  }
  fclose(fp2);
  user.ID = maxID + 1;

  gotoxy(22, rep);
  printf("Enter username: ");
  scanf("%s", user.username);
  gotoxy(22, rep += 2);
  printf("Enter password: ");
  scanf("%s", user.password);

  gotoxy(22, rep += 2);
  printf("1. Admin\n");
  gotoxy(22, rep += 1);
  printf("2. User\n");
  gotoxy(22, rep += 2);
  printf("Enter role: ");
  scanf("%d", &user.role);

  if (isUsernameExists(fopen("docs/users.txt", "r"), user.username)) {
    fclose(fp);
    headerLMS("Add User");
    addUser();
  }
  // check if role is valid
  if (user.role != 1 && user.role != 2) {
    fclose(fp);
    gotoxy(22, rep += 2);
    printf("Invalid role. Please try again.\n");
    sleep(1);
    headerLMS("Add User");
    addUser();
  }

  fprintf(fp, "%d %s %s %d\n", user.ID, user.username, user.password,
          user.role);
  fclose(fp);

  system(clear);
  gotoxy(35, 11);
  printf("User added.\n");
  sleep(1);
}

void deleteUser() {
  int rep = listUsers();

  struct users user;
  FILE *fp;
  fp = fopen("docs/users.txt", "r");
  if (fp == NULL) {
    system(clear);
    printf("File doesn't exists.");
    sleep(1);
    userManagement();
  }
  gotoxy(22, rep);
  printf("Enter ID: ");
  scanf("%d", &user.ID);

  // Check if ID exists
  struct users temp;
  FILE *fp2;
  fp2 = fopen("docs/users.txt", "r");
  int found = 0;
  while (fscanf(fp2, "%d %s %s %d", &temp.ID, temp.username, temp.password,
                &temp.role) != EOF) {
    if (temp.ID == user.ID) {
      found = 1;
      break;
    }
  }
  fclose(fp2);

  if (found == 0) {
    gotoxy(23, rep += 2);
    printf("ID does not exist. Please try again.\n");
    sleep(1);
    headerLMS("Delete User");
    deleteUser();
  }

  // Delete user
  FILE *fp3;
  fp3 = fopen("temp.txt", "w");
  while (fscanf(fp, "%d %s %s %d", &temp.ID, temp.username, temp.password,
                &temp.role) != EOF) {
    if (temp.ID != user.ID) {
      fprintf(fp3, "%d %s %s %d\n", temp.ID, temp.username, temp.password,
              temp.role);
    }
  }
  fclose(fp);
  fclose(fp3);
  remove("docs/users.txt");
  rename("temp.txt", "docs/users.txt");

  gotoxy(22, rep += 2);
  printf("User deleted.\n");
  sleep(1);
}

int listUsers() {
  struct users user;
  FILE *fp;
  fp = fopen("docs/users.txt", "r");
  if (fp == NULL) {
    printf("File doesn't exists.");
    userManagement();
  }
  gotoxy(28, 11);
  printf("ID  Username   Password  Role\n");
  int rep = 12;
  while (fscanf(fp, "%d %s %s %d", &user.ID, user.username, user.password,
                &user.role) != EOF) {
    gotoxy(28, rep++);
    printf("%2d  %-8s   %-8s  %-2d\n", user.ID, user.username, user.password,
           user.role);
  }
  fclose(fp);
  gotoxy(28, ++rep);

  return rep;
}
