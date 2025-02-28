%define NULL 0

%define ORDER_PRE   0
%define ORDER_IN    1
%define ORDER_POST  2
%define ORDER_BFS   3

%define AVL_OFFSET_ROOT 0

%define NODE_OFFSET_VAL     0
%define NODE_OFFSET_LEFT    NODE_OFFSET_VAL   + 8
%define NODE_OFFSET_RIGHT   NODE_OFFSET_LEFT  + 8
%define NODE_OFFSET_HEIGHT  NODE_OFFSET_RIGHT + 8

%define AVL_SIZE 8
%define NODE_SIZE 32

%define QLEN 1024

; struct AVL {
;   Node *root  : 8 bytes
; }
;
; struct Node {
;   int val       : 4 bytes + (padding = 4 bytes)
;   Node *left    : 8 bytes
;   Node *right   : 8 bytes
;   size_t height : 8 bytes
; }

section .text
  extern malloc
  extern free

global avl_create
avl_create: ; () -> RAX: UBSTree*
  mov rdi, AVL_SIZE
  call malloc wrt ..plt

  cmp rax, NULL
  je .done

  mov qword [rax + AVL_OFFSET_ROOT], NULL

  .done:
    ret

height: ; (RDI: Node *node) -> size_t
  xor rax, rax

  cmp rdi, NULL
  jne .left
  ret

  .left:
    cmp qword [rdi + NODE_OFFSET_LEFT], NULL
    je .right

    mov rsi, [rdi + NODE_OFFSET_LEFT]
    mov rax, [rsi + NODE_OFFSET_HEIGHT]

  .right:
    cmp qword [rdi + NODE_OFFSET_RIGHT], NULL
    je .done

    mov rsi, [rdi + NODE_OFFSET_RIGHT]
    cmp [rsi + NODE_OFFSET_HEIGHT], rax
    cmovg rax, [rsi + NODE_OFFSET_HEIGHT]

  .done:
    inc rax
    ret

LL: ; (RDI: Node *node) -> Node*
  mov rsi, [rdi + NODE_OFFSET_RIGHT]

  mov rax, [rsi + NODE_OFFSET_LEFT]
  mov [rdi + NODE_OFFSET_RIGHT], rax
  mov [rsi + NODE_OFFSET_LEFT], rdi

  push rsi
  push rdi
  call height
  pop rdi

  mov [rdi + NODE_OFFSET_HEIGHT], rax
  pop rax
  ret

RR: ; (RDI: Node *node) -> Node*
  mov rsi, [rdi + NODE_OFFSET_LEFT]

  mov rax, [rsi + NODE_OFFSET_RIGHT]
  mov [rdi + NODE_OFFSET_LEFT], rax
  mov [rsi + NODE_OFFSET_RIGHT], rdi

  push rsi
  push rdi
  call height
  pop rdi

  mov [rdi + NODE_OFFSET_HEIGHT], rax
  pop rax
  ret

balance_factor: ; (RDI: Node *node) -> int
  push rdi
  mov rdi, [rdi + NODE_OFFSET_LEFT]
  call height
  pop rdi

  push rax
  mov rdi, [rdi + NODE_OFFSET_RIGHT]
  call height

  mov rdi, rax
  pop rax

  sub rax, rdi
  ret

balance: ; (RDI: Node *node) -> Node*
  cmp rdi, NULL
  jne .left

  mov rax, NULL
  ret

  .left:
    push rdi
    call balance_factor
    pop rdi

    cmp rax, 1
    jng .right

    push rdi
    mov rdi, [rdi + NODE_OFFSET_LEFT]
    call balance_factor
    pop rdi

    cmp rax, 0
    jnl .not_RL

    push rdi
    mov rdi, [rdi + NODE_OFFSET_LEFT]
    call LL
    pop rdi
    mov [rdi + NODE_OFFSET_LEFT], rax

    .not_RL:
      call RR
      mov rdi, rax

    jmp .height

  .right:
    push rdi
    call balance_factor
    pop rdi

    cmp rax, -1
    jnl .done

    push rdi
    mov rdi, [rdi + NODE_OFFSET_RIGHT]
    call balance_factor
    pop rdi

    cmp rax, 0
    jng .not_LR

    push rdi
    mov rdi, [rdi + NODE_OFFSET_RIGHT]
    call RR
    pop rdi
    mov [rdi + NODE_OFFSET_RIGHT], rax

    .not_LR:
      call LL
      mov rdi, rax

    jmp .height

  .height:
    push rdi
    call height
    pop rdi
    mov [rdi + NODE_OFFSET_HEIGHT], rax

  .done:
    mov rax, rdi
    ret

node_alloc: ; (RDI: int val) -> Node*
  push rdi

  mov rdi, NODE_SIZE
  call malloc wrt ..plt

  pop rdi

  cmp rax, NULL
  je .done

  mov [rax + NODE_OFFSET_VAL], edi
  mov qword [rax + NODE_OFFSET_LEFT], NULL
  mov qword [rax + NODE_OFFSET_RIGHT], NULL
  mov qword [rax + NODE_OFFSET_HEIGHT], 1

  .done:
    ret

insert: ; (RDI: Node *node, RSI: int val) -> Node*
  cmp rdi, NULL
  je .alloc

  cmp esi, [rdi + NODE_OFFSET_VAL]
  jl .left
  jg .right

  jmp .done

  .left:
    push rdi

    mov rdi, [rdi + NODE_OFFSET_LEFT]
    call insert

    pop rdi

    mov [rdi + NODE_OFFSET_LEFT], rax
    jmp .done

  .right:
    push rdi

    mov rdi, [rdi + NODE_OFFSET_RIGHT]
    call insert

    pop rdi

    mov [rdi + NODE_OFFSET_RIGHT], rax
    jmp .done

  .alloc:
    mov rdi, rsi
    jmp node_alloc
    mov rdi, rax

  .done:
    call balance
    ret

global avl_insert
avl_insert: ; (RDI: UBSTree *bstree, RSI: int val)
  push rdi

  mov rdi, [rdi + AVL_OFFSET_ROOT]
  call insert

  pop rdi
  mov [rdi + AVL_OFFSET_ROOT], rax

  ret

remove: ; (RDI: Node *node, RSI: int val) -> Node*
  cmp rdi, NULL
  je .done

  cmp esi, [rdi + NODE_OFFSET_VAL]
  jl .less
  jg .greater

  jmp .null_left

  .less:
    push rdi

    mov rdi, [rdi + NODE_OFFSET_LEFT]
    call remove

    pop rdi

    mov [rdi + NODE_OFFSET_LEFT], rax
    jmp .done

  .greater:
    push rdi

    mov rdi, [rdi + NODE_OFFSET_RIGHT]
    call remove

    pop rdi

    mov [rdi + NODE_OFFSET_RIGHT], rax
    jmp .done

  .null_left:
    cmp qword [rdi + NODE_OFFSET_LEFT], NULL
    jne .null_right

    push qword [rdi + NODE_OFFSET_RIGHT]
    call free wrt ..plt
    pop rdi

    jmp .done

  .null_right:
    cmp qword [rdi + NODE_OFFSET_RIGHT], NULL
    jne .get_node

    push qword [rdi + NODE_OFFSET_LEFT]
    call free wrt ..plt
    pop rdi

    jmp .done

  .get_node:
    mov rsi, [rdi + NODE_OFFSET_LEFT]

    .while:
      cmp qword [rsi + NODE_OFFSET_RIGHT], NULL
      je .swap
      mov rsi, [rsi + NODE_OFFSET_RIGHT]
      jmp .while

  .swap:
    mov rax, [rsi + NODE_OFFSET_VAL]
    mov [rdi + NODE_OFFSET_VAL], rax

    push rdi

    mov rdi, [rdi + NODE_OFFSET_LEFT]
    mov rsi, rax

    call remove

    pop rdi
    mov [rdi + NODE_OFFSET_LEFT], rax

  .done:
    call balance
    ret

global avl_remove
avl_remove: ; (RDI: UBSTree *bstree, RSI: int val)
  push rdi

  mov rdi, [rdi + AVL_OFFSET_ROOT]
  call remove

  pop rdi
  mov [rdi + AVL_OFFSET_ROOT], rax

  ret

search: ; (RDI: Node *node, RSI: int val) -> RAX: bool
  cmp rdi, NULL
  jne .check

  xor rax, rax
  ret

  .check:
    cmp esi, [rdi + NODE_OFFSET_VAL]
    jl .left
    jg .right

    mov rax, 1
    ret

  .left:
    mov rdi, [rdi + NODE_OFFSET_LEFT]
    jmp search

  .right:
    mov rdi, [rdi + NODE_OFFSET_RIGHT]
    jmp search

global avl_search
avl_search: ; (RDI: UBSTree *bstree, RSI: int val) -> RAX: bool
  mov rdi, [rdi + AVL_OFFSET_ROOT]
  jmp search

node_free: ; (RDI: Node *node)
  cmp rdi, NULL
  jne .recursion
  ret

  .recursion:
    push rdi
    mov rdi, [rdi + NODE_OFFSET_LEFT]
    call node_free
    pop rdi

    push rdi

    mov rdi, [rdi + NODE_OFFSET_RIGHT]
    call node_free

    pop rdi
    jmp free wrt ..plt

global avl_free
avl_free: ; (RDI: UBSTree *bstree, RSI: int val)
  push rdi

  mov rdi, [rdi + AVL_OFFSET_ROOT]
  call node_free

  pop rdi
  jmp free wrt ..plt

pre_order: ; (RDI: Node *node, RSI: (*consumer)(RDI: int val))
  cmp rdi, NULL
  jne .recursion
  ret

  .recursion:
    push rdi
    push rsi

    mov edi, [rdi + NODE_OFFSET_VAL]
    call rsi

    pop rsi
    pop rdi

    push rdi
    push rsi

    mov rdi, [rdi + NODE_OFFSET_LEFT]
    call pre_order

    pop rsi
    pop rdi

    mov rdi, [rdi + NODE_OFFSET_RIGHT]
    jmp pre_order

in_order: ; (RDI: Node *node, RSI: (*consumer)(RDI: int val))
  cmp rdi, NULL
  jne .recursion
  ret

  .recursion:
    push rdi
    push rsi

    mov rdi, [rdi + NODE_OFFSET_LEFT]
    call in_order

    pop rsi
    pop rdi

    push rdi
    push rsi

    mov edi, [rdi + NODE_OFFSET_VAL]
    call rsi

    pop rsi
    pop rdi

    mov rdi, [rdi + NODE_OFFSET_RIGHT]
    jmp in_order

post_order: ; (RDI: Node *node, RSI: (*consumer)(RDI: int val))
  cmp rdi, NULL
  jne .recursion
  ret

  .recursion:
    push rdi
    push rsi

    mov rdi, [rdi + NODE_OFFSET_LEFT]
    call post_order

    pop rsi
    pop rdi

    push rdi
    push rsi

    mov rdi, [rdi + NODE_OFFSET_RIGHT]
    call in_order

    pop rsi
    pop rdi

    mov edi, [rdi + NODE_OFFSET_VAL]
    jmp rsi

bfs: ; (RDI: Node *node, RSI: (*consumer)(RDI: int val))
  push rbx

  sub rsp, QLEN * 8
  xor rbx, rbx
  mov rcx, 1
  mov [rsp], rdi

  cmp rdi, NULL
  je .done

  .iteration:
    test rcx, rcx
    jz .done

    mov rdi, [rsp + rbx * 8]
    dec rcx

    push rbx
    push rcx
    push rdi
    push rsi

    mov edi, [rdi + NODE_OFFSET_VAL]
    call rsi

    pop rsi
    pop rdi
    pop rcx
    pop rbx

    cmp rcx, QLEN
    jge .next

    cmp qword [rdi + NODE_OFFSET_LEFT], NULL
    je .right

    lea rdx, [rbx + rcx + 1]
    and rdx, (QLEN >> 1) - 1

    mov rax, [rdi + NODE_OFFSET_LEFT]
    mov [rsp + rdx * 8], rax
    inc rcx

    .right:
      cmp rcx, QLEN
      jge .next

      cmp qword [rdi + NODE_OFFSET_RIGHT], NULL
      je .next

      lea rdx, [rbx + rcx + 1]
      and rdx, (QLEN >> 1) - 1

      mov rax, [rdi + NODE_OFFSET_RIGHT]
      mov [rsp + rdx * 8], rax
      inc rcx

    .next:
      inc rbx
      and rbx, (QLEN >> 1) - 1
      jmp .iteration

  .done:
    add rsp, QLEN * 8
    pop rbx
    ret

global avl_traversal
avl_traversal: ; (RDI: UBSTree *bstree, RSI: Order order, RDX: (*consumer)(RDI: int val))
  mov rax, rsi
  mov rsi, rdx
  mov rdi, [rdi + AVL_OFFSET_ROOT]

  cmp rax, ORDER_PRE
  je pre_order

  cmp rax, ORDER_IN
  je in_order

  cmp rax, ORDER_POST
  je post_order

  cmp rax, ORDER_BFS
  je bfs

  ret

nodes: ; (RDI: Node *node) -> size_t
  cmp rdi, NULL
  je .done

  inc rax

  push rdi
  mov rdi, [rdi + NODE_OFFSET_LEFT]
  call nodes
  pop rdi

  mov rdi, [rdi + NODE_OFFSET_RIGHT]
  jmp nodes

  .done:
    ret

global avl_nodes
avl_nodes: ; (RDI: UBSTree *bstree) -> size_t
  xor rax, rax
  mov rdi, [rdi + AVL_OFFSET_ROOT]
  jmp nodes

levels: ; (RDI: Node *node, RSI: size_t level) -> size_t
  cmp rdi, NULL
  je .done

  inc rsi

  push rdi
  push rsi

  mov rdi, [rdi + NODE_OFFSET_LEFT]
  call levels

  pop rsi
  pop rdi

  push rax

  mov rdi, [rdi + NODE_OFFSET_RIGHT]
  call levels

  pop rsi

  cmp rax, rsi
  cmovg rsi, rax

  .done:
    mov rax, rsi
    ret

global avl_levels
avl_levels: ; (RDI: UBSTree *bstree) -> size_t
  mov rdi, [rdi + AVL_OFFSET_ROOT]
  xor rsi, rsi
  jmp levels
