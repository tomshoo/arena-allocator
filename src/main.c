#define __AR_BLOCK_SIZE 32

#include "arena.h"
#include "arheap.h"

#include <string.h>
#include <stdio.h>

int main(const int, const char*[]) {
  _ArHeap*       _arheap = _new_ar_heap(2);
  unsigned short allocations = 0;

  while (_ar_alloc(_arheap, 8)) allocations += 1;
  printf("Allocations before heap growth: %u\n", allocations);

  _add_block(_arheap);

  while (_ar_alloc(_arheap, 8)) allocations += 1;
  printf("Allocations after heap growth:  %u\n", allocations);

  return 0;
}
