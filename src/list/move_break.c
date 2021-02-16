/*
** EPITECH PROJECT, 2021
** list
** File description:
** move_break_and_split.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

extern const size_t BLOCK_SIZE;
extern const size_t MIN_DATA_SIZE;

static bool move_break_and_split(size_t full_size, block_t *ptr)
{
    size_t free_size = full_size - lower_multiple_of_x(full_size, HEAP_ALIGN);
    size_t free_size_pow2 = highter_pow2(free_size);

    if (free_size < MIN_CHUNK_SIZE || (free_size_pow2 != free_size
        && !is_block_splitable(free_size)))
        return false;
    //printf("BREAK: full(%lu) \n", full_size);
    //printf("BREAK: av(%lu) av2(%lu) / %d \n", free_size, free_size_pow2, is_block_splitable(free_size));
    ptr->size = free_size - BLOCK_SIZE;
    ptr->next = NULL;
    if (free_size_pow2 != free_size) {
        split_block(ptr, lower_pow2(free_size) - BLOCK_SIZE);
    }
    brk(ptr + (ptr->size + BLOCK_SIZE));
    listEnd(ptr);
    //printf("SPLIT & BREAK %lu / full %lu \n", ptr->size, full_size);
    //printf("FREE E %lu \n", (full_size - HEAP_ALIGN));
    //printf("XXX %lu \n", ptr->size);
    return true;
}

static void move_break(block_t *ptr)
{
    block_t *last = ptr->prev;

    ptr->prev->next = NULL;
    brk(ptr);
    listEnd(last);
}

void try_move_break(void)
{
    size_t free_size = 0;
    block_t *first_free_block = get_first_prev_free_block(listEnd(NULL), &free_size);

    if (!first_free_block || free_size < HEAP_ALIGN)
        return;
    for (block_t *ptr = first_free_block; ptr && ptr->is_free;
    ptr = ptr->next) {
        if (free_size == HEAP_ALIGN) {
            move_break(ptr);
            break;
        } else if (free_size > HEAP_ALIGN
        && move_break_and_split(free_size, ptr)) {
            break;
        }
        free_size -= ptr->size + BLOCK_SIZE;
    }
}