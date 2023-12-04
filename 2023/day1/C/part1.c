#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_SIZE 1024

int main() {
  int total = 0;
  char line[MAX_LINE_SIZE];
  FILE *fp = fopen("input.txt", "r");

  if(fp == NULL) {
    perror("Error opening file");
    return(1);
  }

  while (fgets(line, sizeof(line), fp) != NULL) {
    int line_total = 0, first = 0, last;

    for(size_t i = 0; i < strlen(line) - 1; i++) {
      int number = line[i] - 0x30;

      if (number >= 1 && number <= 9) {
        if (!first) {
          line_total += number * 10;
          first = 1;
        }
        last = number;
      }
    }

    total += line_total+last;
  }

  fclose(fp);
  printf("%d\n", total);
  return(0);
}

