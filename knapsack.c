#include <stdio.h>

struct Item {
    int weight;
    int profit;
};

void swap(struct Item* a, struct Item* b) {
    struct Item temp = *a;
    *a = *b;
    *b = temp;
}

void sortItems(struct Item arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            double r1 = (double)arr[j].profit / arr[j].weight;
            double r2 = (double)arr[j + 1].profit / arr[j + 1].weight;
            // descending order acc. p/w 
            if (r1 < r2) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

double fractionalKnapsack(struct Item items[], int n, int capacity) 
{
    sortItems(items, n);

    double totalValue = 0.0;
    int current_Weight = 0;

    for (int i = 0; i < n; i++) {
        if (current_Weight + items[i].weight <= capacity)// for full item 
        {
            current_Weight += items[i].weight;
            totalValue += items[i].profit;
        } 
        else //rest fractional
        {
            int remain = capacity - current_Weight;
            totalValue += items[i].profit * ((double)remain / items[i].weight);
            break;
        }
    }

    return totalValue;
}

int main() {
    int n, capacity;
    printf("Enter number of items: ");
    scanf("%d", &n);

    struct Item items[n];
    printf("Enter value and weight of each item:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &items[i].profit, &items[i].weight);
    }

    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    double maxValue = fractionalKnapsack(items, n, capacity);
    printf("Maximum value in Knapsack = %.2f\n", maxValue);

    return 0;
}