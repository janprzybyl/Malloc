#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <sys/mman.h>                       // mmap()
#include <stdlib.h>
#include <stdbool.h>                        // bool
#include <unistd.h>                         // getpagesize()

#define TINY_HEAP_TOTAL_SIZE (2 * getpagesize())
#define TINY_BLOCK_SIZE (TINY_HEAP_TOTAL_SIZE / 128)
#define SMALL_HEAP_TOTAL_SIZE (4 * getpagesize())
#define SMALL_BLOCK_SIZE (SMALL_HEAP_TOTAL_SIZE / 128)

typedef struct          s_block
{
    bool                is_free;
    struct s_block      *next;

}                       t_block;

typedef struct          s_heap
{
    
    struct s_block      *next;

}                       t_heap;

void *malloc(size_t size);
void free(void *ptr);
// void *realloc(void *ptr, size_t size);
// void show_alloc_mem()

void create_blocks(size_t heap_size, void *heap, size_t block_size);
void *find_free_block(t_block *heap);
void merge_heaps(t_block *heap, t_block *new_heap);

void *return_tiny();
void *return_small();
void *return_large();

#endif