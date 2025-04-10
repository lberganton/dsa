#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

typedef struct ArrayStack ArrayStack;
typedef struct LinkedStack LinkedStack;

ArrayStack*   arraystack_create(size_t initial_capacity);
bool          arraystack_push(ArrayStack *stack, int val);
bool          arraystack_pop(ArrayStack *stack, int *ret);
bool          arraystack_peek(ArrayStack* stack, int *ret);
bool          arraystack_equals(ArrayStack *first, ArrayStack *second);
void          arraystack_foreach(ArrayStack *stack, void (*consumer)(int val));
void          arraystack_free(ArrayStack *stack);
size_t        arraystack_size(ArrayStack *stack);

LinkedStack*  linkedstack_create(void);
bool          linkedstack_push(LinkedStack *stack, int val);
bool          linkedstack_pop(LinkedStack *stack, int *ret);
bool          linkedstack_peek(LinkedStack* stack, int *ret);
bool          linkedstack_equals(LinkedStack *first, LinkedStack *second);
void          linkedstack_foreach(LinkedStack *stack, void (*consumer)(int val));
void          linkedstack_free(LinkedStack *stack);
size_t        linkedstack_size(LinkedStack *stack);

#endif
