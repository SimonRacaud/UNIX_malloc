/*
** EPITECH PROJECT, 2021
** src
** File description:
** free.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

void free(void *addr)
{
    block_t *ptr;
    block_t *end = listEnd(NULL);

    if (is_valid_addr(addr)) {
        ptr = get_meta_block(addr);
        ptr->is_free = 1;
        lock_memory();
        if (ptr->prev && ptr->prev->is_free) {
            ptr = fusion_free_blocks(get_first_prev_free_block(ptr, NULL));
        } else if (ptr->next && ptr->next->is_free) {
            ptr = fusion_free_blocks(ptr);
        }
        if (end && end->is_free) {
            try_move_break();
        }
        unlock_memory();
    }
}
