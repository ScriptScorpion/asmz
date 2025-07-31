# this example file for x86-64(amd64) devices and Gnu Assembler
.code64

.section .data
    num: .ascii "9999 \n"      # number as ASCII-symbol with new line symbol for simplicity IT'S OVER 9000
    length = .-num   # length of number

.section .text
    .global _start

_start:
    movq $1, %rax          # sys_write
    movq $1, %rdi          # stdout
    movq $num, %rsi        # adress of line
    movq $length,%rdx     # length of output
    syscall 

    # exiting
    movq $60, %rax         # sys_exit
    xorq %rdi, %rdi        # return 0
    syscall

