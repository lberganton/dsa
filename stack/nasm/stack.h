#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

typedef struct ArrayStack ArrayStack;

ArrayStack*   arraystack_create(size_t initial_capacity);
bool          arraystack_push(ArrayStack *stack, int val);
bool          arraystack_pop(ArrayStack *stack, int *ret);
bool          arraystack_peek(ArrayStack* stack, int *ret);
bool          arraystack_equals(ArrayStack *first, ArrayStack *second);
void          arraystack_foreach(ArrayStack *stack, void (*consumer)(int val));
void          arraystack_free(ArrayStack *stack);
size_t        arraystack_size(ArrayStack *stack);

#endif
