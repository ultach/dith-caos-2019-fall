    .global sort_by_age
    .text

@ sort_by_age:
@ void sort_by_age(int N, person_t *persons) 
@ typedef struct Person {
@     uint32_t  id; // 4                 [r1]
@     uint8_t   age; // 1 + 3            [r1, #4]
@     char      first_name[20]; // 4     [r1, #8]
@     char      last_name[20];  // 4     [r1, #28]
@ } person_t;

sort_by_age:
    
    push    {r4-r7, lr}
    
    mov r4, r0
    mov r5, r0
    mov r6, r0
    mov r7, r1
    mov r0, r1
    add r0, #48
    



start:
    sub r4, #1
    cmp r4, #0
    beq increment

    ldrsb r2, [r0, #4]  // r2 = age1
    ldrsb r3, [r1, #4]  // r3 = age2
     
    cmp r2, r3
    
    blt swap
next:    
    add r0, r0, #48
    add r1, r1, #48

    b start

increment:
    cmp r5, #0
    beq return
    sub r5, #1
    mov r4, r6
    mov r0, r7
    mov r1, r7
    add r0, #48
    b start

swap:
    push {r1-r12}    
    ldr     r4, [r1]
    ldr     r5, [r0]
    str     r4, [r0]
    str     r5, [r1]
    add r0, #4
    add r1, #4

    ldrsb   r4, [r1]
    ldrsb   r5, [r0]
    strb    r4, [r0]
    strb    r5, [r1]
    
    add r0, #1
    add r1, #1

    ldm r0, {r2-r6}
    ldm r1, {r7-r11}
    stm r0, {r7-r11}
    stm r1, {r2-r6}
    add r0, r0, #20
    add r1, r1, #20
    ldm r0, {r2-r6}
    ldm r1, {r7-r11}
    stm r0, {r7-r11}
    stm r1, {r2-r6}
    sub r0, r0, #25
    sub r1, r1, #25

    pop {r1-r12}
    b next

return:
    pop     {r4-r7, pc}
    bx lr



    
    
    
