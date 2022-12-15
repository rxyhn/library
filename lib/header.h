// #ifndef MARKER
// #define MARKER
// // declarations
// #include "lib/common/function.h"
// #include "lib/admin/book/function.h"
// #include "lib/admin/user/function.h"
// #endif

#include <stdio.h>

void gotoxy(int x, int y);
int countLines(FILE *file);
int isUsernameExists(FILE *file, char username[]);
int isIDExists(FILE *file, int ID);
void headerLMS(char str[]);
void addUser();
void deleteUser();
int listUsers();
void userManagement();
void userRegistration();
void addBook();
void deleteBook();
int listBook(char csv[], int pos);
void borrowBook();
void returnBook();
void adminPanel();
void bookManagement();
void userOptions();
void userPanel();
void welcomePage();
void adminLogin();
void userLogin();

struct users {
  int ID;
  char username[50];
  char password[50];
  int role;
};

struct books {
  int id;
  char book_name[1001];
  char author[1001];
};