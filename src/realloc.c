/*
** EPITECH PROJECT, 2021
** src
** File description:
** realloc.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include <string.h>
#include "my_malloc.h"

void *realloc(void *ptr, size_t size)
{
    void *new;
    block_t *ptr_meta;
    size_t *copy_size;

    if (!ptr) {
        return malloc(size);
    } else if (ptr && size == 0) {
        free(ptr);
        return NULL;
    }
    new = malloc(size);
    if (new == NULL)
        return NULL;
    ptr_meta = get_meta_block(ptr);
    copy_size = (ptr_meta->size > size) ? size : ptr_meta->size;
    new = memcpy(new, ptr, copy_size);
    free(ptr);
    return new;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    size_t total_size = nmemb * size;

    if (!nmemb || !size || (nmemb != 0 && total_size / nmemb != size)) {
        return NULL;
    }
    return realloc(ptr, total_size);
}
