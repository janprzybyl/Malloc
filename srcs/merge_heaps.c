#include "malloc.h"

void merge_heaps(t_block *heap, t_block *new_heap)
{
    t_block     *temp;
    
    temp = heap;
    while (temp->next)          // find last node
        temp = temp->next;

    temp->next = new_heap;      // merge last node with new heap

}