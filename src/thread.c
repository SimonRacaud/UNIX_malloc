/*
** EPITECH PROJECT, 2021
** src
** File description:
** thread.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include <pthread.h>

static pthread_mutex_t *get_lock(void)
{
    static pthread_mutex_t my_lock;

    return &my_lock;
}

void lock_memory(void)
{
    pthread_mutex_lock(get_lock());
}

void unlock_memory(void)
{
    pthread_mutex_unlock(get_lock());
}