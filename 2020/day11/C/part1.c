#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main() {
  FILE *fp = fopen("../input_test.txt", "r");
  if(!fp) {
    perror("Error opening file");
    return 1;
  }

  char buffer[200];
  char *seats = NULL;
  size_t len_seats = 0;
  size_t width = 0;
  size_t height = 0;

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    height++;
    for (size_t i = 0; i < strlen(buffer)-1; i++) {
      char *temp = (char *) realloc(seats, ++len_seats*sizeof(char));
      if (!temp) {
        free(seats);
        return 1;
      }
      seats = temp;
      seats[len_seats-1] = buffer[i];
    }
  }

  width = len_seats/height;

  fclose(fp);
  printf("%ld\n", strlen(seats));
  printf("%s\n", seats);
  printf("%ld\n", height);
  printf("%ld\n", width);
  free(seats);
  return 0;
}

