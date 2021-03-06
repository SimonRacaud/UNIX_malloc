/*
** EPITECH PROJECT, 2021
** list
** File description:
** utility.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

extern const size_t META_SIZE;

block_t *get_meta_block(void *addr)
{
    return (block_t *)((char *)addr - META_SIZE);
}

bool is_valid_addr(void *data_addr)
{
    void *head = list_head(NULL);

    if (data_addr && head) {
        if (data_addr >= head && data_addr < sbrk(0)) {
            return (data_addr ==
                (void *)get_meta_block(data_addr) + META_SIZE);
        }
    }
    return false;
}