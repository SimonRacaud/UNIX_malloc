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

extern const size_t BLOCK_SIZE;
extern void *base;
extern const size_t MIN_DATA_SIZE;
extern const void *SBRK_ERROR;

void *malloc(size_t size)
{
    block_t *ptr;
    block_t *last = base;
    size_t s = align_power2(size + BLOCK_SIZE) - BLOCK_SIZE;

    if (base) {
        ptr = find_best_match(&last, s);
        if (ptr) { // Have an available block
            if ((ptr->size - s) >= MIN_CHUNK_SIZE)
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

block_t *find_best_match(block_t **last, size_t size)
{
    block_t *ptr = base;
    block_t *best_ptr = NULL;

    while (ptr) {
        if (IS_COMPLIANT_CHUNK(ptr)) {
            if (best_ptr == NULL) {
                best_ptr = ptr;
            } else if (best_ptr->size > ptr->size) {
                best_ptr = ptr;
            }
        }
        *last = ptr;
        ptr = ptr->next;
    }
    return best_ptr;
}

block_t *extend_heap(block_t *last, size_t data_size)
{
    block_t *ptr = sbrk(0);
    size_t size_jump = highestMultipleofx(BLOCK_SIZE + data_size, HEAP_ALIGN);

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
    if ((size_jump - (BLOCK_SIZE + data_size)) >= MIN_CHUNK_SIZE) {
        split_block(ptr, data_size);
    }
    return ptr;
}

void split_block(block_t *ptr, size_t new_size)
{
    size_t available_size = ptr->size - new_size;
    size_t new_block_size = highestPowerof2(available_size);
    block_t *new;

    new = (block_t *)(ptr->data + new_size);
    new->size = available_size - BLOCK_SIZE;
    new->next = ptr->next;
    new->prev = ptr;
    new->is_free = 1;
    ptr->size = new_size;
    ptr->next = new;
    if (available_size - new_block_size > 0) {
        split_block(new, (new_block_size - BLOCK_SIZE));
    }
}
