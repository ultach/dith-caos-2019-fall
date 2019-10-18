.text
.global solve
solve:
        // Сравниваем D (r3) с нулем, и возращаем 0 если D=0
        cmp     r3, #0
        beq     return
        // Сохраняем значение регистров на стэке
        push    {r4, r5, r6, r7, lr}
        mov     r5, r0
        mov     r4, r2
        // x = r0
        mov     r0, #0
start:
        // Инкрементируем x (++x)
        add     r0, r0, #1
        // Сохранием x^2 в r6
        mul     r6, r0, r0
        // Сохраняем x^3 в r7
        mul     r7, r0, r6
        // r6 = B * x^2
        mul     r6, r1, r6
        // r7 = A * x^3 + B * x^ 2
        mla     r7, r5, r7, r6
        // r2 = C * x
        mul     r2, r4, r0
        // r7 += r2
        add     r7, r2
        cmn     r7, r3
        bne     start
        pop     {r4, r5, r6, r7, pc}
return:
        mov     r0, r3
        bx      lr
