.section .data
	buff1: .fill 10, 1, 0 #  you can do this like that
.section .bss
	buff2: .skip 10 # or like that
	buff3: .space 10 # same as the one above
.section .text
	.global _start 

_start:
	movq $0x6968, %rax # "ih" in hex
    push %rax
	movq $1, %rax     
	movq $1, %rdi            
	leaq (%rsp), %rsi
	movq $2, %rdx
	syscall

	movb $13, buff1 # carriage return
	movb $10, buff2 # newline

	movq $1, %rax
	movq $1, %rdi
	leaq buff1, %rsi
	movq $1, %rdx
	syscall
	
	movq $1, %rax
	movq $1, %rdi
	leaq buff2, %rsi
	movq $1, %rdx
	syscall

	movq $60, %rax      
	xorq %rdi, %rdi   
	syscall      

