/*
 * NOTE: this is the wild west, theres little to non out of mem, stack and 
 *       thread safety here ;P
 *
 * NOTE: all the code here IS NOT TESTED, good luck ( OwO)b
 */

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define LINEAR      1
#define ARENA       2
#define PAGE        3
#ifndef __ALLOC_STYLE
  #define __ALLOC_STYLE ARENA
#endif // !__ALLOC_STYLE

#if (__ALLOC_STYLE == LINEAR)
  #define __ALLOC_STYLE_LINEAR
#elif __ALLOC_STYLE == ARENA
  #define __ALLOC_STYLE_ARENA
#elif (__ALLOC_STYLE == PAGE)
  #define __ALLOC_STYLE_PAGE
// #elif __ALLOC_STYLE == X
//   #define __ALLOC_STYLE_X
#else
  #error "Unsupported __ALLOC_STYLE specified!"
#endif

extern void  free(void* ptr);
extern void* malloc(size_t size);
extern void* calloc(size_t nitems, size_t size);
extern void* realloc(void* ptr, size_t size);

#define UNUSED(var) ((void)var)

/*
 * NOTE: our stack (grows down) starts at 0x90000, and our kernel code 0x1000
 */
#define HEAP_BASE_ADDR      0x10000
// TODO: change this hardcode stuff
#define STACK_BASE_ADDR     0x90000
#define PAGE_SIZE           0x1000

///////////////////////////////////////////////////////////////////////////////
#if defined(__ALLOC_STYLE_LINEAR)
/*
 * def: increase the free_mem_addr linearly & never look back (no need for free,
 *      realloc always needs new mem). Fast & simple stuff.
 *
 *      max_malloc_size is limited to 'STACK_BASE_ADDR - HEAP_BASE_ADDR' but
 *      don't do that ._.
 */
static uint32_t free_mem_addr = HEAP_BASE_ADDR;

#define __no_free
#define __no_calloc
#define __no_realloc

void* malloc(size_t size) {
    /* blocks aligned to 4B, or 0x04*/
    if ( size & 0X03 ) {
        size = (size + 0x03) & ~0x03;
    }
    /* check if we overflow page, pages are aligned to 4KB, or 0x1000 */
    if ( (free_mem_addr & 0X0fff) + size > 0x1000 ) {
        free_mem_addr = (free_mem_addr + 0x0fff) & ~0x0fff;
    }
    uint32_t addr = free_mem_addr;
    free_mem_addr += size;

    return (void*)addr;
}

#elif defined(__ALLOC_STYLE_ARENA)
/*
 * def: get a page of mem for each alloc (realloc included), free_mem_addr
 *      increases linearly, never look back (no need for free, realloc always
 *      needs new mem), fast & simple stuff.
 *
 *      limits our max_malloc_size to ARENA_SIZE.
 */
#define __no_calloc
#define __no_realloc

#define ARENA_SIZE  (PAGE_SIZE / 2)
#define ARENA_NUMS  ((STACK_BASE_ADDR - HEAP_BASE_ADDR) / ARENA_SIZE)

static volatile struct {
    uint16_t elements;
    uint16_t pos;
} arena_table[ARENA_NUMS] = {0};

// if ptr isn't pointing to an arena base it's undefined territory
void  free(void* ptr) {
    if ( ptr == NULL ) { return; }
    uint16_t indx = (((uint32_t)ptr) - HEAP_BASE_ADDR) / ARENA_SIZE;
    if ( arena_table[indx].elements <= 0 ) {
        // TODO: STDERR 'double' free
        return;
    }
    if ( --arena_table[indx].elements == 0 ) { arena_table[indx].pos = 0; }
}
void* malloc(size_t size) {
    /* blocks aligned to 4B, or 0x04*/
    if ( size & 0X03 ) { size = (size + 0x03) & ~0x03; }

    /* find suitable arena */
    for ( uint32_t i = 0; i < ARENA_NUMS; i++ ) {
        if ( arena_table[i].pos + size >= ARENA_SIZE ) { continue; }

        uint32_t ptr = arena_table[i].pos + i * ARENA_SIZE + HEAP_BASE_ADDR;
        arena_table[i].pos += size;
        arena_table[i].elements++;
        return (void*)ptr;
    } return NULL;
}

#elif defined(__ALLOC_STYLE_PAGE)
/*
 * def: get a page of mem for each alloc (realloc included), free_mem_addr
 *      increases linearly, never look back (no need for free, realloc always
 *      needs new mem), fast & simple stuff.
 *
 *      you must manage your all given pages, max_malloc_size is a page size,
 *      overflowing a page will have undefined behaviour.
 */

#define __no_free
#define __no_calloc
#define __no_realloc

#define PAGE_NUMS  ((STACK_BASE_ADDR - HEAP_BASE_ADDR) / PAGE_SIZE)

static uint32_t free_mem_addr = HEAP_BASE_ADDR;

/* Pages are aligned to 4KB, or 0x1000 */
void* malloc(size_t size) {
    UNUSED(size);
    if ( free_mem_addr >= STACK_BASE_ADDR ) { return NULL; }
    uint32_t addr = free_mem_addr;
    free_mem_addr += 0x1000;
    return (void*)addr;
}

// #elif defined(__ALLOC_STYLE_X)
// void  free(void* ptr);
// void* malloc(size_t size);
// void* calloc(size_t nitems, size_t size);
// void* realloc(void* ptr, size_t size);
#endif // !__ALLOC_STYLE_X

#ifdef __no_free
void  free(void* ptr) { UNUSED(ptr); }
#endif // !__free

#ifdef __no_realloc
/* (ptr == NULL) is undefined behaviour.
 * orig_ptr size > new_ptr size is not taken to account */
void* realloc(void* ptr, size_t size) {
    void* dest = malloc(size);

    if ( ptr == NULL ) { return dest; }
    if ( dest ) { memcpy(dest, ptr, size); }
    free(ptr);

    return dest;
}
#endif // !__no_realloc

#ifdef __no_calloc
void* calloc(size_t nitems, size_t size) {
    void* ptr = malloc(size);
    if ( ptr ) { memset(ptr, 0, nitems * size); }
    return ptr;
}
#endif // !__no_calloc

