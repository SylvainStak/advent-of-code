#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


int main() {
  FILE *fp = fopen("../input.txt", "r");
  if(!fp) {
    perror("Error opening file");
    return 1;
  }
  
  char buffer[1024];
  fgets(buffer, sizeof(buffer), fp);
  uint32_t bid;
  uint32_t curr = atoi(buffer);
  uint32_t min = UINT32_MAX;

  fgets(buffer, sizeof(buffer), fp);
  buffer[strlen(buffer)-1] = '\0';
  char *rest;
  char *token = strtok_r(buffer, ",", &rest);
  while (token != NULL) {
    if (token[0] != 'x') {
      uint32_t _bid = atoi(token);
      uint32_t next_min = _bid*(curr/_bid+1);
      if (next_min < min) {
        min = next_min;
        bid = _bid;
      }
    }
    token = strtok_r(NULL, ",", &rest);
  }

  fclose(fp);
  printf("%d\n", (min-curr)*bid);
  return 0;
}

