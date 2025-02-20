%define DATA_LEN 4

section .text

global selectionsort:
selectionsort: ; RDI: int *array, RSI: size_t length
  push rbx                                        ; The SysV ABI define that RBX must be preserved.

  mov rbx, rdi
  mov rcx, rsi
  dec rcx

  test rcx, rcx
  jnz .outer_loop

  pop rbx
  ret

  .outer_loop:
    mov rsi, rbx
    mov rdx, rcx

    mov rdi, rsi

  .inner_loop:
    mov eax, [rsi + DATA_LEN]
    cmp eax, [rdi]
    jle .no_swap

    mov rdi, rsi
    add rdi, DATA_LEN

  .no_swap:
    mov eax, [rdi]
    xchg eax, [rsi + rdx * DATA_LEN]
    mov [rdi], eax

    add rsi, DATA_LEN
    dec rdx
    jnz .inner_loop

    dec rcx
    jnz .outer_loop

  pop rbx
  ret
