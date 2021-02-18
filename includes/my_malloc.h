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

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct block {
    size_t size;
    struct block *next;
    struct block *prev;
    __uint8_t is_free;
} block_t;

#define MIN_CHUNK_SIZE META_SIZE
#define DATA(meta_ptr) (void *) meta_ptr + META_SIZE
#define SAFE_SUB(a, b) a < b ? 0 : a - b

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
bool have_enough_space_next(block_t *ptr, size_t needed_space);
void *unchanged_size_alloc(block_t *ptr_meta, void *ptr, size_t size);
void *lower_size_split(block_t *ptr_meta, void *ptr, size_t size);
void *fusion_split(block_t *ptr_meta, void *ptr, size_t size);

void *reallocarray(void *ptr, size_t nmemb, size_t size);

// THREAD
void lock_memory(void);
void unlock_memory(void);

// DEBUG
void my_debugDisplay();
void my_debugDisplayRev();
void check_break_align();

#endif // !H_MALLOC