%define DATA_LEN 4

section .text

global quicksort:
quicksort: ; RDI: int *array, RSI: size_t low, RDX: size_t high
  push rbx

  cmp rsi, rdx
  jge .done

  mov eax, [rdi + rdx * DATA_LEN]
  mov rbx, rsi
  mov rcx, rsi

  .iteration:
    cmp rcx, rdx
    jge .pivot

    mov r8d, [rdi + rcx * DATA_LEN]

    cmp r8d, eax
    jge .next

    xchg r8d, [rdi + rbx * DATA_LEN]
    mov [rdi + rcx * DATA_LEN], r8d

    inc rbx

    .next:
      inc rcx
      jmp .iteration


  .pivot:
    mov r8d, [rdi + rdx * DATA_LEN]
    xchg r8d, [rdi + rbx * DATA_LEN]
    mov [rdi + rdx * DATA_LEN], r8d

  .recursion_left:
    test rbx, rbx
    jz .recursion_right

    push rsi
    push rdx

    lea rdx, [rbx - 1]
    call quicksort

    pop rdx
    pop rsi

  .recursion_right:
    lea rsi, [rbx + 1]
    call quicksort

  .done:
    pop rbx
    ret
