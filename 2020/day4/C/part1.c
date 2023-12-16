#include <stdio.h>
#include <string.h>


int main() {
  FILE *fp = fopen("../input.txt", "r");
  char *valid[7] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
  char buffer[80];
  unsigned short subcount = 0;
  unsigned short total = 0;

  if(!fp) {
    perror("Error opening file");
    return 1;
  }

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    if (buffer[0] == '\n') {
      total += subcount == 7 ? 1 : 0;
      subcount = 0;
      continue;
    }
    
    for (size_t i = 0; i < 7; i++) {
      subcount += strstr(buffer, valid[i]) ? 1 : 0;
    }
  }

  fclose(fp);
  printf("%d\n", total);
  return 0;
}

