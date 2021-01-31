#include "malloc.h"

void *find_free_block(t_heap *heap, size_t size)
{
    void    *temp_heap;
    void    *temp_block;

    temp_heap = heap;
    while (temp_heap)
    {
        temp_block = (temp_heap + sizeof(t_heap));       // heap's shift from metadata pointer to actual memory pointer
        while (temp_block)
        {
            if (((t_block *)temp_block)->is_free)          // once block is free, return the pointer
            {
                ((t_heap *)temp_heap)->used_blocks += 1;
                ((t_block *)temp_block)->size = size;      // mark as not free already
                ((t_block *)temp_block)->is_free = false;      // mark as not free already
                return (temp_block + sizeof(t_block));    // block shift from structure to actual memory block
            }
            temp_block = ((t_block *)temp_block)->next;     // go to the next block
        }
        temp_heap = ((t_heap *)temp_heap)->next;
    }

    return (NULL);
}