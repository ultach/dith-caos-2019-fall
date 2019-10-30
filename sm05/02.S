.intel_syntax noprefix
.text
.global dot_product

dot_product:
    push ebp
    mov ebp, esp
    sub esp, 4
    push esi
    push edi 

    mov eax, [ebp+8]
    mov ecx, 0
    mov edx, [ebp+12]
    mov edi, [ebp+16]

init:
    sub eax, ecx 
    cmp eax, 3
    jle conditions
    jmp Loop

Loop:
    add eax, ecx
    movups xmm0, [edx+ecx*4] 
    movups xmm1, [edi+ecx*4] 
    dpps xmm0, xmm1, 0xff 
    addss xmm2, xmm0
    add ecx, 4
    jmp init 

conditions:
    cmp eax, 1
    je condition_1
    cmp eax, 2
    je condition_2
    cmp eax, 3
    je condition_3
    cmp eax, 0
    je end

condition_1:
    add ecx, eax
    dec ecx
    movss xmm5, [edx+ecx*4] 
    movss xmm4, [edi+ecx*4]
    mulss xmm5, xmm4
    addss xmm2, xmm5
    jmp end

condition_2:
    add ecx, eax
    sub ecx, 2
    movss xmm3, [edx+ecx*4]
    movss xmm4, [edi+ecx*4]
    mulss xmm3, xmm4
    inc ecx
    movss xmm4, [edx+ecx*4]
    movss xmm5, [edi+ecx*4]
    mulss xmm4, xmm5
    addss xmm3, xmm4
    addss xmm2, xmm3
    jmp end

condition_3:
    add ecx, eax
    sub ecx, 3
    movss xmm3, [edx+ecx*4]
    movss xmm4, [edi+ecx*4]
    mulss xmm3, xmm4
    inc ecx
    movss xmm4, [edx+ecx*4]
    movss xmm5, [edi+ecx*4]
    mulss xmm4, xmm5
    inc ecx
    movss xmm5, [edx+ecx*4]
    movss xmm6, [edi+ecx*4]
    mulss xmm5, xmm6
    addss xmm3, xmm4
    addss xmm3, xmm5
    addss xmm2, xmm3
    jmp end

end:
    movss [ebp-4], xmm2
    fld dword ptr [ebp-4]
    pop edi
    pop esi
    add esp, 4
    leave
    ret

