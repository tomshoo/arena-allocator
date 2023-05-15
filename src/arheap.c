#include "arena.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct __ar_heap {
  _Arena**       __heap_ptr;
  unsigned short blocks;
};

struct __ar_heap* __new_ar_heap(unsigned short __blocks, size_t __block_size) {
  struct __ar_heap* __new_heap = malloc(sizeof(struct __ar_heap));
  if (!__new_heap) return NULL;

  __new_heap->blocks = __blocks;

  if (!(__new_heap->__heap_ptr = calloc(__blocks, sizeof(_Arena*)))) {
    free((void*)__new_heap);
    return NULL;
  }

  _Arena** _temp = __new_heap->__heap_ptr;
  while (__blocks--) {
    if ((*(_temp++) = new_arena(__block_size))) continue;

    _temp -= 1;

    do {
      free_arena(*_temp);
      _temp -= 1;
    } while (_temp != __new_heap->__heap_ptr);

    free((void*)__new_heap);
    return NULL;
  }

  return __new_heap;
}

void _ar_free(struct __ar_heap* __ar_heap) {
  while(__ar_heap->blocks--) free_arena(__ar_heap->__heap_ptr[__ar_heap->blocks]);
  free((void*)__ar_heap);
}

void* _ar_alloc(struct __ar_heap* __ar_heap, size_t __size) {
  for (_Arena** aptr = __ar_heap->__heap_ptr; aptr - __ar_heap->__heap_ptr < __ar_heap->blocks; aptr++) {
    void* __alloc;
    if ((__alloc = aalloc(*aptr, __size))) return __alloc;
  }
  return NULL;
}

void _grow_ar_heap(struct __ar_heap* __ar_heap, _Arena* __arena) {
  _Arena** __new_heap_ptr = calloc(__ar_heap->blocks + 1, sizeof(_Arena*));
  if (!__new_heap_ptr) return;

  memcpy(__new_heap_ptr, __ar_heap->__heap_ptr, sizeof(_Arena*) * __ar_heap->blocks);
  __ar_heap->blocks += 1;

  __new_heap_ptr[__ar_heap->blocks - 1] = __arena;
  free(__ar_heap->__heap_ptr);
  __ar_heap->__heap_ptr = __new_heap_ptr;
}

size_t _ar_size(struct __ar_heap* _Nonnull __ar_heap) {
  _Arena**       _arenas = __ar_heap->__heap_ptr;
  unsigned short blocks = __ar_heap->blocks;
  size_t         size = 0;

  while (blocks--) size += __arena_size(*(_arenas++));
  return size;
}
