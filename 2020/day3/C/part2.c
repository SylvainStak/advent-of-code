#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fp = fopen("../input.txt", "r");
  if(!fp) {
    perror("Error opening file");
    return 1;
  }
  
  size_t f_len = 0;
  char *forest = NULL;
  char buffer[50];
  size_t total = 1;
  unsigned short n_trees = 0;
  unsigned short n_columns = 0;
  unsigned short slopes[5][2] = {{1,1}, {3,1}, {5,1}, {7,1}, {1,2}};
  
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    size_t i = 0;
    while (buffer[i] != '\n') {
      ++f_len;
      char *temp = (char*) realloc(forest, f_len*sizeof(char));
      if (!temp) {
        free(forest);
        return 1;
      }
      forest = temp;
      forest[f_len-1] = buffer[i];
      ++i;
    }
    n_columns = i;
  }
  fclose(fp);

  for (size_t i = 0; i < 5; i++) {
    size_t row_i = 0;
    size_t col_i = 0;
    while (row_i < f_len/n_columns) {
      n_trees += forest[row_i*n_columns+(col_i%n_columns)] == '#' ? 1 : 0;
      row_i += slopes[i][1];
      col_i += slopes[i][0];
    }
    total *= n_trees;
    n_trees = 0;
  }

  free(forest);
  printf("%ld\n", total);
  return 0;
}

