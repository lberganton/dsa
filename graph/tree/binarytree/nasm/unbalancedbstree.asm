%define NULL 0

%define ORDER_PRE   0
%define ORDER_IN    1
%define ORDER_POST  2
%define ORDER_BFS   3

%define UBSTREE_OFFSET_ROOT 0

%define NODE_OFFSET_VAL   0
%define NODE_OFFSET_LEFT  NODE_OFFSET_VAL   + 4
%define NODE_OFFSET_RIGHT NODE_OFFSET_LEFT  + 8

; struct BSTree {
;   Node *root  : 8 bytes
; }
;
; struct Node {
;   int val     : 4 bytes
;   Node *left  : 8 bytes
;   Node *right : 8 bytes
; }

section .text
  extern malloc
  extern free

global ubstree_create
ubstree_create: ; () -> RAX: UBSTree*
  mov rdi, 8
  call malloc wrt ..plt

  cmp rax, NULL
  je .done

  mov qword [rax + UBSTREE_OFFSET_ROOT], NULL

  .done:
    ret

node_alloc: ; (RDI: int val) -> Node*
  push rdi

  mov rdi, 20
  call malloc wrt ..plt

  pop rdi

  cmp rax, NULL
  je .done

  mov [rax + NODE_OFFSET_VAL], edi
  mov qword [rax + NODE_OFFSET_LEFT], NULL
  mov qword [rax + NODE_OFFSET_RIGHT], NULL

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
    call node_alloc
    mov rdi, rax

  .done:
    mov rax, rdi
    ret

global ubstree_insert
ubstree_insert: ; (RDI: UBSTree *bstree, RSI: int val)
  push rdi

  mov rdi, [rdi + UBSTREE_OFFSET_ROOT]
  call insert

  pop rdi

  mov [rdi + UBSTREE_OFFSET_ROOT], rax
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
    mov rax, rdi
    ret

global ubstree_remove
ubstree_remove: ; (RDI: UBSTree *bstree, RSI: int val)
  push rdi

  mov rdi, [rdi + UBSTREE_OFFSET_ROOT]
  call remove

  pop rdi

  mov [rdi + UBSTREE_OFFSET_ROOT], rax
  ret

search: ; (RDI: Node *node, RSI: int val) -> RAX: bool
  cmp rdi, NULL
  jne .check

  xor rax, rax
  jmp .done

  .check:
    cmp esi, [rdi + NODE_OFFSET_VAL]
    jl .left
    jg .right

    mov rax, 1
    jmp .done

  .left:
    mov rdi, [rdi + NODE_OFFSET_LEFT]
    call search
    jmp .done

  .right:
    mov rdi, [rdi + NODE_OFFSET_RIGHT]
    call search
    jmp .done

  .done:
    ret

global ubstree_search
ubstree_search: ; (RDI: UBSTree *bstree, RSI: int val) -> RAX: bool
  mov rdi, [rdi + UBSTREE_OFFSET_ROOT]
  call search
  ret

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

    call free wrt ..plt
    ret

global ubstree_free
ubstree_free: ; (RDI: UBSTree *bstree, RSI: int val)
  push rdi

  mov rdi, [rdi + UBSTREE_OFFSET_ROOT]
  call node_free

  pop rdi

  call free wrt ..plt
  ret

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

    push rdi
    push rsi

    mov rdi, [rdi + NODE_OFFSET_RIGHT]
    call pre_order

    pop rsi
    pop rdi

    ret

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

    push rdi
    push rsi

    mov rdi, [rdi + NODE_OFFSET_RIGHT]
    call in_order

    pop rsi
    pop rdi

    ret

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

    push rdi
    push rsi

    mov edi, [rdi + NODE_OFFSET_VAL]
    call rsi

    pop rsi
    pop rdi

    ret

global ubstree_traversal
ubstree_traversal: ; (RDI: UBSTree *bstree, RSI: Order order, RDX: (*consumer)(RDI: int val))
  cmp rsi, ORDER_PRE
  je .pre

  cmp rsi, ORDER_IN
  je .in

  cmp rsi, ORDER_POST
  je .post

  ret

  .pre:
    mov rax, pre_order
    jmp .traversal
  .in:
    mov rax, in_order
    jmp .traversal
  .post:
    mov rax, post_order
    jmp .traversal

  .traversal:
    mov rdi, [rdi + UBSTREE_OFFSET_ROOT]
    mov rsi, rdx
    call rax

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
  call nodes

  .done:
    ret

global ubstree_nodes
ubstree_nodes: ; (RDI: UBSTree *bstree) -> size_t
  xor rax, rax
  mov rdi, [rdi + UBSTREE_OFFSET_ROOT]
  call nodes
  ret

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

  pop rdx

  cmp rdx, rax
  cmovg rax, rdx

  .done:
    mov rax, rsi
    ret

global ubstree_levels
ubstree_levels: ; (RDI: UBSTree *bstree) -> size_t
  mov rdi, [rdi + UBSTREE_OFFSET_ROOT]
  xor rsi, rsi
  call levels
  ret
