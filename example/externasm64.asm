; this example file for x86-64(amd64) devices and Netwide Assembler
; for compilation do: nasm -f elf64 externasm64.asm -o exe.o && gcc exe.o -o exe -no-pie
section .data
    text: db "NASM IS BEST!", 10, 0   

section .text
    global main
    extern printf

main:
    lea rdi, [rel text] ; loading relative adress of text(better then move)    
    xor eax, eax        ; setting eax to 0
    call printf         
    ret
    leave
