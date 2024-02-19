#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))

#define PADDED_SIZE(x) ((x) + GET_PAD(x))
#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))
#define padded_struct_block_size = PADDED_SIZE(sizeof(struct block));
struct block *head = NULL;  // Head of the list, empty

struct block {
    int size;            // Size in bytes
    int in_use;          // Boolean
    struct block *next;
};

void *myalloc(int size){
    if(head==NULL){
        void *heap = mmap(NULL, 1024, PROT_READ|PROT_WRITE,
                MAP_ANON|MAP_PRIVATE, -1, 0);
        head=heap;
        int data_size = 1024 - PADDED_SIZE(sizeof(struct block));
        head->size = data_size;
        head->in_use = 0;
    }
    return head;
}

//void myfree(void *p);

int main(){

}