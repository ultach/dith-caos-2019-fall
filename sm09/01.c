#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int n = strtol(argv[1], NULL, 10);
    if (n == 1) {
        printf("1\n");
        return 0;
    }

    pid_t process_id = 0;
    int status;
    int process_counter = 1;

    do {
        process_id = fork();
        waitpid(process_id, &status, 0);
        ++process_counter;
    } while (process_counter < n && process_id == 0);
    if (process_id == 0) {
        printf("1 ");
    } else if (process_counter == 2) {
        printf("%d\n", n);
    } else {
        printf("%d ", n - process_counter + 2);
    }

    return 0;
}
