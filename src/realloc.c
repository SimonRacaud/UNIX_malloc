/*
** EPITECH PROJECT, 2021
** src
** File description:
** realloc.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include <string.h>
#include "my_malloc.h"

static void *realloc_optimised_methods(
    block_t *ptr_meta, size_t size, void *ptr)
{
    void *new;

    new = unchanged_size_alloc(ptr_meta, ptr, size);
    if (new)
        return new;
    new = lower_size_split(ptr_meta, ptr, size);
    if (new)
        return new;
    new = fusion_split(ptr_meta, ptr, size);
    if (new)
        return new;
    return NULL;
}

static void *realloc_move_to_new_block(
    block_t *ptr_meta, size_t size, void *ptr)
{
    void *new = NULL;
    size_t copy_size;

    new = malloc(size);
    if (new == NULL)
        return NULL;
    copy_size = (size < ptr_meta->size) ? size : ptr_meta->size;
    new = memcpy(new, ptr, copy_size);
    free(ptr);
    return new;
}

void *realloc(void *ptr, size_t size)
{
    block_t *ptr_meta;
    void *ret;

    if (!ptr) {
        ptr = malloc(size);
        return ptr;
    } else if (ptr && size == 0) {
        free(ptr);
        return NULL;
    }
    if (!is_valid_addr(ptr))
        return NULL;
    ptr_meta = get_meta_block(ptr);
    ret = realloc_optimised_methods(ptr_meta, size, ptr);
    if (ret)
        return ret;
    return realloc_move_to_new_block(ptr_meta, size, ptr);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    size_t total_size = nmemb * size;

    if (!nmemb || !size || (nmemb != 0 && total_size / nmemb != size)) {
        return NULL;
    }
    return realloc(ptr, total_size);
}
