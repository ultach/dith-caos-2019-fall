#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char* concat(const char* s1, const char* s2)
{
    char* result =
        malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main()
{
    struct stat st;
    char file_name[PATH_MAX];
    while (fgets(file_name, sizeof(file_name), stdin)) {
        char* nl = memchr(file_name, '\n', sizeof(file_name));
        if (nl) {
            *nl = '\0';
        }
        if (lstat(file_name, &st) != -1) {
            if (S_ISLNK(st.st_mode)) {
                char path_to_file[PATH_MAX];
                realpath(file_name, path_to_file);
                printf("%s\n", path_to_file);
            } else if (S_ISREG(st.st_mode)) {
                symlink(file_name, concat("link_to_", file_name));
            }
        }
    }
    return 0;
}
