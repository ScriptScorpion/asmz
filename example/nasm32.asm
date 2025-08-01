; this example file for x86(i386) devices and Netwide Assembler
bits 32

section .data
	hello:     db "NASM IS BEST!", 10, 0 ; string and newline character in ASCII, "\n" in C/C++ and Null terminator to know program where line ends
	helloLen:  equ $-hello-1 	; length of string -1 because of Null terminator 

section .text
	global _start 

_start:
	mov eax, 4            ; 'write' system call = 4 in 32bit, in 64 bit Arch call=1
	mov ebx, 1            ; file descriptor 1 = STDOUT
	lea ecx, [rel hello]  ; string to write
	mov edx, helloLen     ; length of string to write
	int 0x80              ; call the kernel

	mov eax, 1            ; 'exit' system call
	mov ebx, 0            ; exit with error code 0
	int 0x80              ; call the kernel
