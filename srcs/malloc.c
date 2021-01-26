#include "malloc.h"

void create_blocks(int heap_size, t_block *heap, int block_size)
{
    int         i;
    t_block     temp;

    temp = heap;
    while (i <= heap_size)
    {
        temp_size = 0;
        temp->is_free = TRUE;
        temp->next = temp + block_size;

        i += block_size;
        temp = temp->next;
    }
    temp->next = NULL;
}

t_block find_free_block(t_block *heap)
{
    t_block temp;

    temp = heap;
    while (temp)
    {
        if (temp->is_free)
            return (temp);

        temp = temp->next;
    }

    return (NULL);
}

t_block     tiny;
t_block     small;
t_block     large;

void *malloc(size_t size)
{   
    if (!size)
        return (NULL);


    if ((size_t)TINY_BLOCK_SIZE > size)
    {
        if (!tiny)
        {
            tiny = mmap(NULL, TINY_HEAP_TOTAL_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
            create_blocks(TINY_HEAP_TOTAL_SIZE, tiny, TINY_BLOCK_SIZE);
        }
        else
        { 
            if (!find_free_block(tiny))
                create another tiny heap
        }
    }
    else if ((size_t)SMALL_BLOCK_SIZE > size)
    {
        if (!small)
        {
            small = mmap(NULL, SMALL_HEAP_TOTAL_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
            create_blocks(SMALL_HEAP_TOTAL_SIZE, small, SMALL_BLOCK_SIZE);
        }
        else
        {
            if (!find_free_block(small))
                create another tiny heap
        }
    }
    else
        large = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);


}