#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
    t_block     *temp;

    temp = ptr - sizeof(t_block);
    if (size <= (size_t)TINY_BLOCK_SIZE)
    {
        if (temp->size > (size_t)TINY_BLOCK_SIZE)
        {
            free(ptr);
            ptr = ret_tiny_block(size);
        }
    }
    else if (size > (size_t)TINY_BLOCK_SIZE && size <= (size_t)SMALL_BLOCK_SIZE)
    {
        if (temp->size < (size_t)SMALL_BLOCK_SIZE || temp->size > (size_t)SMALL_BLOCK_SIZE)
        {
            free(ptr);
            ptr = ret_small_block(size);
        }         
    }
    else
    {
        if (temp->size < (size_t)LARGE_HEAP_SIZE) 
        {
            free(ptr);
            ptr =  ret_large_block();
        }
    }   

    return (ptr);
}