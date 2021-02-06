#include "malloc.h"
#include <stdio.h>

t_heap     *tiny;
t_heap     *small;
t_heap     *large;

void *malloc(size_t size)
{
    void    *ptr;

    if (!size)
        return (NULL);

    size = size + sizeof(t_block);      // we have to add metadata size to block 

    if (size <= (size_t)TINY_BLOCK_SIZE)
    {
        ptr = ret_mem_block(&tiny, TINY_HEAP_SIZE, TINY_BLOCK_SIZE, size);
            int i = 0;
    t_heap *temp_tiny = tiny;
    // printf("tiny after = %p\n", temp_tiny);
    while (temp_tiny)
    {
        printf("tiny nr %d\n", i);
        i++;
        temp_tiny = temp_tiny->next;
    }
    }
    else if (size <= (size_t)SMALL_BLOCK_SIZE)
    {
        ptr = ret_mem_block(&small, SMALL_HEAP_SIZE, SMALL_BLOCK_SIZE, size);
            int x = 0;
    t_heap *temp_small = small;
    // printf("tiny after = %p\n", temp_small);
    while (temp_small)
    {
        printf("small nr %d\n", x);
        x++;
        temp_small = temp_small->next;
    }
    }
    else
    {
        ptr = ret_mem_block(&large, LARGE_HEAP_SIZE, LARGE_BLOCK_SIZE, size);
            int y = 0;
    t_heap *temp_large = large;
    while (temp_large)
    {
        printf("large nr %d\n", y);
        y++;
        temp_large = temp_large->next;
    }
    }



    return (ptr);
}