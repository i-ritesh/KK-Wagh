#include <stdio.h>

#define MAX 100

// Function to input a sparse matrix
void inputSparseMatrix(int sparse[][3], int *nonZeroCount) {
    int rows, cols, value;

    printf("Enter the number of rows and columns of the matrix: ");
    scanf("%d %d", &sparse[0][0], &sparse[0][1]);

    printf("Enter the elements of the matrix (row by row):\n");
    *nonZeroCount = 0;

    for (int i = 0; i < sparse[0][0]; i++) {
        for (int j = 0; j < sparse[0][1]; j++) {
            scanf("%d", &value);
            if (value != 0) {
                (*nonZeroCount)++;
                sparse[*nonZeroCount][0] = i;
                sparse[*nonZeroCount][1] = j;
                sparse[*nonZeroCount][2] = value;
            }
        }
    }

    sparse[0][2] = *nonZeroCount; // Store number of non-zero elements
}

// Function to print the sparse matrix in triplet form
void printSparseMatrix(int sparse[][3]) {
    printf("\nSparse Matrix (Triplet Representation):\n");
    printf("Row\tColumn\tValue\n");
    for (int i = 0; i <= sparse[0][2]; i++) {
        printf("%d\t%d\t%d\n", sparse[i][0], sparse[i][1], sparse[i][2]);
    }
}

// Function to perform a simple and fast transpose
void fastTranspose(int sparse[][3], int transpose[][3]) {
    int rowCount[MAX] = {0}, rowStart[MAX] = {0};
    int rows = sparse[0][0], cols = sparse[0][1], nonZero = sparse[0][2];

    transpose[0][0] = cols;
    transpose[0][1] = rows;
    transpose[0][2] = nonZero;

    // Count occurrences of elements in each column (row in transposed matrix)
    for (int i = 1; i <= nonZero; i++) {
        rowCount[sparse[i][1]]++;
    }

    // Compute starting position of each row in transposed matrix
    for (int i = 1; i < cols; i++) {
        rowStart[i] = rowStart[i - 1] + rowCount[i - 1];
    }

    // Place elements in transposed matrix
    for (int i = 1; i <= nonZero; i++) {
        int col = sparse[i][1];
        int pos = rowStart[col]++;
        transpose[pos + 1][0] = sparse[i][1];
        transpose[pos + 1][1] = sparse[i][0];
        transpose[pos + 1][2] = sparse[i][2];
    }
}

int main() {
    int sparse[MAX][3], transpose[MAX][3];
    int nonZeroCount;

    inputSparseMatrix(sparse, &nonZeroCount);

    printf("\nOriginal Matrix in Sparse Form:");
    printSparseMatrix(sparse);

    fastTranspose(sparse, transpose);

    printf("\nTransposed Matrix in Sparse Form:");
    printSparseMatrix(transpose);

    return 0;
}
