%define NULL 0

%define LINKEDSTACK_OFFSET_TOP      0
%define LINKEDSTACK_OFFSET_ELEMENTS LINKEDSTACK_OFFSET_TOP + 8

%define NODE_OFFSET_VAL 0
%define NODE_OFFSET_NEXT NODE_OFFSET_VAL + 8

%define LINKEDSTACK_SIZE 16
%define NODE_SIZE 16

; typedef struct Node {
;   int val             : 4 bytes + (padding = 4 bytes)
;   struct Node *next   : 8 bytes
; } Node;
;
; struct LinkedStack {
;   Node *top           : 8 bytes
;   size_t elements     : 8 bytes
; };

section .text
  extern malloc
  extern free

global linkedstack_create
linkedstack_create: ; () -> RAX: LinkedStack*
  mov rdi, LINKEDSTACK_SIZE
  call malloc wrt ..plt

  cmp rax, NULL
  je .done

  mov qword [rax + LINKEDSTACK_OFFSET_TOP], NULL
  mov qword [rax + LINKEDSTACK_OFFSET_ELEMENTS], 0

  .done:
    ret

node_create: ; (RDI: int val, RSI: Node *next) -> RAX: Node*
  push rdi
  push rsi

  mov rdi, NODE_SIZE
  call malloc wrt ..plt

  pop rsi
  pop rdi

  cmp rax, NULL
  je .done

  mov [rax + NODE_OFFSET_VAL], edi
  mov [rax + NODE_OFFSET_NEXT], rsi

  .done:
    ret

global linkedstack_push
linkedstack_push: ; (RDI: LinkedStack *stack, RSI: int val) -> RAX: bool
  push rdi
  push rsi

  mov rdx, [rdi + LINKEDSTACK_OFFSET_TOP]
  mov rdi, rsi
  mov rsi, rdx

  call node_create

  pop rsi
  pop rdi

  cmp rax, NULL
  jne .insert

  xor rax, rax
  ret

  .insert:
    mov [rdi + LINKEDSTACK_OFFSET_TOP], rax
    inc qword [rdi + LINKEDSTACK_OFFSET_ELEMENTS]

  mov rax, 1
  ret

global linkedstack_pop
linkedstack_pop: ; (RDI: LinkedStack *stack, RSI: int *ret) -> RAX: bool
  cmp qword [rdi + LINKEDSTACK_OFFSET_ELEMENTS], 0
  jne .return_value

  xor rax, rax
  ret

  .return_value:
    cmp rsi, NULL
    je .remove

    mov rdx, [rdi + LINKEDSTACK_OFFSET_TOP]
    mov edx, [rdx + NODE_OFFSET_VAL]
    mov [rsi], edx

  .remove:
    mov rdx, [rdi + LINKEDSTACK_OFFSET_TOP]
    mov rdx, [rdx + NODE_OFFSET_NEXT]

    push rdi
    push rsi
    push rdx

    mov rdi, [rdi + LINKEDSTACK_OFFSET_TOP]
    call free wrt ..plt

    pop rdx
    pop rsi
    pop rdi

    mov [rdi + LINKEDSTACK_OFFSET_TOP], rdx

  mov rax, 1
  ret

global linkedstack_peek
linkedstack_peek: ; (RDI: LinkedStack *stack, RSI: int *ret) -> RAX: bool
  cmp qword [rdi + LINKEDSTACK_OFFSET_ELEMENTS], 0
  jne .get_element

  xor rax, rax
  ret

  .get_element:
    mov rdx, [rdi + LINKEDSTACK_OFFSET_TOP]
    mov edx, [rdx + NODE_OFFSET_VAL]
    mov [rsi], edx

  mov rax, 1
  ret

global linkedstack_equals
linkedstack_equals: ; (RDI: LinkedStack *first, RSI: LinkedStack *second) -> RAX: bool
  xor rax, rax

  mov rcx, [rdi + LINKEDSTACK_OFFSET_ELEMENTS]
  cmp rcx, [rsi + LINKEDSTACK_OFFSET_ELEMENTS]
  jne .done

  mov rdi, [rdi + LINKEDSTACK_OFFSET_TOP]
  mov rsi, [rsi + LINKEDSTACK_OFFSET_TOP]

  mov rax, 1

  .iteration:
    test rcx, rcx
    jz .done

    mov edx, [rdi + NODE_OFFSET_VAL]
    cmp edx, [rsi + NODE_OFFSET_VAL]
    je .next

    xor rax, rax
    jmp .done

  .next:
    dec rcx
    mov rdi, [rdi + NODE_OFFSET_NEXT]
    mov rsi, [rsi + NODE_OFFSET_NEXT]
    jmp .iteration

  .done:
    ret

global linkedstack_foreach
linkedstack_foreach: ; (RDI: LinkedStack *stack, RSI: void (*consumer)(int val))
  mov rdi, [rdi + LINKEDSTACK_OFFSET_TOP]

  .iteration:
    cmp rdi, NULL
    je .done

    push rdi
    push rsi

    mov rdi, [rdi + NODE_OFFSET_VAL]
    call rsi

    pop rsi
    pop rdi

    mov rdi, [rdi + NODE_OFFSET_NEXT]
    jmp .iteration

  .done:
    ret

free_nodes: ; (RDI: Node *node)
  cmp rdi, NULL
  je .done

  push qword [rdi + NODE_OFFSET_NEXT]
  call free wrt ..plt
  pop rdi

  jmp free_nodes

  .done:
    ret

global linkedstack_free
linkedstack_free: ; (RDI: LinkedStack *stack)
  push rdi

  mov rdi, [rdi + LINKEDSTACK_OFFSET_TOP]
  call free_nodes

  pop rdi

  call free wrt ..plt
  ret

global linkedstack_size
linkedstack_size: ; (RDI: LinkedStack *stack) -> RAX: size_t
  mov rax, [rdi + LINKEDSTACK_OFFSET_ELEMENTS]
  ret
