#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <sys/mman.h>                       // mmap()
#include <stdlib.h>
#include <stdbool.h>                        // bool
#include <unistd.h>                         // getpagesize()

typedef struct          s_block
{
    size_t              size;
    bool                is_free;
    struct s_block      *next;

}                       t_block;

typedef struct          s_heap
{
    int                 *used_blocks;
    struct s_heap       *next;

}                       t_heap;

#define TINY_HEAP_SIZE (2 * getpagesize())
#define TINY_BLOCK_SIZE ((TINY_HEAP_SIZE - sizeof(t_heap)) / 4)
#define SMALL_HEAP_SIZE (4 * getpagesize())
#define SMALL_BLOCK_SIZE ((SMALL_HEAP_SIZE - sizeof(t_heap)) / 112)
#define LARGE_HEAP_SIZE getpagesize() - sizeof(t_heap)

extern t_heap     *tiny;
extern t_heap     *small;
extern t_heap     *large;

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
// void show_alloc_mem()

// void create_blocks(size_t heap_size, void *heap, size_t block_size);
void *find_free_block(t_heap *heap, size_t size);
void *setup_heap(size_t heap_size, size_t block_size);
// void merge_heaps(t_block *heap, t_block *new_heap);
void *ret_tiny_block(size_t size);
// void *ret_small_block(size_t size);
// void *ret_large_block();

#endif