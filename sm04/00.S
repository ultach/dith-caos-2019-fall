	.global summ
	.intel_syntax noprefix
	.text
summ:
	push	ebx
	mov	ecx, N
.Loop:
	mov	ebx, ecx
	dec	ebx
	mov	edx, A
	mov	eax, [edx + 4*ebx]
	mov	edx, B
	add	eax, [edx + 4*ebx]
	mov	edx, R
	mov	[edx + 4*ebx], eax

	loop	.Loop
	
	pop	ebx
	ret
	
	.global everyday795
everyday795:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	push	ebx

	mov	ebx, ebp
	sub	ebx, 4
	push	ebx
	mov	ebx, offset scanf_format_string
	push	ebx
	call	scanf
	add	esp, 8

	mov	ebx, [ebp-4]
	imul	ebx, [ebp+8]
	add	ebx, [ebp+12]
	
	push	ebx
	mov	ebx, printf_format_string_ptr
	push	ebx
	call	printf
	add	esp, 8

	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret
scanf_format_string:
	.string "%d"
printf_format_string_ptr:
	.long	printf_format_string

	.data
printf_format_string:
	.string	"%d\n"
