/*
** EPITECH PROJECT, 2021
** list
** File description:
** move_break_and_split.c, Thursday, 1st January 1970 1:00:00 am
*simon.racaud@epitech.eu
*/

#include "my_malloc.h"

extern const size_t META_SIZE;

static bool move_break_and_split(size_t full_size, block_t *ptr)
{
    ssize_t free_size =
        full_size - lower_multiple_of_x(full_size, heap_align());
    size_t free_size_pow2 = highter_pow2(free_size);

    // printf("%lu / %lu \n", lower_multiple_of_x(full_size, heap_align()),
    // heap_align());
    if (free_size < (ssize_t) MIN_CHUNK_SIZE
        || (free_size_pow2 != (size_t) free_size
            && !is_block_splitable(free_size)))
        return false;
    // printf("ptr->size =%lu\n", ptr->size);
    // printf("BREAK: full(%lu) \n", full_size);
    // printf("BREAK: lw(%lu) \n", lower_multiple_of_x(full_size,
    // heap_align())); printf("BREAK: move size (%lu) \n", full_size -
    // free_size); printf("BREAK: free(%lu) free2(%lu) / %d \n", free_size,
    // free_size_pow2,
    //     is_block_splitable(free_size));
    ptr->size = free_size - META_SIZE;
    ptr->next = NULL;
    listEnd(ptr);
    brk((void *) ptr + free_size);
    if (free_size_pow2 != (size_t) free_size) {
        // printf("f %lu / free_size: %lu + full_size: %lu \n",
        // lower_pow2(free_size), free_size, full_size);
        split_block(ptr, lower_pow2(free_size) - META_SIZE);
    }
    // sbrk(-(full_size - free_size));
    // printf("SPLIT & BREAK %lu / full %lu \n", ptr->size, full_size);
    // printf("FREE E %lu \n", (full_size - heap_align()));
    // printf("XXX %lu \n", ptr->size);
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

    // setvbuf(stdout, NULL, _IONBF, 0); // DEBUG
    // if (first_free_block)
    //     printf("MOVE %lu \n", first_free_block->size + META_SIZE);

    if (!first_free_block || free_size < heap_align())
        return;
    // printf("START MOVE BREAK %lu  \n", free_size);
    // printf("%lu \n", heap_align());
    // check_break_align(); // DEBUG
    // my_debugDisplay();   // DEBUG
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
    // check_break_align(); // DEBUG
    // my_debugDisplay();   // DEBUG
    // printf("END MOVE BREAK %lu  \n", free_size);
}
