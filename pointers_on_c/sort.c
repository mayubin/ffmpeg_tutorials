//
// Created by wangrl on 19-4-15.
//

#include <stdlib.h>
#include <stdio.h>

/**
 * Function called by 'qsort' to compare integer values.
 */
int compare_integers(void const *a, void const *b) {
    register int const *pa = a;
    register int const *pb = b;
    return *pa > *pb ? 1 : (*pa < *pb ? -1 : 0);
}

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
    printf("? ");
    for (i = 0; i < n_values; i++) {
        if (scanf("%d", array + i) != 1) {
            printf("Error reading value #%d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    /**
     * Sort the values.
     */
    qsort(array, n_values, sizeof(int), compare_integers);

    /**
     * Print them out.
     */
    for (i = 0; i < n_values; i += 1)
        printf("%d\n", array[i]);

    /**
     * Free the memory and exit.
     */
    free(array);

    return EXIT_SUCCESS;
}
