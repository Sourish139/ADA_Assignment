// Fibonacci Iterative with Time Calculation
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* allocatemMat(int n)
{
    int *mat = (int*)malloc(n * sizeof(int));
    if (mat == NULL)
    {
        printf("Memory allocation failed\n");
        exit(0);  // exit if memory not allocated
    }
    return mat;
}

void fibonace(int *arr, int n)
{
    if (n >= 1) arr[0] = 0;
    if (n >= 2) arr[1] = 1;

    for (int i = 2; i < n; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
}

void display(int *Arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", Arr[i]);
    }
    printf("\n");
}

int main()
{
    int n;
    clock_t start, end;
    double cpu_time_used;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    int *Arr = allocatemMat(n);

    // start timing
    start = clock();

    fibonace(Arr, n);
    display(Arr, n);

    // end timing
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken :%f seconds", cpu_time_used);

    free(Arr);  // free allocated memory
    return 0;
}