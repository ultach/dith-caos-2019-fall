#include <inttypes.h>
#include <stdio.h>
#include <windows.h>

typedef struct {
    int value;
    uint32_t next_pointer;
} Item;

int main(int argc, TCHAR* argv[])
{
    HANDLE inputFile = CreateFileA(
        argv[1],
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (inputFile == INVALID_HANDLE_VALUE) {
        printf("CAN'T OPEN FILE!\n");
        return 0;
    }
    DWORD nBytesRead;
    Item item;
    LARGE_INTEGER liMoveTo;
    while (1) {
        BOOL bResult =
            ReadFile(inputFile, &item, sizeof(item), &nBytesRead, NULL);
        if (bResult && nBytesRead == 0) {
            break;
        }
        printf("%d ", item.value);
        liMoveTo.QuadPart = item.next_pointer;
        if (item.next_pointer == 0 ||
            SetFilePointerEx(inputFile, liMoveTo, NULL, FILE_BEGIN) == 0) {
            break;
        }
    }
    printf("\n");
    CloseHandle(inputFile);
    return 0;
}