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
  int32_t x = 0;
  int32_t y = 0;
  int32_t wx = 10;
  int32_t wy = 1;

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    char action = buffer[0];
    uint16_t value = atoi(&buffer[1]);
    if (action == 'L' || action == 'R') {
      int32_t temp = wx;
      uint32_t rot = value/90%4;
      // rot 1: 90 Degrees
      // rot 2: 180 Degrees
      // rot 3: 270 Degrees
      // action R: Clockwise
      // action L: Counter-clockwise
      if ((rot == 1 && action == 'R') || (rot == 3 && action == 'L')) {
        wx = wy;
        wy = -temp;
      } else if ((rot == 1 && action == 'L') || (rot == 3 && action == 'R')) {
        wx = -wy;
        wy = temp;
      } else {
        wx = -wx;
        wy = -wy;
      }
    } else {
      switch (action) {
        case 'N': wy += value; break;
        case 'E': wx += value; break;
        case 'S': wy -= value; break;
        case 'W': wx -= value; break;
        case 'F': x += wx*value; y += wy*value; break;
      }
    }
  }

  fclose(fp);
  printf("%d\n", abs(x)+abs(y));
  return 0;
}

