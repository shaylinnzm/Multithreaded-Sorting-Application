#include <stdio.h>
#include <pthread.h>

#define SIZE 10
int arr[SIZE] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};
int result[SIZE];

// Sorting first half
void* sort_first_half(void* arg) {
    for (int i = 0; i < 5 - 1; i++) {
        for (int j = 0; j < 5 - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
    return NULL;
}

// Sorting second half
void* sort_second_half(void* arg) {
    for (int i = 5; i < 9; i++) {
        for (int j = 5; j < 9 - (i - 5); j++) {
            if (arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
    return NULL;
}


void* merge(void* arg) {
    int i = 0, j = 5, k = 0;
    while (i < 5 && j < 10) {
        if (arr[i] < arr[j])
            result[k++] = arr[i++];
        else
            result[k++] = arr[j++];
    }
    while (i < 5)
        result[k++] = arr[i++];
    while (j < 10)
        result[k++] = arr[j++];
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, sort_first_half, NULL);
    pthread_create(&t2, NULL, sort_second_half, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_create(&t3, NULL, merge, NULL);
    pthread_join(t3, NULL);

    printf("Sorted array:\n");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", result[i]);
    printf("\n");

    return 0;
}
