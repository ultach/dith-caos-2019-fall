#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv) {
    char string[32];
    char *p;
    double x;
    int y, z;
    scanf("%lf%s", &x, string);
    y = strtol(string, &p, 16);
    z = strtol(argv[1], &p, 27);

    printf("%0.3f\n", x + y + z);
    return 0;
}
