%define DATA_SIZE 4
%define SEED 1

section .text

global fisheryates
fisheryates: ; RDI: int *array, RSI: size_t length
  mov rcx, rsi
  mov rsi, rdi

  dec rcx
  jz .done

  .loop:
    call random

    xor edx, edx
    mov edi, ecx
    div edi

    mov eax, [rsi + rcx * DATA_SIZE]
    xchg eax, [rsi + rdx * DATA_SIZE]
    mov [rsi + rcx * DATA_SIZE], eax

    loop .loop

  .done:
    ret

; A NASM version for the C rand() function implementation
; suggested by ISO/IEC 9899:TC3 in section 7.20.2.1.
random:
  mov rax, [rel next]
  mov rdx, 1103515245
  mul rdx

  add rax, 12345
  mov [rel next], rax

  shr rax, 16
  and rax, 16383

  ret

section .data
  next: dq SEED
