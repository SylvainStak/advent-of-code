#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define MASK_LEN 36

typedef struct MemBlock {
  uint64_t address;
  uint64_t value;
} MemBlock;

void apply_mask(uint64_t *num, char *mask, uint8_t mask_len) {
  char binary[mask_len];
  for (uint8_t i = 0; i < mask_len; i++)
    binary[i] = '0';

  uint8_t i = mask_len;
  while (*num > 0) {
    binary[--i] = (*num % 2)+'0';
    *num /= 2;
  }
  
  for (uint8_t bit = 0; bit < mask_len; bit++) {
    if (mask[bit] == '1' || mask[bit] == '0') {
      binary[bit] = mask[bit];
    }
  }

  uint64_t mul = 1;
  for (int8_t bit = mask_len-1; bit >= 0; bit--) {
    if (binary[bit] == '1')
      *num += mul;
    mul *= 2;
  }
}


int main() {
  FILE *fp = fopen("../input.txt", "r");
  if(!fp) {
    perror("Error opening file");
    return 1;
  }
  
  char buffer[100];
  char mask[MASK_LEN];
  MemBlock *memory = NULL;
  uint64_t mem_len = 0;
  uint64_t total = 0;

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    if (buffer[1] == 'a') {
      sscanf(buffer, "mask = %s", mask);
      continue;
    }

    uint64_t address, value;
    sscanf(buffer, "mem[%lu] = %lu", &address, &value);
    apply_mask(&value, mask, MASK_LEN);

    bool found = false;
    for (uint64_t i = 0; i < mem_len; i++) {
      if (memory[i].address == address) {
        memory[i].value = value;
        found = true;
        break;
      }
    }

    if (!found) {
      MemBlock *temp = (MemBlock *) realloc(memory, ++mem_len*sizeof(MemBlock));
      if (!temp) {
        free(memory);
        return 1;
      }
      memory = temp;
      memory[mem_len-1].address = address;
      memory[mem_len-1].value = value;
    }
  }

  for (size_t i = 0; i < mem_len; i++) {
    printf("[%ld] => %ld\n", memory[i].address, memory[i].value);
    total += memory[i].value;
  }
  printf("%ld\n", total);

  fclose(fp);
  free(memory);
  return 0;
}

