       .global my_sin    
       .intel_syntax noprefix
       .text
my_sin:
        push		ebp
        mov		ebp, esp
        push		eax
        movsd		xmm0, [ebp+8]
        movsd		xmm2, [ebp+8]
        movsd		xmm1, [ebp+8]
        subsd		xmm0, xmm0
        mov		eax, 1
        mov		ebx, 50000
        subsd		xmm4, xmm4
        cvtsi2sd	xmm6, ebx
        
Loop:
        subsd		xmm0, xmm1 
        mulsd		xmm0, xmm0
        comisd		xmm0, xmm4
        jbe		result
        add		eax, 1
        movsd		xmm0, xmm1
        movsd		xmm3, [ebp+8]
        mulsd		xmm2, xmm3
        mulsd		xmm2, xmm3
        cvtsi2sd	xmm5, eax
        divsd		xmm2, xmm5
        add		eax, 1
        cvtsi2sd	xmm5, eax
        mov		ebx, -1
        divsd		xmm2, xmm5
        cvtsi2sd	xmm5, ebx
        mulsd		xmm2, xmm5
        addsd		xmm1, xmm2
        jmp		Loop
result:
        movsd		[ebp + 8], xmm1
        fld		qword ptr [ebp + 8]
        pop		eax
        mov		esp, ebp
        pop		ebp
        ret
