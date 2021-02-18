/*
** EPITECH PROJECT, 2021
** src
** File description:
** calloc.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

void *calloc(size_t number, size_t size)
{
    size_t *new;
    size_t total_size = number * size;

    if (!number || !size || (number != 0 && total_size / number != size)) {
        return NULL;
    }
    new = malloc(total_size);
    if (new) {
        memset(new, 0, total_size);
    }
    return new;
}