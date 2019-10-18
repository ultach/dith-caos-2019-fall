.text
.global main
main:
    @ keep stack 8-byte aligned
    push {ip, lr}

    @ scanf for number
    ldr r0, =fmtInt
    sub sp, sp, #4
    mov r1, sp
    sub sp, sp, #4
    mov r2, sp
    bl scanf

    @ get scan values
    ldr r1, [sp]
    add sp, sp, #4
    ldr r2, [sp]
    add sp, sp, #4

    add r1, r1, r2

    ldr r0, =textOut
    bl printf

    @ return 0
    mov r0, #0

    @ reverse align
    pop {ip, pc}

@ vars and stuff
.data
fmtInt:     .asciz "%d%d"
textOut:    .asciz "%d\n"


