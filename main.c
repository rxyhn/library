#include "lib/header.h"
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

int main(int argc, char **argv) {
  if (argc < 2) {
    welcomePage();
    system(clear);
    printf("You've attemped to login as user.\n");
    sleep(2);
    userOptions();
  } else if (argc == 2 && !strcmp(argv[1], "admin")) {
    welcomePage();
    system(clear);
    printf("You've attemped to login as admin.\n");
    sleep(2);
    adminLogin();
  } else {
    printf("\nArgument not found.\nAvailable argument:\n1. (none) -> login as "
           "user.\n2. admin -> login as admin.\n\n");
  }

  return 0;
}