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
extern const size_t MIN_DATA_SIZE;
extern void *head;
extern block_t *end;

static size_t nb_block_split_size(size_t s)
{
    size_t size = highestPowerof2(s);

    if (s - size > 0) {
        return 1 + nb_block_split_size(s - size);
    }
    return 1;
}

static bool can_split_block(size_t available_size)
{
    size_t new_block_size = highestPowerof2(available_size);

    if (available_size == new_block_size)
        return true;
    if (new_block_size < MIN_CHUNK_SIZE)
        return false;
    if (available_size - new_block_size == 0)
        return true;
    return can_split_block(available_size - new_block_size);
}

static block_t *process_fusion(block_t *beg, size_t free_block_full_size,
size_t nb_splited_block, block_t *last_free_block)
{
    beg->size = free_block_full_size - BLOCK_SIZE;
    beg->next = last_free_block->next;
    if (beg->next) {
        beg->next->prev = beg;
    }
    if (nb_splited_block > 1) {
        split_block(beg, highestPowerof2(beg->size + BLOCK_SIZE) - BLOCK_SIZE);
    }
    return beg;
}

static block_t *fusion_free_blocks(block_t *beg)
{
    size_t nb_free_block = 1;
    size_t free_block_full_size = (beg->size + BLOCK_SIZE);
    block_t *last_free_block;
    size_t nb_splited_block;

    //printf("FUSION\n");
    for (block_t *ptr = beg->next; ptr != NULL; ptr = ptr->next) {
        if (!ptr->is_free)
            break;
        nb_free_block++;
        free_block_full_size += ptr->size + BLOCK_SIZE;
        last_free_block = ptr;
    }
    if (can_split_block(free_block_full_size) == false)
        return beg;
    nb_splited_block = nb_block_split_size(free_block_full_size);
    if (nb_splited_block >= nb_free_block) {
        return beg;
    }
    return process_fusion(beg, free_block_full_size, nb_splited_block, last_free_block);
}

block_t *get_meta_block(void *addr)
{
    return (block_t *)((char *)addr - BLOCK_SIZE);
}

bool is_valid_addr(void *data_addr)
{
    if (data_addr && head) {
        if (data_addr >= head && data_addr < sbrk(0)) {
            return (data_addr == get_meta_block(data_addr)->data);
        }
    }
    return false;
}

static block_t *get_first_prev_free_block(block_t *current)
{
    block_t *prev;

    if (current->prev && current->prev->is_free) {
        prev = get_first_prev_free_block(current->prev);
        if (prev == NULL) {
            return current;
        } else {
            return prev;
        }
    }
    return NULL;
}

void try_move_break(void)
{
    size_t full_size_count = 0;
    size_t available_size;
    size_t available_size_power2;

    for (block_t *ptr = end; ptr != NULL && ptr->is_free; ptr = ptr->prev) {
        full_size_count += ptr->size + BLOCK_SIZE;
        if (full_size_count == HEAP_ALIGN && ptr->prev) {
            //printf("FREE A %lu \n", (full_size_count));
            //printf("MOVE BREAK %lu \n", ptr->size);
            ptr->prev->next = NULL;
            brk(ptr);
            full_size_count = 0;
        }
        printf("BR %lu > %lu %d %lu \n", full_size_count, HEAP_ALIGN, ptr->prev->is_free, ptr->prev->size);
        if (full_size_count > HEAP_ALIGN && ptr->prev) {
            available_size = full_size_count - HEAP_ALIGN;
            available_size_power2 = highestPowerof2(available_size);
            printf("BREAK: full(%lu) \n", full_size_count);
            printf("BREAK: av(%lu) av2(%lu) / %d \n", available_size, available_size_power2, can_split_block(available_size));
            ptr->size = available_size;
            ptr->next = NULL;
            if (available_size_power2 != available_size && can_split_block(available_size)) {
                split_block(ptr, highestPowerof2(available_size + BLOCK_SIZE) - BLOCK_SIZE);
            }
            brk(ptr + (available_size - BLOCK_SIZE));
            full_size_count = available_size;
            printf("SPLIT & BREAK %lu \n", ptr->size);
            //printf("FREE E %lu \n", (full_size_count - HEAP_ALIGN));
            //printf("XXX %lu \n", ptr->size);
        }
    }
}

void free(void *addr)
{
    block_t *ptr;

    if (is_valid_addr(addr)) {
        ptr = get_meta_block(addr);
        ptr->is_free = 1;
        if (ptr->prev && ptr->prev->is_free) {
            ptr = fusion_free_blocks(get_first_prev_free_block(ptr));
        } else if (ptr->next && ptr->next->is_free) {
            ptr = fusion_free_blocks(ptr);
        } 
        if (end && end->is_free) {
            try_move_break();
        }
    }
}

