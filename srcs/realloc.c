#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
    void    *ptr;

    if ((size_t)TINY_BLOCK_SIZE >= size)
    {
        if (ptr_is_tiny)
            do nothing
        else if (ptr_is_small)
        {
            free(ptr);
            ptr = start(tiny, TINY_HEAP_TOTAL_SIZE, TINY_BLOCK_SIZE);
            return (ptr);
        }
        else
        {
            // function will call return_large I guess
            large = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANON, -1, 0);
            // add to linked list which keeps track of large heaps
            ptr = large;
        }    
    }
    else if (size > TINY_BLOCK_SIZE && size <= SMALL_BLOCK_SIZE)
    {
        if (ptr_is_tiny)
            do nothing
        else if (ptr_is_small)
        {
            free(ptr);
            ptr = start(tiny, TINY_HEAP_TOTAL_SIZE, TINY_BLOCK_SIZE);
            return (ptr);
        }
        else
        {
            // function will call return_large I guess
            large = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANON, -1, 0);
            // add to linked list which keeps track of large heaps
            ptr = large;
        }            
    }
    else (size > SMALL_BLOCK_SIZE)
    {

    }   
}