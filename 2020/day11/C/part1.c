#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Seats {
  char **layout;
  uint32_t rows;
  uint32_t columns;
} Seats;

Seats allocate_seats(uint32_t rows, uint32_t columns) {
  Seats seats = { NULL, rows, columns };
  seats.layout = (char **) calloc(rows, sizeof(char *));
  for (size_t i = 0; i < rows; i++)
    seats.layout[i] = (char *) calloc(columns, sizeof(char));
  return seats;
}

void fill_layout(Seats seats, const char *content) {
  for (size_t i = 0; i < seats.rows; i++) {
    for (size_t j = 0; j < seats.columns; j++) {
      seats.layout[i][j] = content[i*seats.columns+j];
    }
  }
}

void free_seats(Seats *seats) {
  for (size_t i = 0; i < seats->rows; i++) {
    free(seats->layout[i]);
  }
  free(seats->layout);
}

bool equal_generations(const Seats gen1, const Seats gen2) {
  for (size_t i = 0; i < gen1.rows; i++) {
    for (size_t j = 0; j < gen1.columns; j++) {
      if (gen1.layout[i][j] != gen2.layout[i][j])
        return false;
    }
  }
  return true;
}

uint32_t count_free_seats (Seats seats) {
  uint32_t count = 0;
  for (size_t i = 0; i < seats.rows; i++) {
    for (size_t j = 0; j < seats.columns; j++) {
      count += seats.layout[i][j] == '#' ? 1 : 0;
    }
  }
  return count;
}

void copy_layout(Seats dest, Seats src) {
  for (size_t i = 0; i < src.rows; i++) {
    for (size_t j = 0; j < src.columns; j++) {
      dest.layout[i][j] = src.layout[i][j];
    } 
  }
}

void calc_next_gen(Seats current, Seats next) {
  copy_layout(next, current);
  for (size_t i = 0; i < current.rows; i++) {
    for (size_t j = 0; j < current.columns; j++) {
      if (current.layout[i][j] == '.') {
        continue;
      }

      uint8_t neighbors = 0;
      for (int8_t x = -1; x <= 1; x++){
        for (int8_t y = -1; y <= 1; y++){
          uint32_t w_x = i+x;
          uint32_t w_y = j+y;
          if (
            0 <= w_x && w_x < current.rows &&
            0 <= w_y && w_y < current.columns &&
            (w_x != i || w_y != j) &&
            current.layout[w_x][w_y] == '#'
          ) {
            neighbors++;
          }
        }
      }

      if (current.layout[i][j] == 'L' && neighbors == 0) {
        next.layout[i][j] = '#';
      } else if (current.layout[i][j] == '#' && neighbors > 3){
        next.layout[i][j] = 'L';
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

  Seats curr = allocate_seats(rows, columns);
  Seats next = allocate_seats(rows, columns);
  fill_layout(curr, seats);
  free(seats);

  while (!equal_generations(curr, next)) {
    calc_next_gen(curr, next);
    Seats temp = curr;
    curr = next;
    next = temp;
  }

  printf("%d\n", count_free_seats(curr));
  free_seats(&curr);
  free_seats(&next);
  return 0;
}

