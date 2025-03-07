#include "stack.h"
#include <stdlib.h>

struct ArrayStack {
  int *array;
  size_t allocated;
  size_t elements;
};

ArrayStack* arraystack_create(size_t initial_capacity) {
  ArrayStack *new = (ArrayStack*) malloc(sizeof(ArrayStack));
  if (new == NULL) {
    return NULL;
  }

  new->allocated = initial_capacity != 0 ? initial_capacity : 16;
  new->elements = 0;

  new->array = (int*) malloc(new->allocated * sizeof(int));
  if (new->array == NULL) {
    free(new);
    return NULL;
  }

  return new;
}

static bool increase(ArrayStack *stack) {
  int *new = (int*) realloc(stack->array, stack->allocated * 2);
  if (new == NULL) {
    return false;
  }

  stack->array = new;
  stack->allocated *= 2;

  return true;
}

bool arraystack_push(ArrayStack *stack, int val) {
  if (stack->elements == stack->allocated && !increase(stack)) {
    return false;
  }
  stack->array[stack->elements++] = val;
  return true;
}

bool arraystack_pop(ArrayStack *stack, int *ret) {
  if (stack->elements == 0) {
    return false;
  }
  stack->elements--;
  if (ret != NULL) {
    *ret = stack->array[stack->elements];
  }
  return true;
}

bool arraystack_peek(ArrayStack* stack, int *ret) {
  if (stack->elements == 0) {
    return false;
  }
  *ret = stack->array[stack->elements - 1];
  return true;
}

bool arraystack_equals(ArrayStack *first, ArrayStack *second) {
  if (first->elements != second->elements) {
    return false;
  }

  for (size_t i = 0; i < first->elements; i++) {
    if (first->array[i] != second->array[i]) {
      return false;
    }
  }

  return true;
}

void arraystack_foreach(ArrayStack *stack, void (*consumer)(int val)) {
  for (size_t i = stack->elements; i > 0; i--) {
    consumer(stack->array[i - 1]);
  }
}

void arraystack_free(ArrayStack *stack) {
  free(stack->array);
  free(stack);
}

size_t arraystack_size(ArrayStack *stack) {
  return stack->elements;
}
