
/*
 *TCSS 333
 *HW7
 *@Author: Yunhan Tu
 *@version 3/3/18
 */

#ifndef mallok_h
#define mallok_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct block {
    void *address;
    int size;
    int isfree;
    struct block *next;
} Block, List;
void create_pool(int size);
void *my_malloc(int size);
void my_free(void *block);
void free_pool();
void freeList(List *list);
#endif 
