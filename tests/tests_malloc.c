/*
** EPITECH PROJECT, 2021
** Unit_Test_Criterion
** File description:
** Test File
*/

#include <mcheck.h>
#include <criterion/criterion.h>
#include "my_malloc.h"

Test(malloc_free, t01)
{
    char *str = malloc(4);

    strcpy(str, "abc");
    cr_assert_str_eq(str, "abc");
    free(str);
}

Test(realloc, t02)
{
    char *str = malloc(4);

    str = realloc(str, 6);
    strcpy(str, "abcde");
    cr_assert_str_eq(str, "abcde");
    free(str);
}

Test(realloc, t03)
{
    char *str = realloc(NULL, 6);

    strcpy(str, "abcde");
    cr_assert_str_eq(str, "abcde");
    free(str);
}

Test(realloc, t04)
{
    char *str = malloc(4);

    str = realloc(str, 0);
}

Test(calloc, t05)
{
    char *str = calloc(2, 2);

    cr_assert_arr_eq(str, "\0\0\0", 4);
}

Test(realloc_array, t06)
{
    char *str = reallocarray(NULL, 2, 2);
    void *ret;

    strcpy(str, "abc");
    cr_assert_str_eq(str, "abc");
    ret = reallocarray(str, 0, 0);
}