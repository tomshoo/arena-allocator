#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct __arena {
  void* _Nonnull __base_ptr;
  size_t         size;
  size_t         allocated;
} _Arena;

struct __arena* _Nullable new_arena(size_t __size) {
  _Arena* __new_arena = malloc(sizeof(struct __arena));

  if (!__new_arena) return NULL;

  __new_arena->__base_ptr = malloc(__size);
  __new_arena->size       = __size;
  __new_arena->allocated  = 0;

  if (!__new_arena->__base_ptr) {
    free((void*)__new_arena);
    return NULL;
  }

  return __new_arena;
}

void free_arena(struct __arena* _Nonnull __arena) {
  free(__arena->__base_ptr);
  free((void*)__arena);
}

size_t __arena_size(struct __arena* _Nonnull __arena) {
  return __arena->size;
}

void* aalloc(struct __arena* _Nonnull __arena, size_t __alloc_size) {
  if (__arena->allocated + __alloc_size > __arena->size) return NULL;

  __arena->allocated += __alloc_size;
  return __arena->__base_ptr + (__arena->allocated - __alloc_size);
}
