# this example file for x86-64(amd64) devices and Gnu Assembler

.section .data
    prompt:         .asciz "Guess a number (1-100): "  # Prompt message
    too_low:        .asciz "Too low!\n"                # "Too low" message 
    too_high:       .asciz "Too high!\n"               # "Too high" message
    correct:        .asciz "Correct! You win!\n"       # Win message
    invalid:        .asciz "Error: Enter a number!\n"  # Invalid input message
    newline:        .asciz "\n"                        # Newline character

.section .bss
    .lcomm rand_num, 4       # 32-bit random number storage
    .lcomm user_guess, 4     # 32-bit user input storage  
    .lcomm time_buf, 4       # Buffer for sys_time result
    .lcomm input_buf, 16     # Input buffer (16 bytes)

.section .text
    .global _start

_start:
    
    # Get current time for seed
    mov $201, %rax       # sys_time syscall number (201)
    lea time_buf, %rdi   # Load address of time buffer
    syscall

    # Set LCG seed
    mov time_buf, %eax   # Load timestamp into eax
    mov %eax, rand_num   # Store as initial seed

    # Generate Random Number (1-100)
    call rand_lcg        # Call random number generator
    
    # Prepare for division
    xor %edx, %edx       # Clear edx (for division)
    mov $100, %ecx       # Divide by 100 for range 0-99
    div %ecx             # Divide: edx = remainder (0-99)
    inc %edx             # Adjust to range 1-100
    mov %edx, rand_num   # Store final random number

game_loop:
    # Print promt message
    mov $1, %rax         # sys_write syscall
    mov $1, %rdi         # stdout file descriptor
    mov $prompt, %rsi    # Pointer to prompt message
    mov $23, %rdx        # Message length
    syscall

    # Read user input
    mov $0, %rax         # sys_read syscall  
    mov $0, %rdi         # stdin file descriptor
    mov $input_buf, %rsi # Input buffer address
    mov $16, %rdx        # Buffer size
    syscall

    # Convert ASCII to integer
    mov $input_buf, %rsi # Pointer to input buffer
    xor %eax, %eax       # Clear result register
    xor %ecx, %ecx       # Clear digit counter
    xor %edx, %edx       # Clear number storage

convert_loop:
    movzb (%rsi, %rcx), %ebx # Load next character
    cmp $10, %bl         # Check for newline (end of input)
    je convert_done      # If newline, conversion complete
    cmp $'0', %bl        # Check if character < '0'
    jb invalid_input     # If yes, invalid input
    cmp $'9', %bl        # Check if character > '9'
    ja invalid_input     # If yes, invalid input
    sub $'0', %ebx       # Convert ASCII to digit
    imul $10, %edx       # Multiply current number by 10
    add %ebx, %edx       # Add new digit
    inc %rcx             # Move to next character
    jmp convert_loop     # Repeat

invalid_input:
    # Print error message
    mov $1, %rax         # sys_write
    mov $1, %rdi         # stdout
    mov $invalid, %rsi   # Error message pointer
    mov $21, %rdx        # Message length
    syscall
    jmp game_loop        # Restart game loop

convert_done:
    mov %edx, user_guess # Store converted number

    # Compare guess with target number
    mov user_guess, %eax # Load user's guess
    cmp rand_num, %eax   # Compare with target number
    jl too_low_msg       # If guess < target
    jg too_high_msg      # If guess > target
    je win_msg           # If equal

too_low_msg:
    # Print "Too low" message
    mov $1, %rax         # sys_write
    mov $1, %rdi         # stdout
    mov $too_low, %rsi   # Message pointer
    mov $9, %rdx         # Message length
    syscall
    jmp game_loop        # Repeat game loop

too_high_msg:
    # Print "Too high" message
    mov $1, %rax         # sys_write
    mov $1, %rdi         # stdout
    mov $too_high, %rsi  # Message pointer
    mov $10, %rdx        # Message length
    syscall
    jmp game_loop        # Repeat game loop

win_msg:
    # Print win message
    mov $1, %rax         # sys_write
    mov $1, %rdi         # stdout
    mov $correct, %rsi   # Message pointer
    mov $18, %rdx       # Message length
    syscall

    # Exit program
    mov $60, %rax        # sys_exit syscall
    xor %rdi, %rdi       # Exit code 0
    syscall

# LCG Pseudorandom Number Generator

rand_lcg:
    mov rand_num, %eax   # Load current seed
    mov $1664525, %ecx   # Multiplier (a)
    mul %ecx             # eax = eax * ecx
    add $1013904223, %eax # Add increment (c)
    mov %eax, rand_num   # Store new seed
    ret
