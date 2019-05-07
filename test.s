	.globl printf
	.type printf, @function
	.comm a, 40, 4
	.globl main
	.type main, @function
	.section .rodata
.string_ro_0:
	.string "a[%d] is %d\n"
	.data
	.align 4
.string_0:
	.long .string_ro_0
	.section .rodata
.string_ro_1:
	.string "Hak is god\n"
	.data
	.align 4
.string_1:
	.long .string_ro_1
	.section .rodata
.string_ro_2:
	.string "Hak is not god\n"
	.data
	.align 4
.string_2:
	.long .string_ro_2
	.section .rodata
.string_ro_3:
	.string "Hak is not god\n"
	.data
	.align 4
.string_3:
	.long .string_ro_3
	.section .rodata
.string_ro_4:
	.string "Hak is still god\n"
	.data
	.align 4
.string_4:
	.long .string_ro_4
	.text
main:
	pushl %ebp
	movl %esp, %ebp
	subl $72, %esp
.BB.1.1:
	lea a, %ecx	#lea
	movl %ecx, -16(%ebp)
	movl $5, %eax	#mul
	xor %edx, %edx
	movl $4, %ebx
	mul %ebx
	movl %eax, -24(%ebp)
	movl -16(%ebp), %ecx	#add
	addl -24(%ebp), %ecx
	movl %ecx, -20(%ebp)
	movl -20(%ebp), %ecx	#load
	movl (%ecx), %ebx
	movl %ebx, -12(%ebp)
	lea -12(%ebp), %ecx	#lea
	movl %ecx, -12(%ebp)
	movl -12(%ebp), %ecx	#mov
	movl %ecx, -12(%ebp)
	movl $0, %ecx	#mov
	movl %ecx, -4(%ebp)
	jmp .BB.1.2
.BB.1.2:
	movl -4(%ebp), %ecx	#comp
	movl $10, %ebx
	cmp %ebx, %ecx
	jl .BB.1.3
	jmp .BB.1.5
.BB.1.3:
	lea a, %ecx	#lea
	movl %ecx, -28(%ebp)
	movl -4(%ebp), %eax	#mul
	xor %edx, %edx
	movl $4, %ebx
	mul %ebx
	movl %eax, -36(%ebp)
	movl -28(%ebp), %ecx	#add
	addl -36(%ebp), %ecx
	movl %ecx, -32(%ebp)
	movl -4(%ebp), %ecx	#store
	movl -32(%ebp), %ebx
	movl %ecx, (%ebx)
	jmp .BB.1.4
.BB.1.4:
	movl -4(%ebp), %ecx	#add
	addl $1, %ecx
	movl %ecx, -4(%ebp)
	jmp .BB.1.2
.BB.1.5:
	movl $0, %ecx	#mov
	movl %ecx, -4(%ebp)
	jmp .BB.1.6
.BB.1.6:
	movl -4(%ebp), %ecx	#comp
	movl $10, %ebx
	cmp %ebx, %ecx
	jl .BB.1.7
	jmp .BB.1.9
.BB.1.7:
	lea a, %ecx	#lea
	movl %ecx, -40(%ebp)
	movl -4(%ebp), %eax	#mul
	xor %edx, %edx
	movl $4, %ebx
	mul %ebx
	movl %eax, -48(%ebp)
	movl -40(%ebp), %ecx	#add
	addl -48(%ebp), %ecx
	movl %ecx, -44(%ebp)
	movl -44(%ebp), %ecx	#load
	movl (%ecx), %ebx
	movl %ebx, -52(%ebp)
	movl -52(%ebp), %ecx	#arg
	pushl %ecx
	movl -4(%ebp), %ecx	#arg
	pushl %ecx
	movl .string_0, %ecx	#arg
	pushl %ecx
	call printf	#call
	addl $12, %esp
	jmp .BB.1.8
.BB.1.8:
	movl -4(%ebp), %ecx	#add
	addl $1, %ecx
	movl %ecx, -4(%ebp)
	jmp .BB.1.6
.BB.1.9:
	lea a, %ecx	#lea
	movl %ecx, -56(%ebp)
	movl $9, %eax	#mul
	xor %edx, %edx
	movl $4, %ebx
	mul %ebx
	movl %eax, -64(%ebp)
	movl -56(%ebp), %ecx	#add
	addl -64(%ebp), %ecx
	movl %ecx, -60(%ebp)
	movl -60(%ebp), %ecx	#load
	movl (%ecx), %ebx
	movl %ebx, -68(%ebp)
	movl -68(%ebp), %ecx	#comp
	movl $9, %ebx
	cmp %ebx, %ecx
	je .BB.1.10
	jmp .BB.1.11
.BB.1.10:
	movl .string_1, %ecx	#arg
	pushl %ecx
	call printf	#call
	addl $4, %esp
	jmp .BB.1.12
.BB.1.11:
	movl .string_2, %ecx	#arg
	pushl %ecx
	call printf	#call
	addl $4, %esp
	jmp .BB.1.12
.BB.1.12:
	movl -12(%ebp), %ecx	#load
	movl (%ecx), %ebx
	movl %ebx, -72(%ebp)
	movl -72(%ebp), %ecx	#comp
	movl $4, %ebx
	cmp %ebx, %ecx
	je .BB.1.13
	jmp .BB.1.14
.BB.1.13:
	movl .string_3, %ecx	#arg
	pushl %ecx
	call printf	#call
	addl $4, %esp
	jmp .BB.1.15
.BB.1.14:
	movl .string_4, %ecx	#arg
	pushl %ecx
	call printf	#call
	addl $4, %esp
	jmp .BB.1.15
.BB.1.15:
	movl $69, %eax	#return
	leave
	ret
	