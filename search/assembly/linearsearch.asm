%define DATA_LEN 4

global linearsearch
linearsearch: ; RDI: int *array, ESI: int length, EDX: int val
  xor rcx, rcx
  xchg rdi, rsi

  .loop:
    cmp edx, [rsi + rcx * DATA_LEN]
    jne .not_found

    mov eax, ecx
    ret

  .not_found:
    inc rcx
    cmp rcx, rdi
    jne .loop

  mov eax, -1
  ret
