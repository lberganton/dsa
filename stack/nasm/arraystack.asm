%define NULL 0
%define DATA_LEN 4

%define DEFAULT_CAPACITY 16

%define ARRAYSTACK_OFFSET_ARRAY     0
%define ARRAYSTACK_OFFSET_ALLOCATED ARRAYSTACK_OFFSET_ARRAY     + 8
%define ARRAYSTACK_OFFSET_ELEMENTS  ARRAYSTACK_OFFSET_ALLOCATED + 8

%define ARRAYSTACK_SIZE 24

; struct ArrayStack {
;   int *array        : 8 bytes
;   size_t allocated  : 8 bytes
;   size_t elements   : 8 bytes
; }

section .text
  extern malloc
  extern realloc
  extern free

global arraystack_create
arraystack_create: ; (RDI: size_t initial_capacity) -> RAX: ArrayStack*
  push rdi
  mov rdi, ARRAYSTACK_SIZE
  call malloc wrt ..plt
  pop rdi

  cmp rax, NULL
  je .done

  mov rsi, DEFAULT_CAPACITY
  test rdi, rdi
  cmovz rdi, rsi

  mov qword [rax + ARRAYSTACK_OFFSET_ELEMENTS], 0
  mov qword [rax + ARRAYSTACK_OFFSET_ALLOCATED], rdi

  push rax
  lea rdi, [rdi * DATA_LEN]
  call malloc wrt ..plt
  mov rdi, rax
  pop rax

  mov [rax + ARRAYSTACK_OFFSET_ARRAY], rdi
  cmp rdi, NULL
  jne .done

  call free wrt ..plt

  .done:
    ret

increase: ; (RDI: ArrayStack *stack) -> RAX: bool
  mov rsi, [rdi + ARRAYSTACK_OFFSET_ALLOCATED]
  lea rsi, [rsi * 2 * DATA_LEN]

  push rdi
  mov rdi, [rdi + ARRAYSTACK_OFFSET_ARRAY]
  call realloc wrt ..plt
  pop rdi

  cmp rax, NULL
  je .failed

  mov [rdi + ARRAYSTACK_OFFSET_ARRAY], rax
  mov rsi, [rdi + ARRAYSTACK_OFFSET_ALLOCATED]
  lea rsi, [rsi * 2]
  mov [rdi + ARRAYSTACK_OFFSET_ALLOCATED], rsi

  mov rax, 1
  ret

  .failed:
    xor rax, rax
    ret

global arraystack_push
arraystack_push: ; (RDI: ArrayStack *stack, RSI: int val) -> RAX: bool
  mov rax, [rdi + ARRAYSTACK_OFFSET_ELEMENTS]
  cmp rax, [rdi + ARRAYSTACK_OFFSET_ALLOCATED]
  jne .insert_element

  push rdi
  push rsi
  call increase
  pop rsi
  pop rdi

  test rax, rax
  jnz .insert_element
  ret

  .insert_element:
    mov rax, [rdi + ARRAYSTACK_OFFSET_ARRAY]
    mov rdx, [rdi + ARRAYSTACK_OFFSET_ELEMENTS]

    mov dword [rax + rdx * DATA_LEN], esi
    inc dword [rdi + ARRAYSTACK_OFFSET_ELEMENTS]

  mov rax, 1
  ret

global arraystack_pop
arraystack_pop: ; (RDI: ArrayStack *stack, RSI: int *ret) -> RAX: bool
  xor rax, rax

  cmp dword [rdi + ARRAYSTACK_OFFSET_ELEMENTS], 0
  je .done

  cmp rsi, NULL
  je .pop

  mov rdx, [rdi + ARRAYSTACK_OFFSET_ARRAY]
  mov edx, [rdx + ARRAYSTACK_OFFSET_ELEMENTS * DATA_LEN]
  mov [rsi], edx

  .pop:
    dec dword [rdi + ARRAYSTACK_OFFSET_ARRAY + ARRAYSTACK_OFFSET_ELEMENTS]
    inc rax

  .done:
    ret

global arraystack_peek
arraystack_peek: ; (RDI: ArrayStack *stack, RSI: int *ret) -> RAX: bool
  xor rax, rax
  cmp qword [rdi + ARRAYSTACK_OFFSET_ELEMENTS], 0
  je .done

  mov rax, [rdi + ARRAYSTACK_OFFSET_ARRAY]
  mov rdx, [rdi + ARRAYSTACK_OFFSET_ELEMENTS]
  dec rdx
  mov eax, [rax + rdx * DATA_LEN]
  mov [rsi], eax

  .done:
    ret

global arraystack_equals
arraystack_equals: ; (RDI: ArrayStack *first, RSI: ArrayStack *second) -> RAX: bool
  xor rax, rax
  mov rcx, [rdi + ARRAYSTACK_OFFSET_ELEMENTS]
  cmp rcx, [rsi + ARRAYSTACK_OFFSET_ELEMENTS]
  jne .done

  mov rdi, [rdi + ARRAYSTACK_OFFSET_ARRAY]
  mov rsi, [rsi + ARRAYSTACK_OFFSET_ELEMENTS]

  mov rax, 1

  .iteration:
    test rcx, rcx
    jz .done

    mov rdx, [rdi]
    cmp rdx, [rsi]
    je .next

    xor rax, rax
    jmp .done

  .next:
    dec rcx
    add rdi, DATA_LEN
    add rsi, DATA_LEN
    jmp .iteration

  .done:
    ret

global arraystack_foreach
arraystack_foreach: ; (RDI: ArrayStack *stack, RSI: void (*consumer)(int val))
  mov rcx, [rdi + ARRAYSTACK_OFFSET_ELEMENTS]
  test rcx, rcx
  jz .done

  mov rdi, [rdi + ARRAYSTACK_OFFSET_ARRAY]
  lea rdi, [rdi + (rcx - 1) * DATA_LEN]

  .loop:
    push rcx
    push rdi
    push rsi

    mov rdi, [rdi]
    call rsi

    pop rsi
    pop rdi
    pop rcx

    dec rcx
    jz .done

    sub rdi, DATA_LEN
    jmp .loop

  .done:
    ret

global arraystack_free
arraystack_free: ; (RDI: ArrayStack *stack)
  push rdi
  mov rdi, [rdi + ARRAYSTACK_OFFSET_ARRAY]
  call free wrt ..plt

  pop rdi
  call free wrt ..plt
  ret

global arraystack_size
arraystack_size: ; (RDI: ArrayStack *stack) -> RAX: size_t
  mov rax, [rdi + ARRAYSTACK_OFFSET_ELEMENTS]
  ret

