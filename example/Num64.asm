; this example file for x86-64(amd64) devices and Netwide Assembler
bits 64

section .data
    num dw "9999", 10, 0      ; number as ASCII-symbol and newline character in ASCII, "\n" in C/C++ and Null terminator to know programm where line ends
    length equ $-num-1   ; length of number, -1 because Null terminator

section .text
    global _start

_start:
    mov rax, 1          ; sys_write
    mov rdi, 1          ; stdout
    lea rsi, [rel num]  ; adress of line
    mov rdx, length     ; length of output
    syscall 

    ; exiting
    mov rax, 60         ; sys_exit
    xor rdi, rdi        ; return 0
    syscall
