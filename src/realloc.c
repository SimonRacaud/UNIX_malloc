/*
 * File: realloc.c
 * Project: src
 * File Created: Thursday, 1st January 1970 1:00:00 am
 * Author: simon (simon.racaud@epitech.eu)
 * -----
 * Last Modified: Tuesday, 9th February 2021 10:00:46 pm
 * Modified By: simon (simon.racaud@epitech.eu>)
 * -----
 * Copyright 2021 - 2021 TEK2, Epitech
 */

#include <string.h>
#include "my_malloc.h"

void *realloc(void *ptr, size_t size)
{
    if (!ptr) {
        return malloc(size);
    } else if (ptr && size == 0) {
        free(ptr);
        return NULL;
    }
    void *new = malloc(size);
    block_t *ptr_meta = get_meta_block(ptr);

    if (new == NULL)
        return NULL;
    new = memcpy(new, ptr, ptr_meta->size);
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
