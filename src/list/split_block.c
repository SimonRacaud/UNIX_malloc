/*
** EPITECH PROJECT, 2021
** list
** File description:
** split_block.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

extern const size_t BLOCK_SIZE;
extern const size_t MIN_DATA_SIZE;

void split_block(block_t *ptr, size_t ptr_new_size)
{
    size_t free_size = ptr->size - ptr_new_size;
    size_t new_block_futur_size = lower_pow2(free_size);
    block_t *new;
    
    if (free_size - BLOCK_SIZE <= 0 || free_size < MIN_CHUNK_SIZE)
        return;
    new = (block_t *)(ptr->data + ptr_new_size);
    new->size = free_size - BLOCK_SIZE;
    new->next = ptr->next;
    if (new->next == NULL)
        listEnd(new);
    else
        new->next->prev = new;
    new->prev = ptr;
    new->is_free = 1;
    ptr->size = ptr_new_size;
    ptr->next = new;
    if (free_size - new_block_futur_size >= MIN_CHUNK_SIZE) {
        split_block(new, (new_block_futur_size - BLOCK_SIZE));
    }
}

bool is_block_splitable(size_t free_size)
{
    size_t new_block_size = lower_pow2(free_size);

    if (free_size == new_block_size)
        return true;
    if (new_block_size < MIN_CHUNK_SIZE)
        return false;
    return is_block_splitable(free_size - new_block_size);
}

size_t nb_block_if_splitted(size_t free_size)
{
    size_t chunk_size = lower_pow2(free_size);

    if (free_size - chunk_size > 0) {
        return 1 + nb_block_if_splitted(free_size - chunk_size);
    }
    return 1;
}