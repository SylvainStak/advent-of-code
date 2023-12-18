#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 


int main() {
  FILE *fp = fopen("../input.txt", "r");
  if(!fp) {
    perror("Error opening file");
    return 1;
  }

  char buffer[69];
  char *answered = NULL;
  uint32_t len_answered = 0;
  uint32_t total = 0;

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    if (buffer[0] == '\n') {
      total += len_answered;
      len_answered = 0;
      continue;
    }

    for (size_t b_i = 0; b_i < strlen(buffer)-1; b_i++) {
      bool is_duplicated = false;
      size_t answer_i = 0;
      while (!is_duplicated && answer_i < len_answered) {
        if (buffer[b_i] == answered[answer_i]) {
          is_duplicated = true;
        }
        answer_i++;
      }

      if (!is_duplicated) {
        char *temp = (char *) realloc(answered, ++len_answered*sizeof(char));
        if (!temp) {
          free(answered);
          return 1;
        }
        answered = temp;
        answered[len_answered-1] = buffer[b_i];
      }
    }
  }

  fclose(fp);
  free(answered);
  printf("%d\n", total);
  return 0;
}

