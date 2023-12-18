#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 


typedef struct groupAnswer {
  char id;
  uint8_t count;
} groupAnswer;

int main() {
  FILE *fp = fopen("../input.txt", "r");
  if(!fp) {
    perror("Error opening file");
    return 1;
  }

  char buffer[69];
  groupAnswer *answers = NULL;
  uint8_t len_answers = 0;
  uint8_t len_group = 0;
  uint32_t total = 0;

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    if (buffer[0] == '\n') {
      uint8_t all_answered = 0;
      for (size_t i = 0; i < len_answers; i++)
        all_answered += answers[i].count == len_group ? 1 : 0;

      total += all_answered;
      len_answers = 0;
      len_group = 0;
      continue;
    }

    for (size_t b_i = 0; b_i < strlen(buffer)-1; b_i++) {
      bool is_duplicated = false;
      uint8_t answer_i = 0;
      while (!is_duplicated && answer_i < len_answers) {
        if (buffer[b_i] == answers[answer_i].id) {
          is_duplicated = true;
        }
        answer_i++;
      }

      if (!is_duplicated) {
        groupAnswer *temp = (groupAnswer *) realloc(answers, ++len_answers*sizeof(groupAnswer));
        if (!temp) {
          free(answers);
          return 1;
        }
        answers = temp;
        answers[len_answers-1].id = buffer[b_i];
        answers[len_answers-1].count = 1;
      } else {
        answers[answer_i-1].count += 1;
      }
    }

    len_group++;
  }

  fclose(fp);
  free(answers);
  printf("%d\n", total);
  return 0;
}

