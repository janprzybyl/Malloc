#include "malloc.h"

t_block     *tiny;
t_block     *small;
t_block     *large;

void *ret_small_block(size_t size)
{
    void    *ptr;

    if (!small)
    {
        small = mmap(NULL, SMALL_HEAP_SIZE, PROT_READ | PROT_WRITE, 
                    MAP_PRIVATE | MAP_ANON, -1, 0);
        create_blocks(SMALL_HEAP_SIZE, small, SMALL_BLOCK_SIZE);
    }

    if (!(ptr = find_free_block(small, size)))
    {
        t_block     *new_small;

        new_small = mmap(NULL, SMALL_HEAP_SIZE, PROT_READ | PROT_WRITE, 
                        MAP_PRIVATE | MAP_ANON, -1, 0);
        create_blocks(SMALL_HEAP_SIZE, new_small, SMALL_BLOCK_SIZE);
        merge_heaps(small, new_small);
        ptr = find_free_block(small, size);
    }

    return (ptr);    
}

void *ret_tiny_block(size_t size)
{
    void    *ptr;

    if (!tiny)
    {
        tiny = mmap(NULL, TINY_HEAP_SIZE, PROT_READ | PROT_WRITE, 
                    MAP_PRIVATE | MAP_ANON, -1, 0);
        create_blocks(TINY_HEAP_SIZE, tiny, TINY_BLOCK_SIZE);
    }

    if (!(ptr = find_free_block(tiny, size)))
    {
        t_block     *new_tiny;

        new_tiny = mmap(NULL, TINY_HEAP_SIZE, PROT_READ | PROT_WRITE, 
                        MAP_PRIVATE | MAP_ANON, -1, 0);
        create_blocks(TINY_HEAP_SIZE, new_tiny, TINY_BLOCK_SIZE);
        merge_heaps(tiny, new_tiny);
        ptr = find_free_block(tiny, size);
    }

    return (ptr);    
}

void *ret_large_block()
{
    void    *ptr;

    large = mmap(NULL, LARGE_HEAP_SIZE, PROT_READ | PROT_WRITE,
                MAP_PRIVATE | MAP_ANON, -1, 0);
    // add to linked list which keeps track of large heaps
    ptr = large;

    return (ptr);
}