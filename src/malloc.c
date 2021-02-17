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

    //setvbuf(stdout, NULL, _IONBF, 0);
    //printf("MALLOC %lu\n", size);
    //my_debugDisplay();
    if (listHead(NULL)) {
        ptr = add_block(s);
    } else {
        ptr = extend_heap(NULL, s);
        if (!ptr)
            return NULL;
        listHead(ptr);
    }
    //printf("END MALLOC ptr->size = %lu\n", ptr ? ptr->size : 0);
    //my_debugDisplay();
    if (ptr == NULL)
        return NULL;
    return (void *)ptr + META_SIZE;
}
