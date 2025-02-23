%define DATA_LEN 4

section .text

global bubblesort
bubblesort: ; RDI: int *array, RSI: size_t length
  push rbx                                        ; The SysV ABI define that RBX must be preserved.

  mov rbx, rdi
  mov rcx, rsi
  dec rcx

  test rcx, rcx
  jz .done

  .outer_loop:
    mov rsi, rbx
    mov rdx, rcx

  .inner_loop:
    mov eax, [rsi]
    cmp eax, [rsi + DATA_LEN]
    jle .next

    xchg eax, [rsi + DATA_LEN]
    mov [rsi], eax

  .next:
    add rsi, DATA_LEN
    dec rdx
    jnz .inner_loop

    dec rcx
    jnz .outer_loop

  .done:
    pop rbx
    ret
