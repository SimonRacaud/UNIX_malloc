/*
** EPITECH PROJECT, 2021
** src
** File description:
** malloc.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

extern const size_t META_SIZE;

void *malloc(size_t size)
{
    block_t *ptr;
    size_t s = highter_pow2(size + META_SIZE) - META_SIZE;

    lock_memory();
    if (list_head(NULL)) {
        ptr = add_block(s);
    } else {
        ptr = extend_heap(NULL, s);
        if (!ptr)
            return NULL;
        list_head(ptr);
    }
    unlock_memory();
    if (ptr == NULL)
        return NULL;
    return (void *) ptr + META_SIZE;
}
