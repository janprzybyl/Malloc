#include "malloc.h"
#include <string.h>

void *realloc(void *ptr, size_t size)
{
    t_block     *temp;
    void        *data;

    memcpy(data, ptr, strlen(ptr));
    temp = ptr - sizeof(t_block);
    if (size <= (size_t)TINY_BLOCK_SIZE)        // if requested block is TINY
    {
        if (temp->size > (size_t)TINY_BLOCK_SIZE)       // if current block is not TINY - free it and allocate TINY block
        {
            free(ptr);
            ptr = ret_tiny_block(size);
            memcpy(ptr, data, sizeof(data));
        }
    }
    else if (size > (size_t)TINY_BLOCK_SIZE && size <= (size_t)SMALL_BLOCK_SIZE)        // if requested block is SMALL
    {
        if (temp->size < (size_t)SMALL_BLOCK_SIZE || temp->size > (size_t)SMALL_BLOCK_SIZE)     // if current block is not SMALL - free it and allocate SMALL block
        {
            free(ptr);
            ptr = ret_small_block(size);
            memcpy(ptr, data, sizeof(data));
        }         
    }
    else        // if requested block is LARGE
    {
        if (temp->size < (size_t)LARGE_HEAP_SIZE)       // if current block is not LARGE - free it and allocate LARGE block
        {
            free(ptr);
            ptr =  ret_large_block();
            memcpy(ptr, data, sizeof(data));
        }
    }   

    return (ptr);
}