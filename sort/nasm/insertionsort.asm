%define DATA_LEN 4

section .text

global insertionsort
insertionsort: ; RDI: int *array, RSI: size_t length
  xchg rsi, rdi
  mov rcx, 1

  .outer_loop:
    cmp rcx, rdi
    jge .done

    mov rdx, rcx

  .inner_loop:
    mov eax, [rsi + rdx * DATA_LEN]
    cmp eax, [rsi + (rdx - 1) * DATA_LEN]
    jge .next

    xchg eax, [rsi + (rdx - 1) * DATA_LEN]
    mov [rsi + rdx * DATA_LEN], eax

    dec rdx
    jnz .inner_loop

  .next:
    inc rcx
    jmp .outer_loop

  .done:
    ret
