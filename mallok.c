/*
 *TCSS 333
 *HW7
 *@Author: Yunhan Tu
 *@version 3/3/18
 */

#include "mallok.h"
#include <stdio.h>

static void *heap;
static List *list;
static int sizeAvail = 0;


void create_pool(int size) {
    if(heap == NULL && list == NULL) {
        heap = malloc(size * sizeof(int));
        list = malloc(sizeof(Block));
        list->address = heap;
        list->isfree = 1;
        list->size = size;
        list->next = NULL;
        sizeAvail = size;
    }
   
}

void *my_malloc(int size) {
    
    void *returnadd = NULL;
    if(heap != NULL ) {

        Block *current = list;
    //printf("asdsad the address of heap %p \n",list->address );
    //printf("abc the address of current  %p \n",current->address );
    //printf("abc the address of current next %p \n",current->next->address );
        while (current != NULL && (current->isfree == 0 || current->size < size)) {
             // printf("current size%d %d %d\n",current->size, current->isfree, sizeAvail);
            current = current->next; 
            // printf("abc the address of current next %p \n",current->address );
        }
    // printf("asdsad the address of heap %p \n",list->address );
    // if(list != NULL ) {
        // printf("free malloc%d %d\n",current->size, sizeAvail);current != NUL

        if(current != NULL) {
            // printf("current size2%d %d %d\n\n",current->size, current->isfree, sizeAvail);
            if (current->isfree == 1) {
                 // printf("current malloc%d %d\n",current->size, sizeAvail);
                if (sizeAvail >= size) {
                    // sizeAvail = current->size;
                    // current->size = size;
                    // current->isfree = 0;
                    // printf("%d\n",current->size);
                    if (current->size  - size > 0) {
                        sizeAvail = sizeAvail - size;
                        // printf("%d %d\n",current->size, sizeAvail);
                        Block *newBlock = malloc(sizeof(Block));
                        newBlock->isfree = 1;
                        newBlock->size = current->size  - size;
                        newBlock->address = current->address + size;
                        newBlock->next = current->next;
                        current->size = size;
                        current->isfree = 0;
                        current->next = newBlock;
                        // cprintf("asdsad the address of block %p \n",newBlock->address ); 
   
                    }
                    else if(current->size - size == 0) {
                        current->isfree = 0;
                        sizeAvail = sizeAvail - size;
                        // printf("mei la %d %d\n",current->size, sizeAvail);
                    }
                   
                } 
                else {
                    printf("No enough space \n");
                    return NULL; 
                }
                // printf("use malloc%d %d\n",current->size, sizeAvail);
                returnadd = current->address;
            }
            else {
                printf("no place avaliable\n");
            }
        }
    }
    return returnadd;
}


void my_free(void *block) {
    Block *current = list;
    Block *back = NULL;
    Block *front = NULL;
    int flag = 0;
    while (current->next != NULL && current->address != block) {
        front = current;
        current = current->next;
    }
    if(current->next == NULL) {
        if (current->address != block)
        {
            flag = 1;
        }
    }
    if (current != NULL && flag == 0) {
        current->isfree = 1;
        sizeAvail += current->size;
        // printf("free current%d %d\n",current->size, sizeAvail);
        if (current->next != NULL && current->next->isfree == 1) {
             // printf(" currentnext is free %d \n",current->next->isfree);
            back = current->next; 
            current->size += back->size;
            // printf("free back%d %d\n",current->size, sizeAvail);
            current->next = back->next;
            free(back);
            back = NULL;
        }
        if (front != NULL && front->isfree == 1) {
            front->size += current->size;
            // printf(" current front is free %d \n",front->isfree);
            // printf("free front %d %d\n", front->size, sizeAvail);
            front->next = current->next;
            free(current);
            current = NULL;
        }
        
    }
}


void free_pool() {
    freeList(list);
    list = NULL;
    free(heap);
    heap = NULL;
    sizeAvail = 0;
}

void freeList(Block *list) {
    if (list) {
        freeList(list->next);
        free(list);
        list = NULL;
    }
}
