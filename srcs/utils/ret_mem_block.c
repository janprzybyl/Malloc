#include "malloc.h"
#include <stdio.h>

t_heap     *tiny;
t_heap     *small;
t_heap     *large;

void *ret_tiny_block(size_t size)
{
    void        *ptr;
    t_heap      *heap;

    if (!tiny || !(ptr = find_free_block(tiny, size)))      // if heap doesn't exist or is full - create one
    {
        heap = setup_heap(TINY_HEAP_SIZE, TINY_BLOCK_SIZE);     // creates heap and saves it in temporary heap var

        if (!tiny)      // if heap doesn't existed earlier - add to the linked list as our fist heap
        {
            tiny = heap;
            tiny->next = NULL;
        }
        else        // otherwise ad to the linked list as our last heap
        {
            t_heap  *temp_tiny;

            temp_tiny = tiny;
            while (temp_tiny->next)
                temp_tiny = temp_tiny->next;
            temp_tiny->next = heap;      
        }
        ptr = ret_tiny_block(size);     // go recursive and find free block on newly created heap
    }

    return (ptr);    
}

void *ret_small_block(size_t size)
{
    void        *ptr;
    t_heap      *heap;

    if (!small || !(ptr = find_free_block(small, size)))      // if heap doesn't exist or is full - create one
    {
        heap = setup_heap(SMALL_HEAP_SIZE, SMALL_BLOCK_SIZE);     // creates heap and saves it in temporary heap var

        if (!small)      // if heap doesn't existed earlier - add to the linked list as our fist heap
        {
            small = heap;
            small->next = NULL;
        }
        else        // otherwise ad to the linked list as our last heap
        {
            t_heap  *temp_small;

            temp_small = small;
            while (temp_small->next)
                temp_small = temp_small->next;
            temp_small->next = heap;      
        }
        ptr = ret_small_block(size);     // go recursive and find free block on newly created heap
    }

    return (ptr);     
}


void *ret_large_block()
{
    void        *ptr;
    t_heap      *heap;

    heap = mmap(NULL, LARGE_HEAP_SIZE, PROT_READ | PROT_WRITE,
                MAP_PRIVATE | MAP_ANON, -1, 0);

    ptr = heap + sizeof(t_heap);
    heap->used_blocks = 1;

    if (!large)      // if heap doesn't existed earlier - add to the linked list as our fist heap
    {
        large = heap;
        large->next = NULL;
    }
    else        // otherwise ad to the linked list as our last heap
    {
        t_heap  *temp_large;

        temp_large = large;
        while (temp_large->next)
            temp_large = temp_large->next;
        temp_large->next = heap;      
    }

    return (ptr);    
}