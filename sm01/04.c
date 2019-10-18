#include <stdint.h>

#include <stdio.h>

enum shifts { 
  DIGITS_SHIFT = 10,
  UPPERCASE_SHIFT = 36,
  SET_SIZE_MAX = 62
};

uint64_t change_bit(uint64_t aim, uint64_t index, uint64_t value) {
  uint64_t mask = 1;
  mask <<= index;
  if (value) {
    aim |= mask;
  } else {
    aim &= ~mask;
  }
  return aim;
}

void print(uint64_t set) {
  for (int i = 0; i < SET_SIZE_MAX; ++i) {
    if (i < DIGITS_SHIFT && (((set >> i) & 1))) {
      printf("%c", (i + '0'));
    } else if (i >= DIGITS_SHIFT && i < UPPERCASE_SHIFT && (((set >> i) & 1))) {
      printf("%c", (i + 'A' - DIGITS_SHIFT));
    } else if (i >= UPPERCASE_SHIFT && (((set >> i) & 1))) {
      printf("%c", (i + 'a' - UPPERCASE_SHIFT));
    }
  }
  printf("\n");
}

int main() {
  uint64_t result = 0, temporary_set = 0;
  char symbol;

  while (scanf("%c", & symbol) != EOF) {
    if ('9' >= symbol && symbol >= '0') {
      temporary_set = change_bit(temporary_set, symbol - '0', 1);
    } else if ('Z' >= symbol && symbol >= 'A') {
      temporary_set = change_bit(temporary_set, symbol - 'A' + DIGITS_SHIFT, 1);
    } else if ('z' >= symbol && symbol >= 'a') {
      temporary_set = change_bit(temporary_set, symbol - 'a' + UPPERCASE_SHIFT, 1);
    } else {
      switch (symbol) {
      case '&':
        result &= temporary_set;
        break;
      case '|':
        result |= temporary_set;
        break;
      case '^':
        result ^= temporary_set;
        break;
      case '~':
        result = ~result;
        break;
      default:
        break;
      }
      temporary_set = 0;
    }
  }

  print(result);
  return 0;
}
