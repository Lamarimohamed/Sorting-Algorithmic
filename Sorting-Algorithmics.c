#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void initializeArray(int arr[], int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 1000;  // Generate random values between 0 and 999
}

// Bubble Sort
void bubbleSort(int arr[], int n, long long *operations) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*operations)++;
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

// Quick Sort
int partition(int arr[], int low, int high, long long *operations) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        (*operations)++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high, long long *operations) {
    if (low < high) {
        int pi = partition(arr, low, high, operations);
        quickSort(arr, low, pi - 1, operations);
        quickSort(arr, pi + 1, high, operations);
    }
}

// Selection Sort
void selectionSort(int arr[], int n, long long *operations) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            (*operations)++;
            if (arr[j] < arr[min_index])
                min_index = j;
        }
        swap(&arr[i], &arr[min_index]);
    }
}

// Insertion Sort
void insertionSort(int arr[], int n, long long *operations) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            (*operations)++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        (*operations)++;  // Increment for the final placement of the key
    }
}

// Merge Sort
void merge(int arr[], int l, int m, int r, long long *operations) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        (*operations)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        (*operations)++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        (*operations)++;
    }
}

void mergeSort(int arr[], int l, int r, long long *operations) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, operations);
        mergeSort(arr, m + 1, r, operations);
        merge(arr, l, m, r, operations);
    }
}

int main() {
    int arr[ARRAY_SIZE];
    initializeArray(arr, ARRAY_SIZE);

    long long operations = 0;

    // Bubble Sort
    operations = 0;
    clock_t start_bubble = clock();
    bubbleSort(arr, ARRAY_SIZE, &operations);
    clock_t end_bubble = clock();
    printf("Bubble Sort:\n");
    printf("Number of operations: %lld\n", operations);
    printf("Time taken: %f seconds\n\n", ((double)end_bubble - start_bubble) / CLOCKS_PER_SEC);

    // Quick Sort
    operations = 0;
    clock_t start_quick = clock();
    quickSort(arr, 0, ARRAY_SIZE - 1, &operations);
    clock_t end_quick = clock();
    printf("Quick Sort:\n");
    printf("Number of operations: %lld\n", operations);
    printf("Time taken: %f seconds\n\n", ((double)end_quick - start_quick) / CLOCKS_PER_SEC);

    // Selection Sort
    operations = 0;
    clock_t start_selection = clock();
    selectionSort(arr, ARRAY_SIZE, &operations);
    clock_t end_selection = clock();
    printf("Selection Sort:\n");
    printf("Number of operations: %lld\n", operations);
    printf("Time taken: %f seconds\n\n", ((double)end_selection - start_selection) / CLOCKS_PER_SEC);

    // Insertion Sort
    operations = 0;
    clock_t start_insertion = clock();
    insertionSort(arr, ARRAY_SIZE, &operations);
    clock_t end_insertion = clock();
    printf("Insertion Sort:\n");
    printf("Number of operations: %lld\n", operations);
    printf("Time taken: %f seconds\n\n", ((double)end_insertion - start_insertion) / CLOCKS_PER_SEC);

    // Merge Sort
    operations = 0;
    clock_t start_merge = clock();
    mergeSort(arr, 0, ARRAY_SIZE - 1, &operations);
    clock_t end_merge = clock();
    printf("Merge Sort:\n");
    printf("Number of operations: %lld\n", operations);
    printf("Time taken: %f seconds\n\n", ((double)end_merge - start_merge) / CLOCKS_PER_SEC);

    return 0;
}
