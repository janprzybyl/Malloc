#include "malloc.h"
#include <stdio.h>      // temporary    

t_block     *tiny;
t_block     *small;
t_block     *large;

void *return_small()
{
    void    *ptr;

    if (!small)      // if tiny heap doesn't exist
    {
        small = mmap(NULL, SMALL_HEAP_TOTAL_SIZE, PROT_READ | PROT_WRITE, 
                    MAP_PRIVATE | MAP_ANON, -1, 0);
        create_blocks(SMALL_HEAP_TOTAL_SIZE, small, SMALL_BLOCK_SIZE);
    }

    if (!(ptr = find_free_block(small)))
    {
        t_block     *new_small;

        new_small = mmap(NULL, SMALL_HEAP_TOTAL_SIZE, PROT_READ | PROT_WRITE, 
                        MAP_PRIVATE | MAP_ANON, -1, 0);
        create_blocks(SMALL_HEAP_TOTAL_SIZE, new_small, SMALL_BLOCK_SIZE);
        merge_heaps(small, new_small);
        ptr = find_free_block(small);
    }

    return (ptr);    
}
void *return_tiny()
{
    void    *ptr;

    if (!tiny)      // if tiny heap doesn't exist
    {
        tiny = mmap(NULL, TINY_HEAP_TOTAL_SIZE, PROT_READ | PROT_WRITE, 
                    MAP_PRIVATE | MAP_ANON, -1, 0);
        create_blocks(TINY_HEAP_TOTAL_SIZE, tiny, TINY_BLOCK_SIZE);
    }

    if (!(ptr = find_free_block(tiny)))
    {
        t_block     *new_tiny;

        new_tiny = mmap(NULL, TINY_HEAP_TOTAL_SIZE, PROT_READ | PROT_WRITE, 
                        MAP_PRIVATE | MAP_ANON, -1, 0);
        create_blocks(TINY_HEAP_TOTAL_SIZE, new_tiny, TINY_BLOCK_SIZE);
        merge_heaps(tiny, new_tiny);
        ptr = find_free_block(tiny);
    }

    return (ptr);    
}

void *return_large()
{
    void    *ptr;

    large = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE,
                MAP_PRIVATE | MAP_ANON, -1, 0);
    // add to linked list which keeps track of large heaps
    ptr = large;

    return (ptr);
}

void *malloc(size_t size)
{
    void    *ptr;

    if (!size)
        return (NULL);

    size = size + sizeof(t_block);      // we have to add metadata size to block 

    if (size <= (size_t)TINY_BLOCK_SIZE)
        ptr = return_tiny();
    else if (size <= (size_t)SMALL_BLOCK_SIZE)
        ptr = return_small();
    else
        ptr = return_large();

    return (ptr);
}