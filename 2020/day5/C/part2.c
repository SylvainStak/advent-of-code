#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int binary_decode(char* str, char lh_token, char uh_token, uint8_t min, uint8_t max) {
  if (min == max)
    return min;

  uint8_t new_limit = (max+min)/2;
  if (*str == lh_token) max = new_limit;
  else if (*str == uh_token) min = ++new_limit;

  return binary_decode(++str, lh_token, uh_token, min, max);
}

int32_t comparator (const void *p1, const void *p2) {
  return (*(uint32_t*)p1 - *(uint32_t*)p2);
}

int main() {
  FILE *fp = fopen("../input.txt", "r");
  if(!fp) {
    perror("Error opening file");
    return 1;
  }

  char buffer[12];
  uint32_t len_seats = 0;
  uint32_t *seats = NULL;

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    buffer[10] = '\0';
    uint8_t column = binary_decode((char *)(buffer+7), 'L', 'R', 0, 7);
    buffer[7] = '\0';
    uint8_t row = binary_decode(buffer, 'F', 'B', 0, 127);

    uint32_t *temp = (uint32_t *) realloc(seats, ++len_seats*sizeof(uint32_t));
    if (!temp) {
      free(seats);
      return 1;
    }
    seats = temp;
    seats[len_seats-1] = (uint32_t)(row*8+column);
  }

  qsort(seats, len_seats, sizeof(uint32_t), comparator);

  for (size_t i = 1; i < len_seats-1; i++) {
    if (seats[i+1] != seats[i]+1)
      printf("%d\n", seats[i]+1);
  }

  fclose(fp);
  free(seats);
  return 0;
}

