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

const size_t MIN_DATA_SIZE = 1;

const size_t BLOCK_SIZE = sizeof(size_t) + (sizeof(block_t *) * 2)
    + sizeof(__uint8_t);

const void *SBRK_ERROR = (void *)(-1);