#include <stdio.h>
#include <time.h>

long long fib_array[100]; // Array to store fibonacci numbers

// Recursive Fibonacci with memoization
long long fib(int n) {
    if (n <= 1)
        return n;

    // If already computed, return it
    if (fib_array[n] != 0)
        return fib_array[n];

    // Compute and store in array
    fib_array[n] = fib(n - 1) + fib(n - 2);
    return fib_array[n];
}

int main() {
    int terms;
    clock_t start, end;
    double cpu_time_used;

    // Initialize array with 0s
    for (int i = 0; i < 100; i++) {
        fib_array[i] = 0;
    }

    printf("Enter the number of terms: ");
    scanf("%d", &terms);

    // start timing
    start = clock();

    printf("Fibonacci Series: ");
    for (int i = 0; i < terms; i++) {
        printf("%lld ", fib(i));
    }

    // end timing
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken:%f seconds", cpu_time_used);

    return 0;
}