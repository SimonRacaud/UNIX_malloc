/*
** EPITECH PROJECT, 2021
** src
** File description:
** free.c, Thursday, 1st January 1970 1:00:00 am simon.racaud@epitech.eu
*/

#include "my_malloc.h"

//////////////////////////////////////////////
extern const size_t META_SIZE;
void my_debugDisplay() // TEMP
{
    setvbuf(stdout, NULL, _IONBF, 0);
    block_t *meta = (block_t *)listHead(NULL);
    size_t i = 0;
    
    printf("\nDEBUG %p\n", listHead(NULL));
    for (block_t *ptr = meta; ptr != NULL; ptr = ptr->next) {
        printf("\tBlock %lu: s(%lu) ss(%lu) is_free(%d)\n", i, ptr->size, ptr->size + META_SIZE, ptr->is_free);
        i++;
    }
}

void my_debugDisplayRev() // TEMP
{
    setvbuf(stdout, NULL, _IONBF, 0);
    block_t *meta = (block_t *)listEnd(NULL);
    size_t i = 0;
    
    printf("\nDEBUG %p\n", listEnd(NULL));
    for (block_t *ptr = meta; ptr != NULL; ptr = ptr->prev) {
        printf("\tBlock %lu: s(%lu) ss(%lu) is_free(%d)\n", i, ptr->size, ptr->size + META_SIZE, ptr->is_free);
        i++;
        //if (i > 20) break;
    }
}

void free(void *addr)
{
    block_t *ptr;
    block_t *end = listEnd(NULL);
    
    //setbuf(stdout, NULL);
    //printf("FREE\n");
    //my_debugDisplayRev();

    if (is_valid_addr(addr)) {
        ptr = get_meta_block(addr);
        ptr->is_free = 1;
        if (ptr->prev && ptr->prev->is_free) {
            ptr = fusion_free_blocks(get_first_prev_free_block(ptr, NULL));
        } else if (ptr->next && ptr->next->is_free) {
            ptr = fusion_free_blocks(ptr);
        }
        if (end && end->is_free) {
            try_move_break();
        }
    }
    //printf("END FREE\n");
   // my_debugDisplayRev();
    //printf("END FREE\n");
}
