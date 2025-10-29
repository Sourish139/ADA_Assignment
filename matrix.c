#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1024  // maximum size (2^n)

// Function to allocate matrix dynamically
int** allocate_matrix(int n) {
    int **mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        mat[i] = (int*)malloc(n * sizeof(int));
    return mat;
}

// Function to generate random matrix
void generate_matrix(int **mat, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = rand() % 10; // random 0–9
}

// Function to add matrices
void add_matrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Function to subtract matrices
void sub_matrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Iterative multiplication
void iterative_multiply(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// Divide & Conquer multiplication
void divide_conquer(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n/2;
    int **A11 = allocate_matrix(k); int **A12 = allocate_matrix(k);
    int **A21 = allocate_matrix(k); int **A22 = allocate_matrix(k);
    int **B11 = allocate_matrix(k); int **B12 = allocate_matrix(k);
    int **B21 = allocate_matrix(k); int **B22 = allocate_matrix(k);
    int **C11 = allocate_matrix(k); int **C12 = allocate_matrix(k);
    int **C21 = allocate_matrix(k); int **C22 = allocate_matrix(k);
    int **temp1 = allocate_matrix(k); int **temp2 = allocate_matrix(k);

    // Partitioning
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+k];
            A21[i][j] = A[i+k][j];
            A22[i][j] = A[i+k][j+k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+k];
            B21[i][j] = B[i+k][j];
            B22[i][j] = B[i+k][j+k];
        }
    }

    // Recursive calls
    divide_conquer(A11, B11, temp1, k);
    divide_conquer(A12, B21, temp2, k);
    add_matrix(temp1, temp2, C11, k);

    divide_conquer(A11, B12, temp1, k);
    divide_conquer(A12, B22, temp2, k);
    add_matrix(temp1, temp2, C12, k);

    divide_conquer(A21, B11, temp1, k);
    divide_conquer(A22, B21, temp2, k);
    add_matrix(temp1, temp2, C21, k);

    divide_conquer(A21, B12, temp1, k);
    divide_conquer(A22, B22, temp2, k);
    add_matrix(temp1, temp2, C22, k);

    // Combine into C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j+k] = C12[i][j];
            C[i+k][j] = C21[i][j];
            C[i+k][j+k] = C22[i][j];
        }
    }
}

// Strassen’s multiplication
void strassen(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n/2;
    int **A11 = allocate_matrix(k); int **A12 = allocate_matrix(k);
    int **A21 = allocate_matrix(k); int **A22 = allocate_matrix(k);
    int **B11 = allocate_matrix(k); int **B12 = allocate_matrix(k);
    int **B21 = allocate_matrix(k); int **B22 = allocate_matrix(k);
    int **C11 = allocate_matrix(k); int **C12 = allocate_matrix(k);
    int **C21 = allocate_matrix(k); int **C22 = allocate_matrix(k);

    int **M1 = allocate_matrix(k); int **M2 = allocate_matrix(k);
    int **M3 = allocate_matrix(k); int **M4 = allocate_matrix(k);
    int **M5 = allocate_matrix(k); int **M6 = allocate_matrix(k);
    int **M7 = allocate_matrix(k);

    int **tempA = allocate_matrix(k); int **tempB = allocate_matrix(k);

    // Partition matrices
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+k];
            A21[i][j] = A[i+k][j];
            A22[i][j] = A[i+k][j+k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+k];
            B21[i][j] = B[i+k][j];
            B22[i][j] = B[i+k][j+k];
        }
    }

    // M1 = (A11 + A22)(B11 + B22)
    add_matrix(A11, A22, tempA, k);
    add_matrix(B11, B22, tempB, k);
    strassen(tempA, tempB, M1, k);

    // M2 = (A21 + A22)B11
    add_matrix(A21, A22, tempA, k);
    strassen(tempA, B11, M2, k);

    // M3 = A11(B12 - B22)
    sub_matrix(B12, B22, tempB, k);
    strassen(A11, tempB, M3, k);

    // M4 = A22(B21 - B11)
    sub_matrix(B21, B11, tempB, k);
    strassen(A22, tempB, M4, k);

    // M5 = (A11 + A12)B22
    add_matrix(A11, A12, tempA, k);
    strassen(tempA, B22, M5, k);

    // M6 = (A21 - A11)(B11 + B12)
    sub_matrix(A21, A11, tempA, k);
    add_matrix(B11, B12, tempB, k);
    strassen(tempA, tempB, M6, k);

    // M7 = (A12 - A22)(B21 + B22)
    sub_matrix(A12, A22, tempA, k);
    add_matrix(B21, B22, tempB, k);
    strassen(tempA, tempB, M7, k);

    // C11 = M1 + M4 - M5 + M7
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C11[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];

    // C12 = M3 + M5
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C12[i][j] = M3[i][j] + M5[i][j];

    // C21 = M2 + M4
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C21[i][j] = M2[i][j] + M4[i][j];

    // C22 = M1 - M2 + M3 + M6
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C22[i][j] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];

    // Combine into C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j+k] = C12[i][j];
            C[i+k][j] = C21[i][j];
            C[i+k][j+k] = C22[i][j];
        }
    }
}

int main() {
    srand(time(NULL));

    for (int p = 1; p <= 7; p++) {  // test n = 2^1 to 2^8
        int n = 1 << p;  // n = 2^p
        int **A = allocate_matrix(n);
        int **B = allocate_matrix(n);
        int **C = allocate_matrix(n);

        generate_matrix(A, n);
        generate_matrix(B, n);

        clock_t start, end;

        // Iterative
        start = clock();
        iterative_multiply(A, B, C, n);
        end = clock();
        printf("Iterative: n=%d time=%.8f sec\n", n, (double)(end-start)/CLOCKS_PER_SEC);

        // Divide & Conquer
        start = clock();
        divide_conquer(A, B, C, n);
        end = clock();
        printf("Divide & Conquer: n=%d time=%.8f sec\n", n, (double)(end-start)/CLOCKS_PER_SEC);

        // Strassen
        start = clock();
        strassen(A, B, C, n);
        end = clock();
        printf("Strassen: n=%d time=%.8f sec\n\n", n, (double)(end-start)/CLOCKS_PER_SEC);
    }

    return 0;
}