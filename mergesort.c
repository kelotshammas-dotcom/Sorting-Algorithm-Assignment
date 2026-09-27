/* ============================================================
   MergeSort implementation for fixed-length 3-digit social
   media IDs. Prints the state of the FULL array after every
   merge operation so the merging process can be traced.
   ============================================================ */
#include <stdio.h>

#define N 8
int callNo = 0;

void printArray(int arr[], int n, const char *tag) {
    printf("%-28s : ", tag);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/* merge the two sorted halves arr[l..m] and arr[m+1..r] */
void merge(int arr[], int full[], int n, int l, int m, int r) {
    int nl = m - l + 1;
    int nr = r - m;
    int L[50], R[50];
    for (int i = 0; i < nl; i++) L[i] = arr[l + i];
    for (int j = 0; j < nr; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    int comparisons = 0;
    while (i < nl && j < nr) {
        comparisons++;
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else               arr[k++] = R[j++];
    }
    while (i < nl) arr[k++] = L[i++];
    while (j < nr) arr[k++] = R[j++];

    callNo++;
    char tag[64];
    sprintf(tag, "Merge #%d [%d..%d]&[%d..%d]", callNo, l, m, m+1, r);
    printArray(arr, n, tag);
    printf("   (comparisons in this merge = %d)\n", comparisons);
}

void mergeSort(int arr[], int n, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, n, l, m);
    mergeSort(arr, n, m + 1, r);
    merge(arr, arr, n, l, m, r);
}

int main() {
    int arr[N] = {324, 125, 456, 218, 102, 389, 275, 147};
    printf("MERGE SORT TRACE\n");
    printf("================\n");
    printArray(arr, N, "Initial array");
    printf("\n");

    mergeSort(arr, N, 0, N - 1);

    printf("\nFinal sorted array           : ");
    for (int i = 0; i < N; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
