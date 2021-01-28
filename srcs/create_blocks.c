#include "malloc.h"
#include <stdio.h>
//  This function creates linked list of blocks metadata

void create_blocks(size_t heap_size, void *heap, size_t block_size)
{
    size_t      i;
    void        *temp;
    
    i = 0;
    temp = heap;
    while (i < (heap_size - block_size))
    {
        ((t_block *)temp)->is_free = true;
        ((t_block *)temp)->next = temp + block_size;

        i = i + block_size;
        temp = temp + block_size;
    }
    ((t_block *)temp)->next = NULL;
}