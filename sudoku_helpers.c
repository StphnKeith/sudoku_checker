#include <stdio.h>
#include <stdlib.h>

// Return n^x, assuming n >= 1, x >= 0
int power(int n, int x) {
    int accumulator = 1;
    int i = 0;
    while (i < x) {
        accumulator = accumulator * n;
        i++;
    }
    return accumulator;
}

/* Each of the n elements of array elements, is the address of an
 * array of n integers.
 * Return 0 if every integer is between 1 and n^2 and all
 * n^2 integers are unique, otherwise return 1.
 */
int check_group(int **elements, int n) {
    // An array of 1s and 0s where each index i holds a 1 if i+1 has
    // been found in the group, 0 if it has not
    int *uniques = malloc(n * n * sizeof(int));
    for (int l = 0; l < n*n; l++) {
        uniques[l] = 0;
    }

    // Loop through the array to every subarray
    for (int i = 0; i < n; i++) {
        // Loop through every subarray to access every integer
        for (int j = 0; j < n; j++) {
            int num = elements[i][j];
            // printf("num at %d,%d: %d\n", i, j, num);

            if (num < 1 || num > n * n) {
                free(uniques);
                // printf("number out of bounds at %d,%d\n", i, j);
                return 1;
            }
            
            // Check if uniques has marked this number as found
            if (uniques[num-1] == 0) {
                uniques[num-1] = 1;
            } else {
                // printf("value in uniques: %d\n", uniques[num-1]);
                free(uniques);
                // printf("duplicate number at %d,%d\n", i, j);
                return 1;
            }
        }
    }
    free(uniques);
    return 0;
}

/* puzzle is a 9x9 sudoku, represented as a 1D array of 9 pointers
 * each of which points to a 1D array of 9 integers.
 * Return 0 if puzzle is a valid sudoku and 1 otherwise. You must
 * only use check_group to determine this by calling it on
 * each row, each column and each of the 9 inner 3x3 squares
 */
int check_regular_sudoku(int **puzzle) {
    // Check rows
    // printf("check rows\n");
    for (int i = 0; i < 9; i++) {
        // printf("row %d\n", i);
        int *row = puzzle[i];

        // Construct group
        int *row_group[3] = { &(row[0]), &(row[3]), &(row[6]) };

        // Check group
        if (check_group(row_group, 3)) {
            printf("invalid row %d\n", i);
            return 1;
        }
    }

    // Check columns
    // printf("check columns\n");
    for (int i = 0; i < 9; i++) {
        // Construct column i
        // printf("column %d\n", i);

        int col[9];
        for (int j = 0; j < 9; j++) {
            col[j] = puzzle[j][i];
        }

        // Construct group
        int *col_group[3] = { &(col[0]), &(col[3]), &(col[6]) };

        // Check group
        if (check_group(col_group, 3)) {
            return 1;
        }
    }

    // Check squares
    // For each row of squares
    //printf("check squares\n");
    for (int i = 0; i < 3; i++) {
        // For each square in each row of squares
        for (int j = 0; j < 3; j++) {
            // Construct group
            // printf("square %d\n", i*3+j+1);
            int *square_group[3];
            
            // For each row in each square
            for (int k = 0; k < 3; k++) {
                int index1 = i * 3 + k;
                int index2 = j * 3;
                square_group[k] = &(puzzle[index1][index2]);
            }
    
            // Check group
            if (check_group(square_group, 3)) {
                return 1;
            }
        }
    }

    // Return 0 if all is well
    return 0;
}
