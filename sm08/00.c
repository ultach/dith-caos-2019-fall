#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char* file_name = argv[1];
    char* neddle = argv[2];
    int file = open(file_name, O_RDONLY);
    struct stat st;
    fstat(file, &st);
    char* haystack = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0);
    char* current = haystack;
    size_t haystack_size = st.st_size;
    size_t neddle_size = strlen(neddle);
    size_t current_size = haystack_size;
    while (1) {
        current = memmem(current, current_size, neddle, neddle_size);
        if (current == 0 || current == NULL) {
            break;
        }
        printf("%ld ", current - haystack);
        ++current;
        current_size = haystack_size - (current - haystack);
    }
    printf("\n");
    munmap(haystack, st.st_size);
    close(file);
    return 0;
}
