; this example file for x86(i386) devices and Netwide Assembler
bits 32

section .data
	hello:     db 'Hello world!', 10
	helloLen:  equ $-hello

section .text
	global _start 

_start:
	mov eax, 4            ; 'write' system call = 4 in 32bit, in 64 bit Arch call=1
	mov ebx, 1            ; file descriptor 1 = STDOUT
	mov ecx,hello        ; string to write
	mov edx,helloLen     ; length of string to write
	int 0x80              ; call the kernel

	mov eax, 1            ; 'exit' system call
	mov ebx, 0            ; exit with error code 0
	int 0x80              ; call the kernel
