/*
** EPITECH PROJECT, 2021
** src
** File description:
** math.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"
#include <math.h>

size_t highter_pow2(size_t v)
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

size_t lower_pow2(size_t n) 
{
    size_t p = (size_t)log2(n); 

    return (size_t)pow(2, p);
}

size_t highest_multiple_of_x(size_t n, size_t x)
{
    return (((n - (n % x)) / x) + 1) * x;
}

size_t lower_multiple_of_x(size_t nb, size_t x)
{
    size_t coef = 1;

    while (x * coef <= nb) {
        coef++;
    }
    return --coef * x;
}