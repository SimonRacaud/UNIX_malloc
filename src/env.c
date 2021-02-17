/*
** EPITECH PROJECT, 2021
** src
** File description:
** env.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

void *listHead(void *value)
{
    static void *head = NULL;

    if (value != NULL)
        head = value;
    return head;
}

void *listEnd(block_t *value)
{
    static block_t *end = NULL;

    if (value != NULL)
        end = value;
    return end;
}

size_t heap_align(void)
{
    static size_t align = 0;

    if (align == 0) {
        align = (getpagesize() * 2);
    }
    return align;
}

const size_t META_SIZE = sizeof(block_t);

const void *SBRK_ERROR = (void *)(-1);