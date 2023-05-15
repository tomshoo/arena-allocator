#ifndef __I_ARENA_HH_
#define __I_ARENA_HH_

#include <stddef.h>

typedef struct __arena _Arena;

/*!
 * @brief allocate a new arena
 *
 * @param[in] `__size` size of arena to allocate
 *
 * @param[out] `_Arena*` pointer to a new arena, can
 *                       be null if the backing `malloc(size_t)` fails.
 */
extern struct __arena* _Nullable new_arena(size_t);

/*!
 * @brief free all memory held by a given arena.
 *
 * @param[in] `__arena` pointer to an arena.
 */
extern void free_arena(struct __arena* _Nonnull);

/*!
 * @brief allocate memory inside an arena
 *
 * @param[in] `__arena` pointer to an arena to allocate on.
 * @param[in] `__size`  number of bytes to allocate on the arena.
 *
 * @param[out] `void*` pointer to a location on the arena
 *                     corresponding to the size allocated.
 * 
 * @section NOTE
 * It may return a `NULL` pointer in case the requested memory
 * size could not fit onto the arena buffer.
 * @section END
 */
extern void* _Nullable aalloc(struct __arena* _Nonnull, size_t);

/*!
 * @brief get the size aquired by an arena.
 *
 * @param[in] `__arena` pointer to an arena.
 *
 * @param[out] `size_t` size allocate by the arena in bytes.
 */
extern size_t __arena_size(struct __arena* _Nonnull);

#endif
