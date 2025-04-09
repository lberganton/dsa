#include "list.h"
#include <stdlib.h>

#define INSERTION_SORT_MIN 16
#define FILTER_INPLACE 16

struct ArrayList {
  int *array;
  size_t allocated;
  size_t elements;
};

ArrayList* arraylist_create(size_t initial_capacity) {
  ArrayList *new = (ArrayList*) malloc(sizeof(ArrayList));
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

static bool increase(ArrayList *list) {
  int *new = (int*) realloc(list->array, list->allocated * 2 * sizeof(int));
  if (new == NULL) {
    return false;
  }

  list->array = new;
  list->allocated *= 2;

  return true;
}

bool arraylist_insert(ArrayList *list, size_t index, int val) {
  if (index > list->elements) {
    return false;
  }

  if (list->elements == list->allocated && !increase(list)) {
    return false;
  }

  for (size_t i = list->elements; i > index; i--) {
    list->array[i] = list->array[i - 1];
  }

  list->array[index] = val;
  list->elements++;

  return true;
}

bool arraylist_pushleft(ArrayList *list, int val) {
  return arraylist_insert(list, 0, val);
}

bool arraylist_pushright(ArrayList *list, int val) {
  return arraylist_insert(list, list->elements, val);
}

bool arraylist_remove(ArrayList *list, size_t index, int *ret) {
  if (index >= list->elements) {
    return false;
  }

  if (ret != NULL) {
    *ret = list->array[index];
  }

  for (size_t i = index + 1; i < list->elements; i++) {
    list->array[i - 1] = list->array[i];
  }

  list->elements--;

  return true;
}

bool arraylist_popleft(ArrayList *list, int *ret) {
  return arraylist_remove(list, 0, ret);
}

bool arraylist_popright(ArrayList *list, int *ret) {
  return list->elements > 0 && arraylist_remove(list, list->elements - 1, ret);
}

bool arraylist_set(ArrayList *list, size_t index, int val) {
  if (index >= list->elements) {
    return false;
  }
  list->array[index] = val;
  return true;
}

bool arraylist_get(ArrayList *list, size_t index, int *ret) {
  if (index >= list->elements) {
    return false;
  }
  *ret = list->array[index];
  return true;
}

bool arraylist_max(ArrayList *list, int *ret) {
  for (size_t i = 0; i < list->elements; i++) {
    if (i == 0 || list->array[i] > *ret) {
      *ret = list->array[i];
    }
  }
  return list->elements != 0;
}

bool arraylist_min(ArrayList *list, int *ret) {
  for (size_t i = 0; i < list->elements; i++) {
    if (i == 0 || list->array[i] < *ret) {
      *ret = list->array[i];
    }
  }
  return list->elements != 0;
}

bool arraylist_equals(ArrayList *first, ArrayList *second) {
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

bool arraylist_reduce(ArrayList *list, int indentity, int (*function)(int val1, int val2), int *ret) {
  if (list->elements == 0) {
    return false;
  }

  *ret = indentity;
  for (size_t i = 0; i < list->elements; i++) {
    *ret = function(*ret, list->array[i]);
  }

  return true;
}

bool arraylist_anymatch(ArrayList *list, bool (*predicate)(int val)) {
  for (size_t i = 0; i < list->elements; i++) {
    if (predicate(list->array[i])) {
      return true;
    }
  }
  return false;
}

bool arraylist_allmatch(ArrayList *list, bool (*predicate)(int val)) {
  for (size_t i = 0; i < list->elements; i++) {
    if (!predicate(list->array[i])) {
      return false;
    }
  }
  return true;
}

static void filter_inplace(ArrayList *list, bool (*predicate)(int val)) {
  for (size_t i = 0; i < list->elements; i++) {
    if (!predicate(list->array[i])) {
      arraylist_remove(list, i, NULL);
    }
  }
}

static void filter_outofplace(ArrayList *list, bool (*predicate)(int val)) {
  int *new = (int*) malloc(list->allocated * sizeof(int));
  if (new == NULL) {
    filter_inplace(list, predicate);
    return;
  }

  size_t elements = 0;

  for (size_t i = 0; i < list->elements; i++) {
    if (predicate(list->array[i])) {
      new[elements] = list->array[i];
      elements++;
    }
  }

  free(list->array);

  list->array = new;
  list->elements = elements;
}

void arraylist_filter(ArrayList *list, bool (*predicate)(int val)) {
  (list->elements <= FILTER_INPLACE ? filter_inplace : filter_outofplace)(list, predicate);
}

void arraylist_map(ArrayList *list, int (*function)(int val)) {
  for (size_t i = 0; i < list->elements; i++) {
    list->array[i] = function(list->array[i]);
  }
}

void arraylist_foreach(ArrayList *list, void (*consumer)(int val)) {
  for (size_t i = 0; i < list->elements; i++) {
    consumer(list->array[i]);
  }
}

static void insertionsort(int *array, size_t length) {
  for (size_t i = 1; i < length; i++) {
    for (size_t j = i; j > 0 && array[j] < array[j - 1]; j--) {
      swap(&array[j], &array[j - 1]);
    }
  }
}

static void siftdown(int *array, size_t length, size_t i) {
  size_t major = i;
  size_t left = 2 * i + 1;
  size_t right = 2 * i + 2;

  if (left < length && array[left] > array[major]) {
    major = left;
  }

  if (right < length && array[right] > array[major]) {
    major = right;
  }

  if (i != major) {
    swap(&array[i], &array[major]);
    siftdown(array, length, major);
  }
}

static void heapsort(int *array, size_t length) {
  for (size_t i = length / 2; i > 0; i--) {
    siftdown(array, length, i - 1);
  }

  while (length > 0) {
    length--;
    swap(&array[0], &array[length]);
    siftdown(array, length, 0);
  }
}

static size_t quicksort(int *array, size_t low, size_t high) {
  int pivot = array[high];
  size_t pos = low;

  for (size_t i = 0; i < high; i++) {
    if (array[i] < pivot) {
      swap(&array[i], &array[pos]);
      pos++;
    }
  }

  swap(&array[pos], &array[high]);
  return pos;
}

static void introsort(int *array, size_t length, size_t level) {
  if (length <= INSERTION_SORT_MIN) {
    insertionsort(array, length);
  }
  else if (level == 0) {
    heapsort(array, length);
  }
  else {
    size_t pivot = quicksort(array, 0, length - 1);

    if (pivot > 0) {
      introsort(array, pivot, level - 1);
    }
    introsort(&array[pivot + 1], length - pivot - 1, level - 1);
  }
}

static size_t log2int(size_t val) {
  size_t log = 0;
  while (val > 1) {
    val >>= 1;
    log++;
  }
  return log;
}

void arraylist_sort(ArrayList *list) {
  introsort(list->array, list->elements, log2int(list->elements));
}

void arraylist_reverse(ArrayList *list) {
  if (list->elements <= 1) {
    return;
  }

  for (size_t i = 0; i < list->elements / 2; i++) {
    swap(&list->array[i], &list->array[list->elements - i - 1]);
  }
}

void arraylist_free(ArrayList *list) {
  free(list->array);
  free(list);
}

size_t arraylist_findfirst(ArrayList *list, int val, size_t start, size_t end) {
  if (start > end || end >= list->elements) {
    return 0;
  }

  for (; start <= end; start++) {
    if (val == list->array[start]) {
      return start + 1;
    }
  }

  return 0;
}

size_t arraylist_findlast(ArrayList *list, int val, size_t start, size_t end) {
  if (start > end || end >= list->elements) {
    return 0;
  }

  for (; end >= start; end--) {
    if (val == list->array[end]) {
      return end + 1;
    }
  }

  return 0;
}

size_t arraylist_size(ArrayList *list) {
  return list->elements;
}
