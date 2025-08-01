; This example file for x86-64(amd64) devices and Netwide Assembler

section .data
    prompt      db  "Guess a number (1-100): ", 0     ; Prompt message
    prompt_len  equ $ - prompt                       ; Length of prompt
    too_low     db  "Too low!", 10, 0                ; "Too low" message
    too_low_len equ $ - too_low                      ; Length of "Too low"
    too_high    db  "Too high!", 10, 0               ; "Too high" message
    too_high_len equ $ - too_high                    ; Length of "Too high"
    correct     db  "Correct! You win!", 10, 0       ; Win message
    correct_len equ $ - correct                      ; Length of win message
    invalid     db  "Error: Enter a number!", 10, 0  ; Invalid input message
    invalid_len equ $ - invalid                      ; Length of error message
    newline     db  10                               ; Newline character
    input_buf   times 16 db 0                        ; Input buffer (16 bytes)

section .bss
    rand_num    resd 1                               ; Stores the random number
    user_guess  resd 1                               ; Stores user's guess
    time_buf    resd 1                               ; Buffer for sys_time result

section .text
    global _start

_start:
    ; --- Get current time (Unix timestamp) for seed ---
    mov rax, 201                                     ; sys_time syscall (201)
    mov rdi, time_buf                                ; Pointer to store timestamp
    syscall

    ; --- Use timestamp as seed for LCG ---
    mov eax, [time_buf]                              ; Load timestamp
    mov [rand_num], eax                              ; Store as seed

    ; --- Generate random number (1-100) using LCG ---
    call rand_lcg                                    ; Update rand_num
    xor edx, edx                                     ; Clear edx for division
    mov ecx, 100                                     ; Divide by 100 (range 0-99)
    div ecx                                          ; edx = remainder (0-99)
    inc edx                                          ; Adjust to 1-100
    mov [rand_num], edx                              ; Store final random number

game_loop:
    ; --- Print prompt ---
    mov rax, 1                                       ; sys_write syscall
    mov rdi, 1                                       ; stdout file descriptor
    mov rsi, prompt                                  ; Pointer to message
    mov rdx, prompt_len                              ; Message length
    syscall

    ; --- Read user input ---
    mov rax, 0                                       ; sys_read syscall
    mov rdi, 0                                       ; stdin file descriptor
    mov rsi, input_buf                               ; Buffer to store input
    mov rdx, 16                                      ; Max bytes to read
    syscall

    ; --- Convert ASCII input to integer (atoi) ---
    mov rsi, input_buf                               ; Pointer to input buffer
    xor eax, eax                                     ; Clear eax (stores result)
    xor ecx, ecx                                     ; Clear ecx (digit counter)
    xor edx, edx                                     ; Clear edx (stores number)

convert_loop:
    movzx ebx, byte [rsi + rcx]                      ; Load next character
    cmp bl, 10                                       ; Check for newline (end of input)
    je convert_done                                  ; If newline, conversion done
    cmp bl, '0'                                      ; Check if character < '0'
    jb invalid_input                                 ; If yes, invalid input
    cmp bl, '9'                                      ; Check if character > '9'
    ja invalid_input                                 ; If yes, invalid input
    sub bl, '0'                                      ; Convert ASCII to digit
    imul edx, edx, 10                                ; Multiply current number by 10
    add edx, ebx                                     ; Add new digit
    inc ecx                                          ; Move to next character
    jmp convert_loop                                 ; Repeat

invalid_input:
    ; --- Print "Invalid input" message ---
    mov rax, 1                                       ; sys_write
    mov rdi, 1                                       ; stdout
    mov rsi, invalid                                 ; Error message
    mov rdx, invalid_len                             ; Message length
    syscall
    jmp game_loop                                    ; Restart game loop

convert_done:
    mov [user_guess], edx                            ; Store converted number

    ; --- Compare guess with random number ---
    mov eax, [user_guess]                            ; Load user's guess
    cmp eax, [rand_num]                              ; Compare with target number
    jl  less                                         ; If guess < target, jump to "less"
    jg  greater                                      ; If guess > target, jump to "greater"
    je  win                                          ; If equal, jump to "win"

less:
    ; --- Print "Too low" ---
    mov rax, 1                                       ; sys_write
    mov rdi, 1                                       ; stdout
    mov rsi, too_low                                 ; "Too low" message
    mov rdx, too_low_len                             ; Message length
    syscall
    jmp game_loop                                    ; Repeat game loop

greater:
    ; --- Print "Too high" ---
    mov rax, 1                                       ; sys_write
    mov rdi, 1                                       ; stdout
    mov rsi, too_high                                ; "Too high" message
    mov rdx, too_high_len                            ; Message length
    syscall
    jmp game_loop                                    ; Repeat game loop

win:
    ; --- Print Win message ---
    mov rax, 1                                       ; sys_write
    mov rdi, 1                                       ; stdout
    mov rsi, correct                                 ; Win message
    mov rdx, correct_len                             ; Message length
    syscall

    ; --- Exit program ---
    mov rax, 60                                      ; sys_exit
    xor rdi, rdi                                     ; Exit code 0
    syscall

; --- LCG Pseudorandom Number Generator ---
rand_lcg:
    mov eax, [rand_num]                              ; Load current seed
    mov ecx, 1664525                                 ; Multiplier (a)
    mul ecx                                          ; eax = eax * ecx
    add eax, 1013904223                              ; Add increment (c)
    mov [rand_num], eax                              ; Store new seed
    ret
