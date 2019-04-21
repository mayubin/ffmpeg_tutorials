//
// Created by wangrl on 19-4-21.
//

/**
 * Make a copy of a string in dynamically allocated memory.
 * Note: caller is responsible for checking whether the memory was
 * allocated! This allows the caller to respond to an error in
 * any way they wish.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *strdup(char const *string) {
    char *new_string;

    /**
     * Ask for enough memory to hold the string and its
     * terminating NUL byte.
     */
    new_string = malloc(strlen(string) + 1);

    /**
     * If we got the memory, copy the string.
     */
    if (new_string != NULL)
        strcpy(new_string, string);

    return new_string;
}

int main(int argc, char *argv[]) {
    
    char *src = "hello world!";
    
    char *dst = strdup(src);
    
    printf("%s\n", dst);
    
    free(dst);
}