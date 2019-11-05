#include <asm/unistd_32.h>
     .intel_syntax noprefix
     .text
     .global _start
_start:
    push ebp
    mov  ebp, esp
loop1:   
    mov edx, 1              // max length
    mov ecx, ebp          //buffer
    mov ebx, 0             // stdin
    mov eax, __NR_read     // sys_read
    int 0x80

    cmp eax, 0             //end loop if read <= 0
    jle lpend1

    mov edx, eax           //length
    mov ecx, ebp           //buffer
    mov ebx, 1             //stdout
    mov eax, __NR_write    //sys_write
    int 0x80
    jmp loop1              //go back for more
lpend1: 
     mov eax, 1
     mov ebx, 0
     pop ebp
     int 0x80
