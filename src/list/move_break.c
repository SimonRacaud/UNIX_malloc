/*
** EPITECH PROJECT, 2021
** list
** File description:
** move_break.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

extern const size_t META_SIZE;

static bool move_break_and_split(size_t full_size, block_t *ptr)
{
    ssize_t free_size =
        full_size - lower_multiple_of_x(full_size, heap_align());
    size_t free_size_pow2 = highter_pow2(free_size);

    if (free_size < (ssize_t) MIN_CHUNK_SIZE
        || (free_size_pow2 != (size_t) free_size
            && !is_block_splitable(free_size)))
        return false;
    ptr->size = free_size - META_SIZE;
    ptr->next = NULL;
    listEnd(ptr);
    brk((void *) ptr + free_size);
    if (free_size_pow2 != (size_t) free_size) {
        split_block(ptr, lower_pow2(free_size) - META_SIZE);
    }
    return true;
}

static void move_break(block_t *ptr)
{
    block_t *last = ptr->prev;

    if (ptr->prev)
        ptr->prev->next = NULL;
    brk(ptr);
    listEnd(last);
}

void try_move_break(void)
{
    size_t free_size = 0;
    block_t *first_free_block =
        get_first_prev_free_block(listEnd(NULL), &free_size);

    if (!first_free_block || free_size < heap_align())
        return;
    for (block_t *ptr = first_free_block; ptr && ptr->is_free && ptr->prev;
        ptr = ptr->next) {
        if (free_size == heap_align()) {
            move_break(ptr);
            break;
        } else if (free_size > heap_align()
            && move_break_and_split(free_size, ptr)) {
            break;
        }
        free_size -= ptr->size + META_SIZE;
    }
}
