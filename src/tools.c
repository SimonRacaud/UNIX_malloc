/*
 * File: tools.c
 * Project: src
 * File Created: Thursday, 1st January 1970 1:00:00 am
 * Author: simon (simon.racaud@epitech.eu)
 * -----
 * Last Modified: Tuesday, 9th February 2021 9:23:45 pm
 * Modified By: simon (simon.racaud@epitech.eu>)
 * -----
 * Copyright 2021 - 2021 TEK2, Epitech
 */

#include "my_malloc.h"
#include <math.h>

size_t align_power2(size_t v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

size_t highestPowerof2(size_t n) 
{
    size_t p = (size_t)log2(n); 

    return (size_t)pow(2, p);
}

size_t highestMultipleofx(size_t n, size_t x)
{
    return (((n - (n % x)) / x) + 1) * x;
}