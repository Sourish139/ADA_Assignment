#include <stdio.h>
#include <time.h>

struct Activity {
    int index;
    int start;
    int finish;
};

void swap(struct Activity *a, struct Activity *b) {
    struct Activity temp = *a;
    *a = *b;
    *b = temp;
}

// Ascending order sorting
void sortActivities(struct Activity activities[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (activities[j].finish > activities[j + 1].finish) {
                swap(&activities[j], &activities[j + 1]);
            }
        }
    }
}

// Greedy Activity Selection
void activitySelection(struct Activity activities[], int n) {
    sortActivities(activities, n);

    printf("\nActivities sorted by finish time:\n");
    for (int i = 0; i < n; i++) {
        printf("Activity %d: Start = %d, Finish = %d\n",
               activities[i].index, activities[i].start, activities[i].finish);
    }

    printf("\nSelected activities are:\n");

    int last = 0; //Act. with earliest finish time as ref.
    printf("Activity %d (Start: %d, Finish: %d)\n",
           activities[last].index, activities[last].start, activities[last].finish);

    for (int i = 1; i < n; i++) {
        if (activities[i].start >= activities[last].finish) {
            printf("Activity %d (Start: %d, Finish: %d)\n",
                   activities[i].index, activities[i].start, activities[i].finish);
            last = i;
        }
    }
}

int main() {
    int n;

    printf("Enter the number of activities: ");
    scanf("%d", &n);

    struct Activity activities[n];

    printf("\nEnter start and finish times for each activity:\n");
    for (int i = 0; i < n; i++) {
        printf("Activity %d -> Start: ", i + 1);
        scanf("%d", &activities[i].start);
        printf("Activity %d -> Finish: ", i + 1);
        scanf("%d", &activities[i].finish);
        activities[i].index = i + 1;
    }

    // Time check
    clock_t start_time = clock();
    activitySelection(activities, n);
    clock_t end_time = clock();

    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("\nExecution time: %.6f seconds\n", time_taken);

    return 0;
}
