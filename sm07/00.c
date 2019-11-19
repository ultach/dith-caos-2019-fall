#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int exit_code = 0;
    int input = open(argv[1], O_RDONLY);

    if (input == -1) {
        exit_code = 1;
        goto finally;
    }
    int out_digits = open(argv[2], O_WRONLY | O_CREAT, 0640);
    int out_other = open(argv[3], O_WRONLY | O_CREAT, 0640);
    if (out_digits == -1 || out_other == -1) {
        exit_code = 2;
        goto finally;
    }

    ssize_t in_read;
    char in_byte;
    int out;
    while ((in_read = read(input, &in_byte, sizeof(in_byte))) > 0) {
        out = ('0' <= in_byte && in_byte <= '9') ? out_digits : out_other;
        if (write(out, &in_byte, sizeof(in_byte)) == -1) {
            exit_code = 3;
            goto finally;
        }
    }
    if (in_read == -1) {
        exit_code = 3;
        goto finally;
    }
finally:
    close(input);
    close(out_digits);
    close(out_other);
    return exit_code;
}