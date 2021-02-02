#include "malloc.h"
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
    while (i < (heap_size - block_size))
    {
        ((t_block *)temp)->size = 0;
        ((t_block *)temp)->is_free = true;
        ((t_block *)temp)->next = temp + block_size;
        ((t_block *)temp)->heap = heap;

        i = i + block_size;
        temp = temp + block_size;
    }
    ((t_block *)temp)->size = 0;
    ((t_block *)temp)->is_free = true;
    ((t_block *)temp)->next = NULL;     // indicate end of heap
    ((t_block *)temp)->heap = heap;
    
    ((t_heap *)heap)->heap_size = heap_size;
    ((t_heap *)heap)->used_blocks = 0;

    return (heap);
}