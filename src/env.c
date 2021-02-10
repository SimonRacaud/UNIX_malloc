/*
 * File: env.h
 * Project: includes
 * File Created: Thursday, 1st January 1970 1:00:00 am
 * Author: simon (simon.racaud@epitech.eu)
 * -----
 * Last Modified: Wednesday, 10th February 2021 10:09:56 am
 * Modified By: simon (simon.racaud@epitech.eu>)
 * -----
 * Copyright 2021 - 2021 TEK2, Epitech
 */

#include "my_malloc.h"

void *base = NULL;

const size_t MIN_DATA_SIZE = 1;

const size_t BLOCK_SIZE = sizeof(size_t) + (sizeof(block_t *) * 2)
    + sizeof(__uint8_t);

const void *SBRK_ERROR = (void *)(-1);