#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct pportField {
    char name[4];
    char value[20];
} pportField;

bool is_valid(pportField *passport, uint8_t p_len) {
  char *valid[7] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

  uint8_t valid_cnt = 0;
  for (uint8_t v = 0; v < 7; v++) {
    bool isPresent = false;
    for (uint8_t f = 0; f < p_len; f++) {
      if (strcmp(passport[f].name, valid[v]) == 0) {
        isPresent = true;
      }
    }
    valid_cnt += isPresent ? 1 : 0;
  }

  if (valid_cnt < 7)
    return false;

  size_t f_id = 0;
  while (f_id < p_len) {
    char *name = passport[f_id].name;
    char *value = passport[f_id].value;

    if (strcmp(name, "byr") == 0) {
      int num = atoi(value);
      if (strlen(value) != 4 || num < 1920 || num > 2002) return false;
    } 
    else if (strcmp(name, "iyr") == 0) {
      int num = atoi(value);
      if (strlen(value) != 4 || num < 2010 || num > 2020) return false;
    }
    else if (strcmp(name, "eyr") == 0) {
      int num = atoi(value);
      if (strlen(value) != 4 || num < 2020 || num > 2030) return false;
    }
    else if (strcmp(name, "hgt") == 0) {
      char *unit = &value[strlen(value)-2];
      uint8_t min, max;

      if (strcmp(unit, "cm") == 0) {
        min = 150; max = 193;
      }
      else if (strcmp(unit, "in") == 0) {
        min = 59; max = 76;
      }
      else {
        return false;
      }

      value[strlen(value)-2] = '\0';
      uint16_t num = atoi(value);
      if (num < min || num > max) return false;
    }
    else if (strcmp(name, "hcl") == 0) {
      if (value[0] != '#') return false;
      if (strlen(value) != 7) return false;

      char *valid_hex = "0123456789abcdef";
      for (uint8_t c = 1; c < 7; c++) {
        bool is_valid = false; 
        for (uint8_t h = 0; h < 16; h++) {
          if (value[c] == valid_hex[h])
            is_valid = true;
        }
        if (!is_valid) return false;
      }
    }
    else if (strcmp(name, "ecl") == 0) {
      char *valid_eyes[7] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
      bool is_valid = false;

      for (uint8_t i = 0; i < 7; i++) {
        if (strcmp(value, valid_eyes[i]) == 0)
          is_valid = true;
      }

      if (!is_valid) return false;
    }
    else if (strcmp(name, "pid") == 0) {
      if (strlen(value) != 9) return false;

      for (uint8_t i = 0; i < 9; i++) {
        if (value[i] < 0x30 || value[i] > 0x39)
          return false;
      }
    }

    f_id++;
  }

  return true;
}

int main() {
  FILE *fp = fopen("../input.txt", "r");

  if(!fp) {
    perror("Error opening file");
    return 1;
  }

  char buffer[100];
  uint16_t valid = 0;
  uint8_t p_len = 0;
  pportField *passport = NULL;

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    if (buffer[0] == '\n') {
      valid += is_valid(passport, p_len) ? 1 : 0;
      p_len = 0;
      continue;
    }

    char *rest;
    char *token = strtok_r(buffer, " ", &rest);
    while (token != NULL) {
      size_t t_len = strlen(token);
      if (token[t_len - 1] == '\n')
        token[t_len - 1] = '\0';  

      pportField *temp = (pportField*) realloc(passport, ++p_len*sizeof(pportField));
      if (!temp) {
        free(passport);
        return 1;
      }
      passport = temp;

      char *field_rest;
      pportField *currentField = &passport[p_len-1];
      snprintf(currentField->name, sizeof(currentField->name), "%s", strtok_r(token, ":", &field_rest));
      snprintf(currentField->value, sizeof(currentField->value), "%s", strtok_r(NULL, ":", &field_rest));

      token = strtok_r(NULL, " ", &rest);
    }
  }

  fclose(fp);
  free(passport);
  printf("%d\n", valid);
  return 0;
}

