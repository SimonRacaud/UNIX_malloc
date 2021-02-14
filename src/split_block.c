/*
 * File: split_block.c
 * Project: src
 * File Created: Thursday, 1st January 1970 1:00:00 am
 * Author: simon (simon.racaud@epitech.eu)
 * -----
 * Last Modified: Sunday, 14th February 2021 6:15:55 pm
 * Modified By: simon (simon.racaud@epitech.eu>)
 * -----
 * Copyright 2021 - 2021 TEK2, Epitech
 */

#include "my_malloc.h"

extern block_t *end;
extern const size_t BLOCK_SIZE;
extern const size_t MIN_DATA_SIZE;

//printf("> %lu %lu \n", sizeof(block_t), BLOCK_SIZE);
//printf("> SIZE %lu / NEW SIZE %lu \n", new_size + BLOCK_SIZE, available_size);

void split_block(block_t *ptr, size_t new_size)
{
    size_t available_size = ptr->size - new_size;
    size_t new_block_size = highestPowerof2(available_size);
    block_t *new;
    
    //printf("> av %lu - nbs %lu - ns %lu \n", available_size, new_block_size, new_size);
    if (available_size - BLOCK_SIZE == 0 || available_size < MIN_CHUNK_SIZE)
        return;    
    new = (block_t *)(ptr->data + new_size);
    new->size = available_size - BLOCK_SIZE;
    new->next = ptr->next;
    if (new->next == NULL)
        end = new;
    else
        new->next->prev = new;
    new->next_free = NULL;
    new->prev = ptr;
    new->is_free = 1;
    ptr->size = new_size;
    ptr->next = new;
    if (available_size - new_block_size > 0) {
        split_block(new, (new_block_size - BLOCK_SIZE));
    }
}