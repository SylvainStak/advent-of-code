#include <stdio.h>

int main() {
  FILE *fp = fopen("../input.txt", "r");
  char line[1024];
  int total = 0;

  if(fp == NULL) {
    perror("Error opening file");
    return(1);
  }

  while (fgets(line, sizeof(line), fp) != NULL) {
    int c_id = -1;
    int first = 0, last = 0;
    while (line[c_id++] != '\n') {
      if (line[c_id] >= 0x31 && line[c_id] <= 0x39) {
        int num = line[c_id] - 0x30;
        first += first == 0 ? num * 10 : 0;
        last = num;
      }
    }
    total += first+last;
  }

  fclose(fp);
  printf("%d\n", total);
  return(0);
}

