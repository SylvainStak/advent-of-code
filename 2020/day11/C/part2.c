#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


const int8_t directions[8][2] = {{1,-1}, {1,0}, {1,1}, {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}};

typedef struct Seats {
  char **layout;
  uint32_t rows;
  uint32_t columns;
} Seats;

Seats *allocate_seats(uint32_t rows, uint32_t columns) {
  Seats *seats = (Seats *) malloc(sizeof(Seats));
  seats->rows = rows;
  seats->columns = columns;
  seats->layout = (char **) calloc(rows, sizeof(char *));
  for (size_t i = 0; i < rows; i++)
    seats->layout[i] = (char *) calloc(columns, sizeof(char));
  return seats;
}

void fill_layout(Seats *seats, const char *content) {
  for (size_t i = 0; i < seats->rows; i++) {
    for (size_t j = 0; j < seats->columns; j++) {
      seats->layout[i][j] = content[i*seats->columns+j];
    }
  }
}

void free_seats(Seats *seats) {
  for (size_t i = 0; i < seats->rows; i++) {
    free(seats->layout[i]);
  }
  free(seats->layout);
  free(seats);
}

bool equal_generations(const Seats *gen1, const Seats *gen2) {
  for (size_t i = 0; i < gen1->rows; i++) {
    for (size_t j = 0; j < gen1->columns; j++) {
      if (gen1->layout[i][j] != gen2->layout[i][j])
        return false;
    }
  }
  return true;
}

uint32_t count_seats_taken (Seats *seats) {
  uint32_t count = 0;
  for (size_t i = 0; i < seats->rows; i++) {
    for (size_t j = 0; j < seats->columns; j++) {
      count += seats->layout[i][j] == '#' ? 1 : 0;
    }
  }
  return count;
}

void copy_layout(Seats *dest, Seats *src) {
  for (size_t i = 0; i < src->rows; i++) {
    for (size_t j = 0; j < src->columns; j++) {
      dest->layout[i][j] = src->layout[i][j];
    } 
  }
}

void calc_next_gen(Seats *current, Seats *next) {
  copy_layout(next, current);
  for (size_t i = 0; i < current->rows; i++) {
    for (size_t j = 0; j < current->columns; j++) {
      if (current->layout[i][j] == '.') {
        continue;
      }

      uint8_t neighbors = 0;
      for (uint8_t dir = 0; dir < 8; dir++) {
        bool finished = false;
        int8_t deltaX = directions[dir][0];
        int8_t deltaY = directions[dir][1];
        int32_t x = i+deltaX;
        int32_t y = j+deltaY;
        while (!finished) {
          if (
            !(0 <= x && x < current->rows) ||
            !(0 <= y && y < current->columns) ||
            current->layout[x][y] == 'L'
          ) {
            finished = true;
          } else if (current->layout[x][y] == '#') {
            neighbors++;
            finished = true;
          }
          x += deltaX;
          y += deltaY;
        }
      }

      if (current->layout[i][j] == 'L' && neighbors == 0) {
        next->layout[i][j] = '#';
      } else if (current->layout[i][j] == '#' && neighbors > 4){
        next->layout[i][j] = 'L';
      }
    }
  }
}


int main() {
  FILE *fp = fopen("../input.txt", "r");
  if(!fp) {
    perror("Error opening file");
    return 1;
  }

  char buffer[1024];
  char *seats = NULL;
  uint32_t len_seats = 0;
  uint32_t columns = 0;
  uint32_t rows = 0;

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    rows++;
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
  fclose(fp);
  columns = len_seats/rows;

  Seats *curr = allocate_seats(rows, columns);
  Seats *next = allocate_seats(rows, columns);
  fill_layout(curr, seats);
  free(seats);

  while (!equal_generations(curr, next)) {
    calc_next_gen(curr, next);
    Seats *temp = curr;
    curr = next;
    next = temp;
  }

  printf("%d\n", count_seats_taken(curr));
  free_seats(curr);
  free_seats(next);
  return 0;
}

