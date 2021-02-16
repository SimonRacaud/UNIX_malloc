/*
** EPITECH PROJECT, 2021
** list
** File description:
** fusion.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

extern const size_t BLOCK_SIZE;

static block_t *process_fusion(block_t *beg, size_t free_blocks_full_size,
size_t nb_splitted_block, block_t *last_free_block)
{
    beg->size = free_blocks_full_size - BLOCK_SIZE;
    beg->next = last_free_block->next;
    if (beg->next) {
        beg->next->prev = beg;
    }
    if (nb_splitted_block > 1) {
        split_block(beg, lower_pow2(beg->size + BLOCK_SIZE) - BLOCK_SIZE);
    }
    return beg;
}

block_t *fusion_free_blocks(block_t *beg)
{
    size_t nb_free_block = 1;
    size_t free_blocks_full_size = (beg->size + BLOCK_SIZE);
    block_t *last_free_block;
    size_t nb_splitted_block;

    for (block_t *ptr = beg->next; ptr != NULL; ptr = ptr->next) {
        if (!ptr->is_free)
            break;
        nb_free_block++;
        free_blocks_full_size += ptr->size + BLOCK_SIZE;
        last_free_block = ptr;
    }
    if (is_block_splitable(free_blocks_full_size) == false)
        return beg;
    nb_splitted_block = nb_block_if_splitted(free_blocks_full_size);
    if (nb_splitted_block >= nb_free_block) {
        return beg;
    }
    return process_fusion(beg, free_blocks_full_size, nb_splitted_block,
        last_free_block);
}