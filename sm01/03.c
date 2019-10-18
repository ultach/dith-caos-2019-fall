#include "stdio.h"

#include <string.h>

int main(int argc, char ** argv) {
  for (int i = 1; i < argc; i++) {
    int result = 0;
    for (int j = 2; j < strlen(argv[i]); ++j) {
      if (argv[i][j - 1] == 'x') {
        if (argv[i][j] > '0' && argv[i][j] <= '1') {
          result += 1;
        } else if (argv[i][j] >= '2' && argv[i][j] <= '3') {
          result += 2;
        } else if (argv[i][j] >= '4' && argv[i][j] <= '7') {
          result += 3;
        } else {
          result += 4;
        }
      } else {
        result += 4;
      }
    }
    result = result % 8 > 0 ? result / 8 + 1 : result / 8;
    printf("%d ", result);
  }
  return 0;
}
