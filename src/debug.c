/*
** EPITECH PROJECT, 2021
** src
** File description:
** debug.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

extern const size_t META_SIZE;

void my_debug_display(void)
{
    block_t *meta = (block_t *) list_head(NULL);
    size_t i = 0;

    setvbuf(stdout, NULL, _IONBF, 0);
    printf("\nDEBUG %p\n", list_head(NULL));
    for (block_t *ptr = meta; ptr != NULL; ptr = ptr->next) {
        printf("\tBlock %lu: s(%lu) ss(%lu) is_free(%d)\n", i, ptr->size,
            ptr->size + META_SIZE, ptr->is_free);
        i++;
    }
}

void my_debug_display_rev(void)
{
    block_t *meta = (block_t *) list_end(NULL);
    size_t i = 0;

    setvbuf(stdout, NULL, _IONBF, 0);
    printf("\nDEBUG %p\n", list_end(NULL));
    for (block_t *ptr = meta; ptr != NULL; ptr = ptr->prev) {
        printf("\tBlock %lu: s(%lu) ss(%lu) is_free(%d)\n", i, ptr->size,
            ptr->size + META_SIZE, ptr->is_free);
        i++;
    }
}

void check_break_align(void)
{
    block_t *meta = (block_t *) list_head(NULL);
    size_t size = 0;

    setvbuf(stdout, NULL, _IONBF, 0);
    for (block_t *ptr = meta; ptr != NULL; ptr = ptr->next) {
        size += ptr->size + META_SIZE;
    }
    printf("DEBUG ALIGN : s %lu ha %lu |  %lu \n", size, heap_align(),
        size % heap_align());
    printf("> %lu / %lu \n",
        (size_t)(sbrk(0) - list_head(NULL)) % getpagesize(),
        (size_t)(sbrk(0) - list_head(NULL)));
}