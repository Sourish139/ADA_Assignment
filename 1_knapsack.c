#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapSack(int capacity, int weights[], int values[], int n) {
    int dp[n + 1][capacity + 1];

    // bottom-up dp[][] table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], 
                               dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][capacity];
}

int main() {
    int n, capacity;
    printf("Enter number of items: ");
    scanf("%d", &n);

    int profit[n], weights[n];
    printf("Enter value and weight of each item:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &profit[i], &weights[i]);
    }

    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    int maxValue = knapSack(capacity, weights, profit, n);
    printf("Maximum value in Knapsack = %d\n", maxValue);

    return 0;
}