#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int counter = 1;
    pid_t process_id;
    do {
        process_id = fork();
        if (process_id != -1) {
            ++counter;
        }
    } while (process_id == 0);
    if (process_id > 0) {
        int status;
        waitprocess_id(process_id, &status, 0);
    }

    else if (process_id == -1) {
        printf("%d\n", counter);
    }
    return 0;
}