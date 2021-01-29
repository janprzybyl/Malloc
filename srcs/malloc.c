#include "malloc.h"
#include <stdio.h>      // temporary    

void *malloc(size_t size)
{
    void    *ptr;

    if (!size)
        return (NULL);

    size = size + sizeof(t_block);      // we have to add metadata size to block 

    if (size <= (size_t)TINY_BLOCK_SIZE)
        ptr = ret_tiny_block(size);
    else if (size <= (size_t)SMALL_BLOCK_SIZE)
        ptr = ret_small_block(size);
    else
        ptr = ret_large_block();

    return (ptr);
}