#include <stdio.h>
#include <stdint.h>

int binary_decode(char* str, char lh_token, char uh_token, uint8_t min, uint8_t max) {
  if (min == max)
    return min;

  uint8_t new_limit = (max+min)/2;
  if (*str == lh_token) max = new_limit;
  else if (*str == uh_token) min = ++new_limit;

  return binary_decode(++str, lh_token, uh_token, min, max);
}


int main() {
  FILE *fp = fopen("../input.txt", "r");
  if(!fp) {
    perror("Error opening file");
    return 1;
  }

  char buffer[12];
  uint32_t highest_seat_id = 0;

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    buffer[10] = '\0';
    uint8_t column = binary_decode((char *)(buffer+7), 'L', 'R', 0, 7);
    buffer[7] = '\0';
    uint8_t row = binary_decode(buffer, 'F', 'B', 0, 127);

    uint32_t seat_id = row*8+column;
    if (seat_id > highest_seat_id)
      highest_seat_id = seat_id;
  }

  fclose(fp);
  printf("%d\n", highest_seat_id);
  return 0;
}

