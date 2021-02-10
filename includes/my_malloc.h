/*
 * File: malloc.h
 * Project: includes
 * File Created: Thursday, 1st January 1970 1:00:00 am
 * Author: simon (simon.racaud@epitech.eu)
 * -----
 * Last Modified: Tuesday, 9th February 2021 9:12:11 pm
 * Modified By: simon (simon.racaud@epitech.eu>)
 * -----
 * Copyright 2021 - 2021 TEK2, Epitech
 */

#ifndef H_MALLOC
#define H_MALLOC

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct block
{
    size_t size;
    struct block *next;
    struct block *prev;
    __uint8_t is_free;
    char data[1];
} block_t;

#define HEAP_ALIGN (getpagesize() * 2)
#define MIN_CHUNK_SIZE align_power2(BLOCK_SIZE + MIN_DATA_SIZE)
#define IS_COMPLIANT_CHUNK(c) (c->is_free && c->size >= size)

// TOOLS
size_t align_power2(size_t v);
size_t highestPowerof2(size_t n);
size_t highestMultipleofx(size_t n, size_t x);

// MALLOC
block_t *find_best_match(block_t **last, size_t size);
block_t *extend_heap(block_t *last, size_t s);
void split_block(block_t *ptr, size_t s);
void *malloc(size_t size);

// FREE
void free(void *addr);
block_t *get_meta_block(void *addr);
bool is_valid_addr(void *data_addr);

// REALLOC
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

#endif // !H_MALLOC