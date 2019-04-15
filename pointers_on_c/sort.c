//
// Created by wangrl on 19-4-15.
//

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    int *array;
    int n_values;
    int i;

    /**
     * See how many numbers there will be
     */
    printf("How many values are there? ");
    if (scanf("%d", &n_values) != 1 || n_values <= 0) {
        printf("Illegal number of values.\n");
        exit(EXIT_FAILURE);
    }

    /**
     * Get memory to store them.
     */
    array = malloc(n_values * sizeof(int));
    if (array == NULL) {
        printf("Can't get memory for that many values.\n");
        exit(EXIT_FAILURE);
    }

    /**
     * Read the numbers.
     */
    for (i = 0; i < n_values; i++) {
        printf("? ");
        if (scanf("%d", array + i) != 1) {
            printf("Error reading value #%d\n", i);
            exit(EXIT_FAILURE);
        }
    }



    return 0;
}
