section .data
    string: db "/bin/sh", 0
section .text
    global _start
_start:
   mov rax, 0x3b
   lea rdi, [string]
   mov rsi, 0
   mov rdx, 0
   syscall
   
   mov rax, 60
   xor rdi, rdi
   syscall
