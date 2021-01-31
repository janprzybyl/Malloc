#include "malloc.h"
#include <stdio.h>

t_heap     *tiny;
// t_heap     *small;
// t_heap     *large;

void *ret_tiny_block(size_t size)
{
    printf("1\n");
    void    *ptr;

    if (!tiny)      // if no heap exist yet
    {
        printf("heap doesn't exist - let's create!\n");
        tiny = setup_heap(TINY_HEAP_SIZE, TINY_BLOCK_SIZE);
        tiny->next = NULL;
    }
    printf("2\n");
    if (!(ptr = find_free_block(tiny, size)))       // if heap is full
    {
        printf("heap full - let's create another one!\n");
        t_heap  *new_tiny;

        printf("a\n");
        new_tiny = setup_heap(TINY_HEAP_SIZE, TINY_BLOCK_SIZE);
        printf("b\n");
        t_heap *temp_tiny = tiny;
        while (temp_tiny->next)
            temp_tiny = temp_tiny->next;
        printf("c\n");
        temp_tiny->next = new_tiny;
        printf("d\n");
        ptr = find_free_block(tiny, size);
        printf("e\n");
    }
    printf("3\n");

    return (ptr);    
}

// void *ret_small_block(size_t size)
// {
//     void    *ptr;

//     if (!small)
//     {
//         small = mmap(NULL, SMALL_HEAP_SIZE, PROT_READ | PROT_WRITE, 
//                     MAP_PRIVATE | MAP_ANON, -1, 0);
//         create_blocks(SMALL_HEAP_SIZE, small, SMALL_BLOCK_SIZE);
//     }

//     if (!(ptr = find_free_block(small, size)))
//     {
//         t_block     *new_small;

//         new_small = mmap(NULL, SMALL_HEAP_SIZE, PROT_READ | PROT_WRITE, 
//                         MAP_PRIVATE | MAP_ANON, -1, 0);
//         create_blocks(SMALL_HEAP_SIZE, new_small, SMALL_BLOCK_SIZE);
//         merge_heaps(small, new_small);
//         ptr = find_free_block(small, size);
//     }

//     return (ptr);    
// }


// void *ret_large_block()
// {
//     void    *ptr;

//     large = mmap(NULL, LARGE_HEAP_SIZE, PROT_READ | PROT_WRITE,
//                 MAP_PRIVATE | MAP_ANON, -1, 0);
//     // add to linked list which keeps track of large heaps
//     ptr = large;

//     return (ptr);
// }