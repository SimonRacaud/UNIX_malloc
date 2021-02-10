/*
 * File: calloc.c
 * Project: src
 * File Created: Thursday, 1st January 1970 1:00:00 am
 * Author: simon (simon.racaud@epitech.eu)
 * -----
 * Last Modified: Tuesday, 9th February 2021 9:55:18 pm
 * Modified By: simon (simon.racaud@epitech.eu>)
 * -----
 * Copyright 2021 - 2021 TEK2, Epitech
 */

#include "my_malloc.h"

void *calloc(size_t number, size_t size)
{
    size_t *new = malloc(number * size);

    if (new) {
        for (size_t i = 0; i < (number * size); i++) {
            new[i] = 0;
        }
    }
    return new;
}