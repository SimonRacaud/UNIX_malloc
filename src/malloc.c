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

extern void *head;
extern block_t *end;
extern const size_t BLOCK_SIZE;
extern const size_t MIN_DATA_SIZE;
extern const void *SBRK_ERROR;

static block_t *set_new_block(size_t s, block_t *last)
{
    block_t *ptr;

    ptr = find_best_match(&last, s);
    if (ptr) {
        if ((ptr->size - s) >= MIN_CHUNK_SIZE)
            split_block(ptr, s);
        ptr->is_free = 0;
    } else {
        ptr = extend_heap(last, s);
        if (!ptr)
            return NULL;
    }
    return ptr;
}

block_t *find_best_match(block_t **last, size_t size)
{
    block_t *ptr = head;
    block_t *best_ptr = NULL;

    while (ptr) {
        if (ptr->is_free && ptr->size >= size) {
            if (best_ptr == NULL) {
                best_ptr = ptr;
            } else if (best_ptr->size > ptr->size) {
                best_ptr = ptr;
            }
        }
        *last = ptr;
        ptr = ptr->next;
    }
    if (best_ptr && !best_ptr->is_free) {
        return NULL;
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
    ptr->next_free = NULL;
    if (last) {
        last->next = ptr;
    }
    ptr->prev = last;
    ptr->is_free = 0;
    end = ptr;
    //printf("1 CREATE BLOCK : s(%lu) (%u)\n\n", ptr->size, ptr->is_free);
    if ((size_jump - (BLOCK_SIZE + data_size)) >= MIN_CHUNK_SIZE) {
        split_block(ptr, data_size);
    }
    return ptr;
}

void *malloc(size_t size)
{
    printf("MALLOC\n");
    block_t *ptr;
    block_t *last = head;
    size_t s = align_power2(size + BLOCK_SIZE) - BLOCK_SIZE;

    if (size == 0)
        return NULL;
    if (head) {
        ptr = set_new_block(s, last);
    } else {
        ptr = extend_heap(NULL, s);
        if (!ptr)
            return NULL;
        head = ptr;
    }
    return (ptr->data);
}

