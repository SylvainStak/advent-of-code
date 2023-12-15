#include <stdio.h>
#include <stdlib.h>

int find_number(int *arr, size_t len) {
  for (size_t i = 0; i < len; i++) {
    for (size_t j = 0; j < len; j++) {
      int n1 = arr[i];
      int n2 = arr[j];
      if (n1 != n2 && n1+n2 == 2020)
        return n1*n2;
    }
  }
  return 0;
}

int main() {
  FILE *fp = fopen("../input.txt", "r");
  size_t len = 0;
  int *arr = NULL;
  char buffer[10];

  if(!fp) {
    perror("Error opening file");
    return 1;
  }

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    ++len;
    int *temp = (int*) realloc(arr, len*sizeof(int));
    if (!temp) {
      free(arr);
      return 1;
    }
    arr = temp;
    arr[len-1] = atoi(buffer);
  }

  fclose(fp);
  printf("%d\n", find_number(arr, len));
  free(arr);
  return 0;
}

