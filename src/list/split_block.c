/*
** EPITECH PROJECT, 2021
** list
** File description:
** split_block.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

extern const size_t META_SIZE;

void split_block(block_t *ptr, size_t ptr_new_size)
{
    size_t free_size = (ptr->size < ptr_new_size) ? 0 : ptr->size - ptr_new_size;
    size_t new_block_futur_size = lower_pow2(free_size);
    block_t *new;
    
    //setvbuf(stdout, NULL, _IONBF, 0); // DEBUG
    if ((ssize_t)free_size - (ssize_t)META_SIZE <= 0
    || free_size < MIN_CHUNK_SIZE)
        return;
    new = (block_t *)(DATA(ptr) + ptr_new_size);
    new->size = free_size - META_SIZE;
    new->next = ptr->next;
    //printf("SPLIT f %lu / pns %lu / ps %lu \n", free_size, ptr_new_size, ptr->size); // DEBUG
    //printf("SPLIT ptr s %lu / next s %lu \n", new->size + META_SIZE, (new_block_futur_size)); // DEBUG
    if (new->next == NULL)
        listEnd(new);
    else
        new->next->prev = new;
    new->prev = ptr;
    new->is_free = 1;
    ptr->size = ptr_new_size;
    ptr->next = new;
    if (free_size - new_block_futur_size >= MIN_CHUNK_SIZE) {
        split_block(new, (new_block_futur_size - META_SIZE));
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