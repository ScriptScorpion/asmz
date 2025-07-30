# this example file for x86-64(amd64) devices and Gnu Assembler
.code64

.section .data
    num: .ascii "9999 \n"      # number as ASCII-symbol with new line symbol for simplicity IT'S OVER 9000
    length = .-num   # length of number

.section .text
    .global _start

_start:
    mov $1, %rax          # sys_write
    mov $1, %rdi          # stdout
    mov $num, %rsi        # adress of line
    mov $length,%rdx     # length of output
    syscall 

    # exiting
    mov $60, %rax         # sys_exit
    xor %rdi, %rdi        # return 0
    syscall

