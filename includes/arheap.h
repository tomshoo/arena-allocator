#ifndef __I_AR_HEAP_H_
#define __I_AR_HEAP_H_

#include "arena.h"
#include <stddef.h>

#ifndef __AR_BLOCK_SIZE
#define __AR_BLOCK_SIZE 256
#endif

typedef struct __ar_heap _ArHeap;

extern _ArHeap* _Nullable __new_ar_heap(unsigned short, size_t);
extern void               _ar_free(struct __ar_heap* _Nonnull);
extern void*    _Nullable _ar_alloc(struct __ar_heap* _Nonnull, size_t);
extern size_t             _ar_size(struct __ar_heap* _Nonnull);
extern void               _grow_ar_heap(struct __ar_heap* _Nonnull, _Arena* _Nonnull);

#define _new_ar_heap(__block)             \
  __new_ar_heap(__block, __AR_BLOCK_SIZE)

#define _add_block(__ar_heap)                    \
  do {                                           \
    _Arena* _arena = new_arena(__AR_BLOCK_SIZE); \
    if (!_arena) break;                          \
    _grow_ar_heap(__ar_heap, _arena);            \
  } while(0)

#endif
