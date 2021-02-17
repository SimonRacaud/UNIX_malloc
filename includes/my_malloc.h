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
#include <string.h>

typedef struct block
{
    size_t size;            
    struct block *next;     
    struct block *prev;     
    __uint8_t is_free;      
    char data[1];           
} __attribute__((packed)) block_t;

#define MIN_CHUNK_SIZE highter_pow2(BLOCK_SIZE + MIN_DATA_SIZE)

// MATH
size_t highter_pow2(size_t v);
size_t lower_pow2(size_t n);
size_t highest_multiple_of_x(size_t n, size_t x);
size_t lower_multiple_of_x(size_t nb, size_t x);

// List
void *listHead(void *value);
void *listEnd(block_t *value);
size_t heap_align(void);

block_t *add_block(size_t size);
block_t *extend_heap(block_t *last, size_t size);

block_t *find_best_match(block_t **last, size_t size);
block_t *get_first_prev_free_block(block_t *current, size_t *full_size);

void split_block(block_t *ptr, size_t s);
bool is_block_splitable(size_t free_size);
size_t nb_block_if_splitted(size_t free_size);

block_t *get_meta_block(void *addr);
bool is_valid_addr(void *data_addr);

block_t *fusion_free_blocks(block_t *beg);

void try_move_break(void);

// C/MALLOC
void *malloc(size_t size);
void *calloc(size_t number, size_t size);

// FREE
void free(void *addr);

// REALLOC
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

/////// DEBUG
void my_debugDisplay();
void my_debugDisplayRev(); // TEMP

#endif // !H_MALLOC