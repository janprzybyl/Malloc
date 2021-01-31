#include "malloc.h"

// void create_blocks(size_t heap_size, void *heap, size_t block_size)
// {
//     size_t      i;
//     void        *temp;
    
//     i = sizeof(t_heap);
//     temp = heap;
//     while (i < (heap_size - block_size))
//     {
//         ((t_block *)temp)->size = 0;
//         ((t_block *)temp)->is_free = true;
//         ((t_block *)temp)->next = temp + block_size;

//         i = i + block_size;
//         temp = temp + block_size;
//     }
//     ((t_block *)temp)->next = NULL;
// }
#include <stdio.h>
void *setup_heap(size_t heap_size, size_t block_size)
{
    void        *heap;
    void        *temp;
    size_t      i;

    heap = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, 
                MAP_PRIVATE | MAP_ANON, -1, 0);

    temp = heap + sizeof(t_heap);
    i = sizeof(t_heap);     // first sizeof(t_heap) bytes are our heap's metadata so we need to skip it
    printf("before creating blocks\n");
    while (i < (heap_size - block_size))
    {
        printf("block at address %p\n", temp);
        ((t_block *)temp)->size = 0;
        ((t_block *)temp)->is_free = true;
        ((t_block *)temp)->next = temp + block_size;

        i = i + block_size;
        temp = temp + block_size;
    }
    printf("after creating blocks\n");
    ((t_block *)temp)->next = NULL;     // indicate end of heap
    printf("indicate end of heap\n");
    ((t_heap *)heap)->used_blocks = 0;
    printf("set used_blocks to 0\n");

    return (heap);
}