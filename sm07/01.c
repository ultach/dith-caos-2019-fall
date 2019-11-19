#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
    int value;
    uint32_t next_pointer;
} Item;

int main(int argc, char* argv[])
{

    int input_file = open(argv[1], O_RDONLY);
    if (input_file == -1) {
        return 0;
    }
    Item item;
    ssize_t in_read;
    while ((in_read = read(input_file, &item, sizeof(item))) > 0) {
        if (in_read == -1) {
            goto ret;
        }
        printf("%d ", item.value); // TODO

        if ((item.next_pointer == 0) ||
            (lseek(input_file, item.next_pointer, SEEK_SET) == -1)) {
            goto ret;
        }
    }
    printf("\n");
ret:
    close(input_file);
    return 0;
}
