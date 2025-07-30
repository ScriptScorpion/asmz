; this example file for x86-64(amd64) devices and Netwide Assembler
bits 64

section .data
    num dw '9999'      ; number as ASCII-symbol IT'S OVER 9000
    newline db 10    ; newline character \n in C/C++
    length equ $-num   ; length of number

section .text
    global _start

_start:
    mov rax, 1          ; sys_write
    mov rdi, 1          ; stdout
    mov rsi, num        ; adress of line
    mov rdx, length     ; length of output
    syscall 

    ; print new line
    mov rsi, newline   ; newline charcter
    mov rdx, 1         ; length of newline character(if you set it to other number it can sometimes crash programm)
    syscall

    ; exiting
    mov rax, 60         ; sys_exit
    xor rdi, rdi        ; return 0
    syscall
