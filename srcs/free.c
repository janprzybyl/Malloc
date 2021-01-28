#include "malloc.h"

void free(void *ptr)
{
    if (ptr)
    {
        ptr = ptr - sizeof(t_block);
        ((t_block *)ptr)->is_free = true;
    }
}