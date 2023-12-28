#include <stdio.h>
#include <stdlib.h>

#define ROWS_A 3
#define COLS_A 2
#define ROWS_B 2
#define COLS_B 4

void multiplyMatrices(int** A, int** B, int*** result, int rows, int cols);
void printMatrix(int** matrix, int rows, int cols);

int main() {
    // Dynamic memory allocation for matrices
    int** matrixA = (int**)malloc(ROWS_A * sizeof(int*));
    for (int i = 0; i < ROWS_A; ++i) 
    {
        matrixA[i] = (int*)malloc(COLS_A * sizeof(int));
    }

    int** matrixB = (int**)malloc(ROWS_B * sizeof(int*));
    for (int i = 0; i < ROWS_B; ++i) 
    {
        matrixB[i] = (int*)malloc(COLS_B * sizeof(int));
    }

    int** resultMatrix = (int**)malloc(ROWS_A * sizeof(int*));
    for (int i = 0; i < ROWS_A; ++i) 
    {
        resultMatrix[i] = (int*)malloc(COLS_B * sizeof(int));
    }

    // Initialize matrices (for simplicity, you can modify this part)
    for (int i = 0; i < ROWS_A; ++i) 
    {
        for (int j = 0; j < COLS_A; ++j) 
        {
            matrixA[i][j] = i * COLS_A + j + 1;
        }
    }

    for (int i = 0; i < ROWS_B; ++i) 
    {
        for (int j = 0; j < COLS_B; ++j) 
        {
            matrixB[i][j] = i * COLS_B + j + 7;
        }
    }

    // Perform matrix multiplication
    multiplyMatrices(matrixA, matrixB, &resultMatrix, ROWS_A, COLS_B);

    // Print matrices
    printf("Matrix A:\n");
    printMatrix(matrixA, ROWS_A, COLS_A);

    printf("\nMatrix B:\n");
    printMatrix(matrixB, ROWS_B, COLS_B);

    printf("\nResult Matrix:\n");
    printMatrix(resultMatrix, ROWS_A, COLS_B);

    // Free dynamically allocated memory
    for (int i = 0; i < ROWS_A; ++i) {
        free(matrixA[i]);
    }
    free(matrixA);

    for (int i = 0; i < ROWS_B; ++i) {
        free(matrixB[i]);
    }
    free(matrixB);

    for (int i = 0; i < ROWS_A; ++i) {
        free(resultMatrix[i]);
    }
    free(resultMatrix);

    return 0;
}

void multiplyMatrices(int** A, int** B, int*** result, int rows, int cols) 
{
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            (*result)[i][j] = 0;
            for (int k = 0; k < COLS_A; ++k) 
            {
                (*result)[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void printMatrix(int** matrix, int rows, int cols) 
{
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}