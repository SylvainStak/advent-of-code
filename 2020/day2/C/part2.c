#include <stdio.h>

int main() {
  FILE *fp = fopen("../input.txt", "r");
  char buffer[50];
  int valid = 0;

  if(!fp) {
    perror("Error opening file");
    return 1;
  }

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    int i1, i2;
    char target, passwd[30];
    sscanf(buffer, "%d-%d %c: %s", &i1, &i2, &target, passwd);

    unsigned short count = 0;
    count += passwd[i1-1] == target ? 1 : 0;
    count += passwd[i2-1] == target ? 1 : 0;
    valid += count == 1 ? 1 : 0; 
  }

  fclose(fp);
  printf("%d\n", valid);
  return 0;
}

