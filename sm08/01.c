#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct {
    int value;
    uint32_t next_pointer;
} Item;

int main(int argc, char* argv[])
{
    char* file_name = argv[1];
    int file = open(file_name, O_RDONLY);
    struct stat st;
    fstat(file, &st);
    if (st.st_size == 0) {
        goto finally;
    }
    char* content = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0);
    Item* current = (Item*)content;
    printf("%d ", current->value);
    while (current->next_pointer != 0) {
        current = (Item*)(content + current->next_pointer);
        printf("%d ", current->value);
    }
    munmap(content, st.st_size);
finally:
    close(file);
    return 0;
}