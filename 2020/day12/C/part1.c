#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int main() {
  FILE *fp = fopen("../input.txt", "r");
  if(!fp) {
    perror("Error opening file");
    return 1;
  }
  
  char buffer[100];
  char *compass = "NESW";
  uint8_t dir = 1;
  int32_t x = 0;
  int32_t y = 0;

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    char action = buffer[0];
    uint16_t value = atoi(&buffer[1]);
    if (action == 'L' || action == 'R') {
      uint8_t delta = value/90%4;
      dir += action == 'R' ? delta : -delta;   
    } else {
      if (action == 'F')
        action = compass[dir%4];
      switch (action) {
        case 'N': y += value; break;
        case 'E': x += value; break;
        case 'S': y -= value; break;
        case 'W': x -= value; break;
      }
    }
  }

  fclose(fp);
  printf("%d\n", abs(x)+abs(y));
  return 0;
}

