#ifdef _WIN32
#include <Windows.h>
#define clear "cls"
#else
#include <unistd.h>
#define clear "clear"
#endif

#include "../lib/header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adminPanel(void) {
  int choice;

  headerLMS("Main Menu");

  gotoxy(22, 11);
  printf("----= 1. Book Management   ");

  gotoxy(22, 13);
  printf("----= 2. User Management   ");

  gotoxy(22, 15);
  printf("----= 0. Log Out ");

  gotoxy(20, 17);
  printf("============================================");

  gotoxy(22, 19);
  printf("----= Console :   ");
  scanf("%d", &choice);

  switch (choice) {
  case 1:
    bookManagement();
    break;

  case 2:
    userManagement();
    break;

  case 0:
    system("clear");
    gotoxy(15, 8);
    printf("---= Thank you for using this app. Have a nice Day :) =---");
    gotoxy(15, 16);
    puts("\n");
    exit(0);
    break;
  }
}

void bookManagement(void) {
  int choice;

  headerLMS("Book Management");

  gotoxy(22, 11);
  printf("----= 1. Add Book   ");

  gotoxy(22, 13);
  printf("----= 2. Delete Book   ");

  gotoxy(22, 15);
  printf("----= 3. List Book ");

  gotoxy(22, 17);
  printf("----= 0. Go back ");

  gotoxy(20, 20);
  printf("============================================");

  gotoxy(22, 22);
  printf("----= Console :   ");
  scanf("%d", &choice);

  getchar();

  switch (choice) {
  case 1:
    system(clear);
    headerLMS("Add Book");
    addBook();
    bookManagement();
    break;

  case 2:
    system(clear);
    headerLMS("Delete Book");
    deleteBook();
    bookManagement();
    break;

  case 3:
    system(clear);
    headerLMS("List Book");
    int rep = listBook("docs/book.csv", 11);
    gotoxy(37, rep += 2);
    printf("Borrowed");
    gotoxy(32, rep += 2);
    rep += listBook("docs/borrow.csv", rep);
    gotoxy(32, rep);
    printf("Enter to continue.\n");
    getchar();
    bookManagement();
    break;

  case 0:
    adminPanel();
    bookManagement();
    break;
  }
}

void userManagement(void) {
  int choice;

  headerLMS("User Management");

  gotoxy(22, 11);
  printf("----= 1. Add User   ");

  gotoxy(22, 13);
  printf("----= 2. Delete User   ");

  gotoxy(22, 15);
  printf("----= 3. List User ");

  gotoxy(22, 17);
  printf("----= 0. Go Back");

  gotoxy(20, 19);
  printf("============================================");

  gotoxy(22, 21);
  printf("----= Console :   ");
  scanf("%d", &choice);

  switch (choice) {
  case 1:
    system(clear);
    headerLMS("Add User");
    addUser();
    userManagement();
    break;

  case 2:
    system(clear);
    headerLMS("Delete User");
    deleteUser();
    userManagement();
    break;

  case 3:
    system(clear);
    headerLMS("User List");
    listUsers();
    printf("Enter to continue.\n");
    getchar();
    getchar();
    userManagement();
    break;

  case 0:
    adminPanel();
    userManagement();
    break;
  }
}

void userPanel() {
  int choice;

  headerLMS("User Panel");

  gotoxy(22, 11);
  printf("----= 1. List Book ");

  gotoxy(22, 13);
  printf("----= 2. Borrow Book ");

  gotoxy(22, 15);
  printf("----= 3. Return Book");

  gotoxy(22, 17);
  printf("----= 0. Log Out");

  gotoxy(20, 19);
  printf("============================================");

  gotoxy(22, 21);
  printf("----= Console :   ");
  scanf("%d", &choice);

  getchar();

  switch (choice) {
  case 1:
    system(clear);
    headerLMS("List Book");
    int rep = listBook("docs/book.csv", 11);
    gotoxy(32, rep += 2);
    printf("Enter to continue.\n");
    getchar();
    userPanel();
    break;

  case 2:
    system(clear);
    headerLMS("Borrow Book");
    borrowBook();
    userPanel();
    break;

  case 3:
    system(clear);
    headerLMS("Return Book");
    returnBook();
    userPanel();
    break;

  case 0:
    userOptions();
    userPanel();
    break;
  }
}