/*
** EPITECH PROJECT, 2021
** list
** File description:
** find.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

extern const size_t BLOCK_SIZE;

block_t *find_best_match(block_t **last, size_t size)
{
    block_t *ptr = listHead(NULL);
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

block_t *get_first_prev_free_block(block_t *current, size_t *full_size)
{
    block_t *prev;

    if (full_size && current && current->is_free) {
        *full_size += current->size + BLOCK_SIZE;
    }
    if (current->prev && current->prev->is_free) {
        prev = get_first_prev_free_block(current->prev, full_size);
        if (prev == NULL) {
            return current;
        } else {
            return prev;
        }
    }
    return NULL;
}