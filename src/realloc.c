/*
** EPITECH PROJECT, 2021
** src
** File description:
** realloc.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include <string.h>
#include "my_malloc.h"

extern const size_t META_SIZE;

static bool have_enough_space_next(block_t *ptr, size_t needed_space)
{
    size_t free_space = ptr->size + META_SIZE;
    for (block_t *p = ptr->next; p && p->is_free; p = p->next) {
        free_space += p->size + META_SIZE;
    }
    //fprintf(stderr, "> %lu %lu \n", free_space, lower_pow2(free_space));
    if (lower_pow2(free_space) - META_SIZE >= needed_space) {
        return true;
    }
    return false;
}

static void *unchanged_size_alloc(block_t *ptr_meta, void *ptr, size_t size)
{
    if (ptr_meta->size + META_SIZE == highter_pow2(size + META_SIZE))
        return ptr;
    return NULL;
}

static void *lower_size_split(block_t *ptr_meta, void *ptr, size_t size)
{
    if (lower_pow2(ptr_meta->size + META_SIZE - 1) > highter_pow2(size + META_SIZE)
    && is_block_splitable(ptr_meta->size + META_SIZE)) {
        //my_debugDisplayRev();
        //printf("## %lu %lu \n", highter_pow2(size + META_SIZE), lower_pow2(ptr_meta->size + META_SIZE - 1) );

        split_block(ptr_meta, highter_pow2(size + META_SIZE) - META_SIZE);
        return ptr;
    }
    return NULL;
}

static void *fusion_split(block_t *ptr_meta, void *ptr, size_t size)
{
    if (ptr_meta->next && ptr_meta->next->is_free
    && have_enough_space_next(ptr_meta, size)) {
        fusion_free_blocks(ptr_meta);
        //my_debugDisplay();
        if (ptr_meta->size < size) {
            fprintf(stderr, "WARNING: realloc fusion failed\n");
            //exit(1);
        }
        return ptr;
    }
    return NULL;
}

void *realloc(void *ptr, size_t size)
{
    void *new = NULL;
    block_t *ptr_meta;
    size_t copy_size;

    //setvbuf(stdout, NULL, _IONBF, 0);
    //printf("REALLOC %lu %p \n", size, ptr); // DEBUG
    if (!ptr) {
        //printf("X \n");
        //my_debugDisplay();
        ptr = malloc(size);
        return ptr;
        //exit(1);
    } else if (ptr && size == 0) {
        free(ptr);
    //printf("REALLOC 1 \n"); // DEBUG
        return NULL;
    }
    
    if (!is_valid_addr(ptr))
       return NULL;
    //printf("REALLOC 2 \n"); // DEBUG

    ptr_meta = get_meta_block(ptr);
    // size unchanged
    new = unchanged_size_alloc(ptr_meta, ptr, size);
    if (new)
        return new;
    //printf("REALLOC 3 %lu  / %lu \n", size, ptr_meta->size); // DEBUG
    
    //my_debugDisplay();
    //my_debugDisplayRev();
    // size lower + splittable
    new = lower_size_split(ptr_meta, ptr, size);
   // printf("REALLOC 3.5 %lu  / %lu \n", size, ptr_meta->size); // DEBUG

    if (new)
        return new;
    //printf("REALLOC 4 \n"); // DEBUG
    
    // have next free blocks => merge
    new = fusion_split(ptr_meta, ptr, size);
    if (new)
        return new;
    //printf("REALLOC 5 \n"); // DEBUG
    
    // new alloc + copy
    new = malloc(size);
    if (new == NULL)
        return NULL;
    copy_size = (size < ptr_meta->size) ? size : ptr_meta->size;
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
