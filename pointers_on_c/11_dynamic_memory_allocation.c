//
// Created by wangrl on 19-4-15.
//

// 进行错误检查
#include <malloc.h>
#include <stdlib.h>

#define MALLOC(num, type) (type *)alloc((num) * sizeof(type))
extern void *alloc(size_t size);

int main(int argc, char *argv[]) {

    int *pi;
    pi = malloc(100);
    if (pi == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    pi = malloc(5 * sizeof(int));

    int *pi2, i;
    pi2 = pi;
    for (i = 0; i < 25; i++)
        *pi2++ = 0;

    for (i = 0; i < 25; i++)
        pi[i] = 0;

    int *new_memory;
    /**
     * Get space for a bunch of integers.
     */
    new_memory = MALLOC(25, int);

    /**
     * Get 10 integers
     */
    pi = malloc(10 * sizeof(int));

    /**
     * Free only the last 5 integers; keep the first 5.
     */
    free(pi + 5);


    return 0;
}

void *alloc(size_t size) {
    void *new_mem;
    /**
     * Ask for the requested memory, and check that we really got it.
     */
    new_mem = malloc(size);
    if (new_mem == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }
}