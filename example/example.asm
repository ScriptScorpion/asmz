; this example file for amd64 devices
section .data
	hello:     db 'Hello world!', 10
	helloLen:  equ $-hello

section .text
	global _start 

_start:
	mov rax,1            ; 'write' system call = 4 in 32bit, in 64 bit Arch call=1
	mov rdi,1            ; file descriptor 1 = STDOUT
	mov rsi,hello        ; string to write
	mov rdx,helloLen     ; length of string to write
	syscall              ; call the kernel

	mov rax,60            ; 'exit' system call
	xor rdi,rdi            ; exit with error code 0
	syscall              ; call the kernel
