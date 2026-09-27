/* ============================================================
   QuickSort implementation for fixed-length 3-digit social
   media IDs. Uses Lomuto partition scheme (last element as
   pivot). Prints the full array after every partition call.
   ============================================================ */
#include <stdio.h>

#define N 8
int callNo = 0;
long totalComparisons = 0;

void printArray(int arr[], int n, const char *tag) {
    printf("%-30s : ", tag);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

int partition(int arr[], int n, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    int comparisons = 0;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    totalComparisons += comparisons;

    callNo++;
    char tag[64];
    sprintf(tag, "Partition #%d pivot=%d (range %d..%d)", callNo, pivot, low, high);
    printArray(arr, n, tag);
    printf("   pivot placed at index %d, comparisons = %d\n", i + 1, comparisons);
    return i + 1;
}

void quickSort(int arr[], int n, int low, int high) {
    if (low < high) {
        int pi = partition(arr, n, low, high);
        quickSort(arr, n, low, pi - 1);
        quickSort(arr, n, pi + 1, high);
    }
}

int main() {
    int arr[N] = {324, 125, 456, 218, 102, 389, 275, 147};
    printf("QUICK SORT TRACE (Lomuto partition, pivot = last element)\n");
    printf("===========================================================\n");
    printArray(arr, N, "Initial array");
    printf("\n");

    quickSort(arr, N, 0, N - 1);

    printf("\nFinal sorted array             : ");
    for (int i = 0; i < N; i++) printf("%d ", arr[i]);
    printf("\n");
    printf("Total comparisons              : %ld\n", totalComparisons);
    printf("Total partition calls          : %d\n", callNo);
    return 0;
}
