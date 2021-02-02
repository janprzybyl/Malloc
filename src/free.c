#include "malloc.h"
#include <stdio.h>

void free(void *ptr)
{
    t_heap  *heap;

    if (!ptr)
        return;


        ptr = ptr - sizeof(t_block);
        ((t_block *)ptr)->size = 0;
        ((t_block *)ptr)->is_free = true;

        heap = ((t_block *)ptr)->heap;
        heap->used_blocks -= 1;  

        if (heap->prev)
        {
            heap->prev->next = heap->next;
            munmap((void *)heap, heap->heap_size);
        }
}