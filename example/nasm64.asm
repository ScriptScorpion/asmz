; this example file for x86-64(amd64) devices and Netwide Assembler
bits 64

section .data
	hello:     db "NASM IS BEST!", 10, 0 ; string and newline character in ASCII, "\n" in C/C++ and Null terminator to know program where line ends
	helloLen:  equ $-hello-1 ; length of string -1 because of Null terminator

section .text
	global _start 

_start:
	mov rax, 1            ; 'write' system call = 4 in 32bit, in 64 bit Arch call=1
	mov rdi, 1            ; file descriptor 1 = STDOUT
	lea rsi, [rel hello]  ; string to write
	mov rdx, helloLen     ; length of string to write
	syscall              ; call the kernel

	mov rax,60            ; 'exit' system call
	xor rdi,rdi            ; exit with error code 0
	syscall              ; call the kernel
