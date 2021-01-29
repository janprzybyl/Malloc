#include "malloc.h"
#include <stdio.h>

void *find_free_block(t_block *heap, size_t size)
{
    void    *temp;

    temp = heap;
    while (temp)
    {
        if (((t_block *)temp)->is_free)          // once block is free, return the pointer
        { 
            ((t_block *)temp)->size = size;      // mark as not free already
            ((t_block *)temp)->is_free = false;      // mark as not free already
            return (temp + sizeof(t_block));    // block shift from structure to actual memory block
        }
        temp = ((t_block *)temp)->next;
    }

    return (NULL);
}