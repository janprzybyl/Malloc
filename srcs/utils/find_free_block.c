#include "malloc.h"

// void *find_free_block(t_block *heap, size_t size)
// {
//     void    *temp;

//     temp = heap;
//     while (temp)
//     {
//         if (((t_block *)temp)->is_free)          // once block is free, return the pointer
//         {

//             ((t_block *)temp)->size = size;      // mark as not free already
//             ((t_block *)temp)->is_free = false;      // mark as not free already
//             return (temp + sizeof(t_block));    // block shift from structure to actual memory block
//         }
//         temp = ((t_block *)temp)->next;
//     }

//     return (NULL);
// }
#include <stdio.h>
void *find_free_block(t_heap *heap, size_t size)
{
    void    *temp_heap;
    void    *temp_block;

    temp_heap = heap;
    printf("find free block\n");
    while (temp_heap)
    {
        printf("heap starts here\n");
        temp_block = (temp_heap + sizeof(t_heap));       // heap's shift from metadata pointer to actual memory pointer
        while (temp_block)
        {
            printf("check if block at address %p is free\n", temp_block);
            if (((t_block *)temp_block)->is_free)          // once block is free, return the pointer
            {
                printf("is free - return\n");
                ((t_heap *)temp_heap)->used_blocks += 1;
                ((t_block *)temp_block)->size = size;      // mark as not free already
                ((t_block *)temp_block)->is_free = false;      // mark as not free already
                return (temp_block + sizeof(t_block));    // block shift from structure to actual memory block
            }
            printf("is not free - go again\n");
            temp_block = ((t_block *)temp_block)->next;     // go to the next block
        }
        printf("end of heap - go to annother\n");
        temp_heap = ((t_heap *)temp_heap)->next;
    }

    return (NULL);
}