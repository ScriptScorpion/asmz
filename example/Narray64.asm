; this example file for x86-64(amd64) devices and Netwide Assembler

section .data
	hello1: times 10 db 0 ; you can do this like that
	Len:  equ $-hello1 
section .bss
	hello2 resb 10 ; or like that
section .text
	global _start 

_start:
	sub rsp, 8  ; reserving stack for the value
	mov BYTE [rsp], 10 ; equivalent of this: push 10 (you cannot do 0x10, it will not work)
	mov DWORD [hello1], 0x31727261 ; 0x31727261 = arr1
	mov DWORD [hello2], 0x32727261 ; 0x32727261 = arr2

	mov rax, 1            
	mov rdi, 1          
	lea rsi, [rel hello1] ; pointer to the message 
	mov rdx, Len    
	syscall   

	mov rax, 1
	mov rdi, 1
	lea rsi, [rsp] ; newline
	mov rdx, 1
	syscall

	mov rax, 1
	mov rdi, 1
	lea rsi, [rel hello2] ; pointer to the message
	mov rdx, Len
	syscall

	mov rax, 1
	mov rdi, 1
	lea rsi, [rsp] ; newline
	mov rdx, 1
	syscall

	add rsp, 8 ; restoring stack
	mov rax, 60 ; exit
	xor rdi, rdi ; return 0      
	syscall        
