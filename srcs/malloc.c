#include "malloc.h"
#include <stdio.h>

void create_blocks(size_t heap_size, void *heap, size_t block_size)
{
    size_t      i;
    void        *temp;
    
    i = 0;
    temp = heap;
    while (i < heap_size - block_size)
    {
        ((t_block *)temp)->data_size = 0;
        ((t_block *)temp)->is_free = true;
        ((t_block *)temp)->next = temp + block_size;

        i += block_size;
        temp = temp + block_size;
    }
    ((t_block *)temp)->next = NULL;

}

t_block *find_free_block(t_block *heap)
{
    t_block     *temp;

    temp = heap;
    while (temp)
    {
        if (temp->is_free)
        {   
            temp->is_free = false;
            return (temp + sizeof(t_block));
        }
        temp = temp->next;
    }

    return (NULL);
}

void merge_heaps(t_block *heap, t_block *new_heap)
{
    t_block     *temp;

    temp = heap;
    while (temp)
        temp = temp->next;

    temp->next = new_heap;

}

t_block     *tiny;
t_block     *small;
t_block     *large;

void *malloc(size_t size)
{
    void    *ptr;

    if (!size)
        return (NULL);

    if ((size_t)TINY_BLOCK_SIZE >= size)
    {
        if (!tiny)      // if tiny heap doesn't exist
        {
            printf("A\n");
            tiny = mmap(NULL, TINY_HEAP_TOTAL_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
            create_blocks(TINY_HEAP_TOTAL_SIZE, tiny, TINY_BLOCK_SIZE);
        }

        if (!(ptr = find_free_block(tiny)))
        {
            printf("B\n");
            t_block     *new_tiny;

            new_tiny = mmap(NULL, TINY_HEAP_TOTAL_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
            create_blocks(TINY_HEAP_TOTAL_SIZE, new_tiny, TINY_BLOCK_SIZE);
            merge_heaps(tiny, new_tiny);
            ptr = find_free_block(tiny);
        }

        printf("C\n");
        printf("address = %p\n", ptr);
        return (ptr);

    }
    else if ((size_t)SMALL_BLOCK_SIZE >= size)
    {
        printf("SMALL\n");
        if (!small)      // if small heap doesn't exist
        {
            small = mmap(NULL, SMALL_HEAP_TOTAL_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
            create_blocks(SMALL_HEAP_TOTAL_SIZE, small, SMALL_BLOCK_SIZE);
        }

        if (!(ptr = find_free_block(small)))
        {
            t_block     *new_small;

            new_small = mmap(NULL, SMALL_HEAP_TOTAL_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
            create_blocks(SMALL_HEAP_TOTAL_SIZE, new_small, SMALL_BLOCK_SIZE);
            merge_heaps(small, new_small);
            ptr = find_free_block(small);
        }

        return (ptr);

    }
    else
    {
        ptr = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
        
        return (ptr);
    }    

}