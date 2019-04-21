//
// Created by wangrl on 19-4-11.
//

/**
 * This program reads input lines from standard input and prints
 * each input file, followed by just some portions of the line, to
 * the standard output.
 *
 * The first input is a lint of column numbers, which ends with a
 * negative number. The column numbers are paired and specify
 * ranges of columns from the input line that are to be printed.
 * For example, 0 3 10 12 -1 indicates that only columns 0 through 3
 * and columns 10 through 12 will be printed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS    20      /* max # of columns to process */
#define MAX_INPUT   1000    /* max len of input & output lines */

/**
 * Read the list of column numbers, ignoring any beyond the specified maximum.
 */
int read_column_numbers(int columns[], int max) {
    int num = 0;
    int ch;
    /**
     * Get the numbers, stopping at eof or when a number is < 0.
     */
    while (num < max && scanf("%d", &columns[num]) == 1
            && columns[num] >= 0)
        num += 1;

    /**
     * Make sure we have an even number of inputs, as they are supported to be paired.
     */
    if (num % 2 != 0) {
        puts("Last column number is not paired.");
        exit(EXIT_FAILURE);
    }

    /**
     * Discard the rest of the line that contained the final numbers.
     */
    while ((ch = getchar()) != EOF && ch != '\n')
        ;

    return num;
}

/**
 * Process a line of input by concatenating the characters from
 * the indicated columns. The output lne is the NUL terminated.
 */
int rearrange(char *output, char const *input,
        int n_columns, int const columns[]) {
    int col;            /* subscript for columns array */
    int output_col;     /* output column counter */
    int len;            /* length of input line */

    len = strlen(input);
    output_col = 0;

    /**
     * Process each pair of column numbers.
     */
    for (col = 0; col < n_columns; col += 2) {
        int nchars = columns[col + 1] - columns[col] + 1;

        /**
         * If the input line isn't this long or the output array is full, we're done
         */
        if (columns[col] >= len || output_col == MAX_INPUT - 1)
            break;

        /**
         * If there isn't room in the output array, only copy what will fit.
         */
        if (output_col + nchars > MAX_INPUT - 1)
            nchars = MAX_INPUT - output_col - 1;

        /**
         * Copy the relevant data.
         */
        strncpy(output + output_col, input + columns[col], nchars);
        output_col += nchars;
    }
    output[output_col] = '\0';
}

int main(int argc, char *argv[]) {

    int n_columns;              /* # of columns to process */
    int columns[MAX_COLS];      /* the columns to process */
    char input[MAX_INPUT];      /* array for input file */
    char output[MAX_INPUT];     /* array for output file */

    /**
     * Read the list of column numbers
     */
    n_columns = read_column_numbers(columns, MAX_COLS);

    /**
     * Read, process and print the remaining lines of input
     */
    while (fgets(input, MAX_INPUT, stdin) != NULL) {
        printf("Original input: %s", input);
        rearrange(output, input, n_columns, columns);
        printf("Rearranged line: %s", output);
    }

    return EXIT_SUCCESS;
}

