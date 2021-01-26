#include "malloc.h"

void free(void *ptr)
{
    t_block     *curr;

    if (valid pointer)
    {
        curr = ptr;
        curr--;
        curr->is_free = TRUE;
    }
}