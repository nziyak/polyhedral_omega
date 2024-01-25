#include <stdio.h>
#include <stdlib.h>

#define ROWS_A 3
#define COLS_A 2
#define ROWS_B 2
#define COLS_B 4

struct{
    int** A; //matrix A
    int** B; //matrix B
    int** result; //result matrix
}doubleMatrix_t;

struct{
    int* A; //matrix A
    int** B; //matrix B
    int* result; //result matrix
}singleMatrix_t;

void multMatrices_Db(int** A, int** B, int*** result, int rows, int cols);
void multMatrices_S(int* A, int** B, int* result, int cols);
void printMatrix_Db(int** matrix, int rows, int cols);
void printMatrix_S(int* matrix, int num);

int main() 
{
    int sel, index;
    
    printf("\n ------------------------------------\n");
    printf("Welcome to Ziya's Matrix Multiplicator!");

    do{
        printf("\n ------------------------------------\n");
        printf("enter an operation number.\n");
        printf("> obtain complete result matrix: 1\n");
        printf("> obtain a single row of result matrix: 2\n");
        printf("> obtain a single column of result matrix: 3\n");
        printf("> quit: 4\n");
        printf("> ");
        
        if(!(scanf("%d", &sel)) || sel > 4 || sel < 0)
        {
            fflush(stdin);
            printf("\ninvalid operation! enter again:\n");
            continue;
        }
        printf("\n");

        switch(sel)
        {
            case 1:

                // Dynamic memory allocation for matrices
                doubleMatrix_t.A = (int**)malloc(ROWS_A * sizeof(int*));
                doubleMatrix_t.result = (int**)malloc(ROWS_A * sizeof(int*));
                for (int i = 0; i < ROWS_A; ++i) 
                {
                    doubleMatrix_t.A[i] = (int*)malloc(COLS_A * sizeof(int));
                    doubleMatrix_t.result[i] = (int*)malloc(COLS_B * sizeof(int));
                }

                doubleMatrix_t.B = (int**)malloc(ROWS_B * sizeof(int*));
                for (int i = 0; i < ROWS_B; ++i) doubleMatrix_t.B[i] = (int*)malloc(COLS_B * sizeof(int));

                // Initialize matrices (for simplicity, you can modify this part)
                for (int i = 0; i < ROWS_A; ++i) 
                {
                    for (int j = 0; j < COLS_A; ++j) 
                    {
                       doubleMatrix_t.A[i][j] = i * COLS_A + j + 1;
                    }
                }

                for (int i = 0; i < ROWS_B; ++i) 
                {
                    for (int j = 0; j < COLS_B; ++j) 
                    {
                        doubleMatrix_t.B[i][j] = i * COLS_B + j + 7;
                    }
                }

                // Perform matrix multiplication
                multMatrices_Db(doubleMatrix_t.A, doubleMatrix_t.B, &doubleMatrix_t.result, ROWS_A, COLS_B);

                // Print matrices
                printf("Matrix A:\n");
                printMatrix_Db(doubleMatrix_t.A, ROWS_A, COLS_A);

                printf("\nMatrix B:\n");
                printMatrix_Db(doubleMatrix_t.B, ROWS_B, COLS_B);

                printf("\nResult Matrix:\n");
                printMatrix_Db(doubleMatrix_t.result, ROWS_A, COLS_B);

                // Free dynamically allocated memory
                for (int i = 0; i < ROWS_A; ++i) 
                {
                    free(doubleMatrix_t.A[i]);
                    free(doubleMatrix_t.result[i]);
                }
                free(doubleMatrix_t.A);
                free(doubleMatrix_t.result);

                for (int i = 0; i < ROWS_B; ++i) free(doubleMatrix_t.B[i]);
                free(doubleMatrix_t.B);
                
                break;
            
            case 2: //first allocate a 2D matrix, then take the row that user wants from result matrix. then take that row and deallocate 2D matrix.

                doubleMatrix_t.A = (int**)malloc(ROWS_A * sizeof(int*)); //allocate 2d A
                for (int i = 0; i < ROWS_A; ++i) doubleMatrix_t.A[i] = (int*)malloc(COLS_A * sizeof(int));
                if(doubleMatrix_t.A == NULL) return 1;

                // Initialize matrix
                for (int i = 0; i < ROWS_A; ++i) 
                {
                    for (int j = 0; j < COLS_A; ++j) 
                    {
                       doubleMatrix_t.A[i][j] = i * COLS_A + j + 1;
                    }
                }

                printf("enter the row of the result index you want: ");
                scanf("%d", &index);
                printf("\n");

                // Dynamic memory allocation for matrices
                singleMatrix_t.A = (int*)malloc(COLS_A * sizeof(int));
                if(singleMatrix_t.A == NULL) return 0;

                doubleMatrix_t.B = (int**)malloc(ROWS_B * sizeof(int*));
                for (int i = 0; i < ROWS_B; ++i) doubleMatrix_t.B[i] = (int*)malloc(COLS_B * sizeof(int)); //allocate rows of B
                if(doubleMatrix_t.B == NULL) return 0;

                singleMatrix_t.result = (int*)malloc(COLS_A * sizeof(int));
                if(singleMatrix_t.result == NULL) return 0;
                
                for(int j = 0; j < COLS_A; j++) //copy the desired row into single dimension matrix
                {
                    singleMatrix_t.A[j] = doubleMatrix_t.A[index][j];
                }
                
                printf("Matrix A:\n");
                printMatrix_Db(doubleMatrix_t.A, ROWS_A, COLS_A);
                printf("\n");

                for (int i = 0; i < ROWS_A; ++i) free(doubleMatrix_t.A[i]); //free 2D A
                free(doubleMatrix_t.A);

                for (int i = 0; i < ROWS_B; ++i) //initialize B
                {
                    for (int j = 0; j < COLS_B; ++j) 
                    {
                        doubleMatrix_t.B[i][j] = i * COLS_B + j + 7;
                    }
                }

                // Perform matrix multiplication
                multMatrices_S(singleMatrix_t.A, doubleMatrix_t.B, singleMatrix_t.result, COLS_B);

                // Print matrices
                printf("Matrix A[%d][]:\n", index);
                printMatrix_S(singleMatrix_t.A, COLS_A);
                printf("\n");

                printf("\nMatrix B:\n");
                printMatrix_Db(doubleMatrix_t.B, ROWS_B, COLS_B);

                printf("\nResult Matrix[%d]:\n", index);
                printMatrix_S(singleMatrix_t.result, COLS_B); //PRINTS 2 COLS INSTEAD OF 4???
                printf("\n");

                // Free dynamically allocated memory
                free(singleMatrix_t.A);
                free(singleMatrix_t.result);

                for (int i = 0; i < ROWS_B; ++i) free(doubleMatrix_t.B[i]);
                free(doubleMatrix_t.B);

                break;
            
            case 3:

                doubleMatrix_t.A = (int**)malloc(ROWS_A * sizeof(int*));
                doubleMatrix_t.result = (int**)malloc(ROWS_A * sizeof(int*));
                for (int i = 0; i < ROWS_A; ++i) 
                {
                    doubleMatrix_t.A[i] = (int*)malloc(COLS_A * sizeof(int));
                    doubleMatrix_t.result[i] = (int*)malloc(COLS_B * sizeof(int));
                }

                doubleMatrix_t.B = (int**)malloc(ROWS_B * sizeof(int*));
                for (int i = 0; i < ROWS_B; ++i) doubleMatrix_t.B[i] = (int*)malloc(COLS_B * sizeof(int));

                // Initialize matrices (for simplicity, you can modify this part)
                for (int i = 0; i < ROWS_A; ++i) 
                {
                    for (int j = 0; j < COLS_A; ++j) 
                    {
                       doubleMatrix_t.A[i][j] = i * COLS_A + j + 1;
                    }
                }

                for (int i = 0; i < ROWS_B; ++i) 
                {
                    for (int j = 0; j < COLS_B; ++j) 
                    {
                        doubleMatrix_t.B[i][j] = i * COLS_B + j + 7;
                    }
                }

                printf("enter the column of the result index you want: ");
                scanf("%d", &index);
                printf("\n");

                printf("Matrix A:\n");
                printMatrix_Db(doubleMatrix_t.A, ROWS_A, COLS_A);
                printf("\n");

                printf("Matrix B:\n");
                printMatrix_Db(doubleMatrix_t.B, ROWS_B, COLS_B);
                printf("\n");

                printf("Matrix B[][%d]:\n", index);
                for (int i = 0; i < COLS_B; ++i) 
                {
                    printf("%d\n", doubleMatrix_t.B[i][index]);
                }

                //calculate result matrix
                for (int j = 0; j < ROWS_B; ++j) 
                {
                    for (int k = 0; k < COLS_A; ++k) 
                    {
                        doubleMatrix_t.result[j][index] += doubleMatrix_t.A[k][j] * doubleMatrix_t.B[j][index];
                    }
                }

                printf("\nResult Matrix:\n");
                for(int i = 0; i < ROWS_A; i++) printf("%d\n", doubleMatrix_t.result[i][index]);

                break;
        }

    }while(sel != 4);

    return 0;
}

void multMatrices_Db(int** A, int** B, int*** result, int rows, int cols) 
{
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            for (int k = 0; k < COLS_A; ++k) 
            {
                (*result)[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void multMatrices_S(int* A, int** B, int* result, int cols) 
{
    for (int j = 0; j < cols; ++j) 
    {
        for (int k = 0; k < COLS_A; ++k) 
        {
            result[j] += A[k] * B[k][j];
        }
    }
}

void printMatrix_Db(int** matrix, int rows, int cols) 
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

void printMatrix_S(int* matrix, int num) 
{
    for(int i = 0; i < num; ++i) printf("%d\t", matrix[i]);        
}