/*
** EPITECH PROJECT, 2021
** src
** File description:
** realloc.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

extern const size_t META_SIZE;

bool have_enough_space_next(block_t *ptr, size_t needed_space)
{
    size_t free_space = ptr->size + META_SIZE;

    for (block_t *p = ptr->next; p && p->is_free; p = p->next) {
        free_space += p->size + META_SIZE;
    }
    if (lower_pow2(free_space) - META_SIZE >= needed_space) {
        return true;
    }
    return false;
}

void *unchanged_size_alloc(block_t *ptr_meta, void *ptr, size_t size)
{
    if (ptr_meta->size + META_SIZE == highter_pow2(size + META_SIZE))
        return ptr;
    return NULL;
}

void *lower_size_split(block_t *ptr_meta, void *ptr, size_t size)
{
    if (lower_pow2(ptr_meta->size + META_SIZE - 1)
            > highter_pow2(size + META_SIZE)
        && is_block_splitable(ptr_meta->size + META_SIZE)) {
        split_block(ptr_meta, highter_pow2(size + META_SIZE) - META_SIZE);
        return ptr;
    }
    return NULL;
}

void *fusion_split(block_t *ptr_meta, void *ptr, size_t size)
{
    if (ptr_meta->next && ptr_meta->next->is_free
        && have_enough_space_next(ptr_meta, size)) {
        fusion_free_blocks(ptr_meta);
        if (ptr_meta->size < size) {
            fprintf(stderr, "WARNING: realloc fusion failed\n");
        }
        return ptr;
    }
    return NULL;
}
