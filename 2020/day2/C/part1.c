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
    int min, max;
    char target, passwd[30];
    sscanf(buffer, "%d-%d %c: %s", &min, &max, &target, passwd);

    int count = 0;
    size_t i = 0;
    while (passwd[i] != '\0') {
      if (passwd[i] == target) count++;
      i++;
    }

    valid += min <= count && count <= max ? 1 : 0;    
  }

  fclose(fp);
  printf("%d\n", valid);
  return 0;
}

