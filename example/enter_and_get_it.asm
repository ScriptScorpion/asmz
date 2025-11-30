; this example file for x86-64(amd64) devices and Netwide Assembler
section .data
    buff: times 255 db 0 ; fill buffer with 0
    buffs: equ $-buff
section .text
    global _start
_start:
    mov rax, 0 ; read
    mov rdi, 0 ; read
    mov rsi, buff ; buffer
    mov rdx, buffs ; buffer size
    syscall
    mov rdx, rax ; length of readed bytes 
    mov rax, 1 ; write
    mov rdi, 1 ; write
    mov rsi, buff ; write what was inputed
    syscall

    mov rax, 60 ; exit code
    xor rdi, rdi ; exit with error code 0
    syscall
