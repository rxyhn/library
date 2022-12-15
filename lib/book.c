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

void addBook() {
  int rep = listBook("docs/book.csv", 11);
  struct books book;
  FILE *fp;
  fp = fopen("docs/book.csv", "a");
  gotoxy(22, rep += 2);
  printf("Enter Book ID : ");
  scanf("%d", &book.id);
  getchar();
  gotoxy(22, rep += 2);
  printf("Enter Book Name : ");
  scanf("%[^\n]s", book.book_name);
  getchar();
  gotoxy(22, rep += 2);
  printf("Enter Author Name : ");
  scanf("%[^\n]s", book.author);
  getchar();
  fprintf(fp, "%d, %s, %s,\n", book.id, book.book_name, book.author);
  fclose(fp);
}

void deleteBook() {

  int rep = listBook("docs/book.csv", 11);

  struct books book;
  FILE *fp;
  fp = fopen("docs/book.csv", "r");
  if (fp == NULL) {
    system(clear);
    printf("File doesn't exists.");
    sleep(1);
    userManagement();
  }
  gotoxy(22, rep += 2);
  printf("Enter ID: ");
  scanf("%d", &book.id);

  // Check if ID exists
  struct books temp;
  FILE *fp2;
  fp2 = fopen("docs/book.csv", "r");
  int found = 0;
  while (fscanf(fp2, "%d, %1001[^,], %1001[^,],", &temp.id, temp.book_name,
                temp.author) != EOF) {
    if (temp.id == book.id) {
      found = 1;
      break;
    }
  }
  fclose(fp2);

  if (found == 0) {
    gotoxy(23, 12);
    printf("ID does not exist. Please try again.\n");
    sleep(1);
    deleteBook();
  }

  // Delete the book by the id
  FILE *fp3;
  fp3 = fopen("temp.csv", "w");
  while (fscanf(fp, "%d, %1001[^,], %1001[^,],", &temp.id, temp.book_name,
                temp.author) != EOF) {
    if (temp.id != book.id) {
      fprintf(fp3, "%d, %s, %s,\n", temp.id, temp.book_name, temp.author);
    }
  }

  fclose(fp);
  fclose(fp3);

  remove("docs/book.csv");
  rename("temp.csv", "docs/book.csv");

  gotoxy(22, rep += 2);
  printf("Book deleted.\n");
  sleep(1);
}

int listBook(char csv[], int pos) {
  FILE *fp;
  fp = fopen(csv, "r");
  gotoxy(13, pos);
  printf("Book ID\t\t   Book Name\t      Author Name\n");
  // while (fscanf(fp, "%d %s %s", &book.id, book.book_name, book.author) !=
  // EOF) {
  //   printf("%d\t\t%s\t\t%s\n", book.id, book.book_name, book.author);
  // }
  char buffer[1024];
  int row = pos += 1;
  int column = 0;
  while (fgets(buffer, 1024, fp)) {
    column = 0;
    char *value = strtok(buffer, ",");
    gotoxy(11, ++row);
    int i = -9;
    while (value) {
      gotoxy(i += 22, row);
      printf("%s", value);
      value = strtok(NULL, ",");
      putchar('\t');
      putchar('\t');
      column++;
    }
  }
  fclose(fp);

  return row;
}

// void searchBook() {
//   headerLMS("Search Book");
//   struct books book;
//   FILE *fp;
//   char book_name[1001];
//   fp = fopen("docs/book.csv", "r");
//   gotoxy(22, 11);
//   printf("Enter Book Name : ");
//   scanf("%[^\n]", book_name);
//   while (fscanf(fp, "%d %[^,]s %[^,]s", &book.id, book.book_name,
//                 book.author) != EOF) {
//     if (strcmp(book_name, book.book_name) == 0) {
//       printf("%d\t%s\t%s\n", book.id, book.book_name, book.author);
//     }
//   }
//   fclose(fp);
// }

void borrowBook() {
  headerLMS("Borrow Book");

  // show book list
  int rep = listBook("docs/book.csv", 11);

  // select book by id
  gotoxy(22, rep += 2);
  int id;
  printf("Enter Book ID : ");
  scanf("%d", &id);
  getchar();

  // check book is available or not
  struct books book;
  FILE *fp;
  fp = fopen("docs/book.csv", "r");
  int found = 0;
  while (fscanf(fp, "%d, %1001[^,], %1001[^,],", &book.id, book.book_name,
                book.author) != EOF) {
    if (book.id == id) {
      found = 1;
      break;
    }
  }
  fclose(fp);

  if (found == 0) {
    printf("Book isn't available!\n");
    sleep(1);
    return;
  }

  // if book is available then add to docs/borrow.csv
  FILE *fp2;
  fp2 = fopen("docs/borrow.csv", "a");
  fprintf(fp2, "%d, %s, %s,\n", book.id, book.book_name, book.author);
  fclose(fp2);

  // remove book from docs/book.csv
  FILE *fp3;
  fp3 = fopen("temp.csv", "w");

  FILE *fp4;
  fp4 = fopen("docs/book.csv", "r");
  while (fscanf(fp4, "%d, %1001[^,], %1001[^,],", &book.id, book.book_name,
                book.author) != EOF) {
    if (book.id != id) {
      fprintf(fp3, "%d, %s, %s,\n", book.id, book.book_name, book.author);
    }
  }
  fclose(fp4);
  fclose(fp3);

  remove("docs/book.csv");
  rename("temp.csv", "docs/book.csv");

  // show book is borrowed
  gotoxy(22, rep += 2);
  printf("Book is borrowed\n");
  sleep(1);
}

void returnBook() {

  // show borrow list
  struct books book;
  FILE *fp;
  int rep = listBook("docs/borrow.csv", 11);

  // select book by id
  int id;
  gotoxy(22, rep += 2);
  printf("Enter Book ID : ");
  scanf("%d", &id);
  getchar();

  // check book is available or not
  fp = fopen("docs/borrow.csv", "r");
  int found = 0;
  while (fscanf(fp, "%d, %[^,], %[^,],\n", &book.id, book.book_name,
                book.author) != EOF) {
    if (book.id == id) {
      found = 1;
      break;
    }
  }
  fclose(fp);

  if (found == 0) {
    gotoxy(22, rep += 2);
    printf("Book isn't available!\n");
    sleep(1);
    return;
  }

  // if book is available then add to docs/book.csv
  FILE *fp2;
  fp2 = fopen("docs/book.csv", "a");
  fprintf(fp2, "%d, %s, %s,\n", book.id, book.book_name, book.author);
  fclose(fp2);

  // remove book from docs/borrow.csv
  FILE *fp3;
  fp3 = fopen("temp.csv", "w");

  FILE *fp4;
  fp4 = fopen("docs/borrow.csv", "r");
  while (fscanf(fp4, "%d, %[^,], %[^,],\n", &book.id, book.book_name,
                book.author) != EOF) {
    if (book.id != id) {
      fprintf(fp3, "%d, %s, %s,\n", book.id, book.book_name, book.author);
    }
  }
  fclose(fp4);
  fclose(fp3);

  remove("docs/borrow.csv");
  rename("temp.csv", "docs/borrow.csv");

  // show book is returned
  gotoxy(22, rep += 2);
  printf("Book is returned\n");
  sleep(1);
}
