/*
** EPITECH PROJECT, 2021
** list
** File description:
** create.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

extern const size_t BLOCK_SIZE;
extern const size_t MIN_DATA_SIZE;
extern const void *SBRK_ERROR;

static void alloc_in_this_block(block_t *ptr, size_t size)
{
    if ((ptr->size - size) >= MIN_CHUNK_SIZE)
        split_block(ptr, size);
    ptr->is_free = 0;
}

block_t *add_block(size_t size)
{
    block_t *ptr;
    block_t *last = listEnd(NULL);

    ptr = find_best_match(&last, size);
    if (ptr) {
        alloc_in_this_block(ptr, size);
    } else {
        ptr = extend_heap(last, size);
        if (!ptr)
            return NULL;
    }
    return ptr;
}

block_t *extend_heap(block_t *last, size_t size)
{
    block_t *ptr = sbrk(0);
    size_t size_jump = highest_multiple_of_x(BLOCK_SIZE + size, heap_align());

    if (sbrk(size_jump) == SBRK_ERROR) {
        return NULL;
    }
    ptr->size = (size_jump - BLOCK_SIZE);
    ptr->next = NULL;
    if (last) {
        last->next = ptr;
    }
    ptr->prev = last;
    ptr->is_free = 0;
    listEnd(ptr);
    if ((size_jump - (BLOCK_SIZE + size)) >= MIN_CHUNK_SIZE) {
        split_block(ptr, size);
    }
    return ptr;
}