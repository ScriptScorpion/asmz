# this example file for x86-64(amd64) devices and Gnu Assembler
.code64

.section .data
	hello: .ascii "Hello world!\n"  
	helloLen = .-hello            

.section .text
	.global _start

_start:
	movq $1, %rax          # 'write' system call = 4 in 32bit, in 64 bit Arch call=1
	movq $1, %rdi          # file descriptor 1 = STDOUT
	movq $hello, %rsi      # string to write
	movq $helloLen, %rdx   # length of string to write
	syscall               # call the kernel

	movq $60, %rax         # 'exit' system call
	xorq %rdi, %rdi        # exit with error code 0
	syscall               # call the kernel
