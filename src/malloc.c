/*
** EPITECH PROJECT, 2021
** src
** File description:
** malloc.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

extern const size_t BLOCK_SIZE;

void *malloc(size_t size)
{
    block_t *ptr;
    size_t s = highter_pow2(size + BLOCK_SIZE) - BLOCK_SIZE;

    if (size == 0)
        return NULL;
    if (listHead(NULL)) {
        ptr = add_block(s);
    } else {
        ptr = extend_heap(NULL, s);
        if (!ptr)
            return NULL;
        listHead(ptr);
    }
    return (ptr->data);
}
