/*
 * File: malloc.c
 * Project: src
 * File Created: Thursday, 1st January 1970 1:00:00 am
 * Author: simon (simon.racaud@epitech.eu)
 * -----
 * Last Modified: Tuesday, 9th February 2021 9:11:53 pm
 * Modified By: simon (simon.racaud@epitech.eu>)
 * -----
 * Copyright 2021 - 2021 TEK2, Epitech
 */

#include "my_malloc.h"

void *base = NULL;
const size_t MIN_DATA_SIZE = 1;

void *malloc(size_t size)
{
    block_t *ptr;
    block_t *last = base;
    size_t s = align_power2(size + BLOCK_SIZE) - BLOCK_SIZE;

    if (base) {
        ptr = find_block(&last, s);
        if (ptr) { // Have an available block
            if ((ptr->size - s) >= align_power2(BLOCK_SIZE + MIN_DATA_SIZE))
                split_block(ptr, s);
            ptr->is_free = 0;
        } else {
            ptr = extend_heap(last, s);
            if (!ptr)
                return NULL;
        }
    } else {
        // Its the first alloc of the processus
        ptr = extend_heap(NULL, s);
        if (!ptr)
            return NULL;
        base = ptr;
    }
    return (ptr->data);
}

block_t *find_block(block_t **last, size_t size)
{
    block_t *ptr = base;

    while (ptr && !(ptr->is_free && ptr->size >= size)) {
        *last = ptr;
        ptr = ptr->next;
    }
    return ptr;
}

block_t *extend_heap(block_t *last, size_t s)
{
    block_t *ptr = sbrk(0);

    if (sbrk(BLOCK_SIZE + s) == SBRK_ERROR) {
        return NULL;
    }    
    ptr->size = s;
    ptr->next = NULL;
    if (last)
        last->next = ptr;
    ptr->prev = last;
    ptr->is_free = 0;
    return ptr;
}

void split_block(block_t *ptr, size_t s)
{
    block_t *new = (block_t *)(ptr->data + s);

    new->size = ptr->size - s - BLOCK_SIZE;
    new->next = ptr->next;
    new->prev = ptr;
    new->is_free = 1;
    ptr->size = s;
    ptr->next = new;
}
