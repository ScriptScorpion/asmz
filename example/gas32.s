# this example file for x86(i386) devices and Gnu Assembler
.code32

.section .data
	hello: .asciz "GAS IS BEST! \n" # string and newline character "\n" in C/C++, asciz instead of ascii to add Null terminator 
	helloLen = .-hello          # length of string

.section .text
	.global _start

_start:
	movl $4, %eax          # 'write' system call = 4 in 32bit, in 64 bit Arch call=1
	movl $1, %ebx          # file descriptor 1 = STDOUT
	movl $hello, %ecx      # string to write
	movl $helloLen, %edx   # length of string to write
	int $0x80               # call the kernel

	movl $1, %eax         # 'exit' system call
	xorl %ebx, %ebx        # exit with error code 0
	int $0x80               # call the kernel
