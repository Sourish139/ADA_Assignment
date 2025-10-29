#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// Recursive method - Fibonacci
int fib_recursion(int n)
{
    if(n<=1)
    {
        return n;
    }
    return fib_recursion(n-1)+fib_recursion(n-2);
}
int main()
{
    int terms;
    clock_t start, end;
    double cpu_time_used;

    printf("Enter the number of terms: ");
    scanf("%d", &terms);

    start = clock();

    for (int i = 0; i < terms; i++)
    {
        printf("%d ", fib_recursion(i));
    }

    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nTime taken:%f seconds", cpu_time_used);

    return 0;
}