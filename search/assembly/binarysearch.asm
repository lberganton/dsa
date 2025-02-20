%define DATA_LEN 4

section .text

global binarysearch
binarysearch: ; RDI: int *array, ESI: int length, EDX: int val
  push rbx                                        ; The SysV ABI define that RBX must be preserved.

  mov rbx, rdi
  mov rdi, rsi
  xor rsi, rsi
  dec rdi

  .loop:
    cmp rsi, rdi
    jg .done

    mov rcx, rsi
    add rcx, rdi
    shr rcx, 1

    mov eax, [rbx + rcx * DATA_LEN]

    cmp edx, eax
    jl .less
    jg .greater

    pop rbx
    mov rax, rcx
    ret

  .less:
    mov rdi, rcx
    dec rdi
    jmp .loop

  .greater:
    mov rsi, rcx
    inc rsi
    jmp .loop

  .done:
    mov rax, -1
    pop rbx
    ret
