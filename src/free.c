/*
 * File: free.c
 * Project: src
 * File Created: Thursday, 1st January 1970 1:00:00 am
 * Author: simon (simon.racaud@epitech.eu)
 * -----
 * Last Modified: Tuesday, 9th February 2021 10:00:06 pm
 * Modified By: simon (simon.racaud@epitech.eu>)
 * -----
 * Copyright 2021 - 2021 TEK2, Epitech
 */

#include "my_malloc.h"

extern const size_t BLOCK_SIZE;
extern void *base;

static block_t *fusion_free_blocks(block_t *beg)
{
    if (beg->next && beg->next->is_free) {
        beg->size += BLOCK_SIZE + beg->next->size;
        beg->next = beg->next->next;
        if (beg->next) {
            beg->next->prev = beg;
        }
    }
    return beg;
}

block_t *get_meta_block(void *addr)
{
    return (block_t *)((char *)addr - BLOCK_SIZE);
}

bool is_valid_addr(void *data_addr)
{
    if (data_addr && base) {
        if (data_addr >= base && data_addr < sbrk(0)) {
            return (data_addr == get_meta_block(data_addr)->data);
        }
    }
    return false;
}

void free(void *addr)
{
    block_t *ptr;

    if (is_valid_addr(addr)) {
        ptr = get_meta_block(addr);
        ptr->is_free = 1;
        if (ptr->prev && ptr->prev->is_free) {
            ptr = fusion_free_blocks(ptr->prev);
        }
        if (ptr->next) {
            ptr = fusion_free_blocks(ptr);
        } else {
            if (ptr->prev) {
                ptr->prev->next = NULL;
            } else {
                base = NULL;
            }
            brk(ptr);
        }
    }
}

