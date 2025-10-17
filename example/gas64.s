# this example file for x86-64(amd64) devices and Gnu Assembler
# Disclaimer: you can write in GAS without b,w,l,q, after operation, but this in some cases can give error if you don't specify this.
.code64

.section .data
	hello: .asciz "GAS IS BEST! \n"   # string and newline character "\n" in C/C++, asciz instead of ascii to add Null terminator  
	helloLen = .-hello         # length of string          

.section .text
	.global _start

_start:
	movq $1, %rax          # 'write' system call = 4 in 32bit, in 64 bit Arch call=1
	movq $1, %rdi          # file descriptor 1 = STDOUT
	leaq hello(%rip), %rsi  # string to write
	movq $helloLen, %rdx   # length of string to write
	syscall               # call the kernel

	movq $60, %rax         # 'exit' system call
	xorq %rdi, %rdi        # exit with error code 0
	syscall               # call the kernel
