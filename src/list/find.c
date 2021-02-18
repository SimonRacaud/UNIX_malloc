/*
** EPITECH PROJECT, 2021
** list
** File description:
** find.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

extern const size_t META_SIZE;

block_t *find_best_match(block_t **last, size_t size)
{
    block_t *ptr = list_head(NULL);
    block_t *best_ptr = NULL;

    while (ptr) {
        if (ptr->is_free && ptr->size >= size && best_ptr == NULL) {
            best_ptr = ptr;
        } else if (ptr->is_free && ptr->size >= size
            && best_ptr->size > ptr->size) {
            best_ptr = ptr;
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
    for (block_t *p = current; p; p = p->prev) {
        if (full_size && p && p->is_free) {
            *full_size += p->size + META_SIZE;
        }
        if (!p->prev || !p->prev->is_free) {
            return p;
        }
    }
    return current;
}