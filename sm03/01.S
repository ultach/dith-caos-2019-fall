	.text
	.global	main
main:
    push   {r4, r5, lr}
    ldr    r4, =stdin
    ldr    r5, =stdout
    b      loop

cond:
    subs   r0, r0, #48
	cmp    r0, #9
    add    r0, r0, #48
    bls    print
loop:
	ldr    r0, [r4]
	bl     fgetc
	cmp    r0, #-1
    bne    cond
    b      return
print:
	ldr    r1, [r5]
	bl     fputc
	b      loop
return:
    mov    r0, #0
    pop    {r4, r5, pc}