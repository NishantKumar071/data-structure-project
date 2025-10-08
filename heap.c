#include <stdio.h>
#include "heap.h"

typedef struct {
    int vertex;
    int accidentRate;
} HeapNode;

void heapify(HeapNode arr[], int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left].accidentRate > arr[largest].accidentRate)
        largest = left;

    if (right < n && arr[right].accidentRate > arr[largest].accidentRate)
        largest = right;

    if (largest != i) {
        HeapNode temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void detectHotspots(int accidentRates[], int n) {
    HeapNode heap[n];
    for (int i = 0; i < n; i++) {
        heap[i].vertex = i;
        heap[i].accidentRate = accidentRates[i];
    }

    for (int i = n/2 - 1; i >= 0; i--)
        heapify(heap, n, i);

    printf("\nTop 3 Accident Hotspots:\n");
    for (int i = 0; i < 3 && n > 0; i++) {
        printf("Location %d (Accident Rate: %d)\n", heap[0].vertex, heap[0].accidentRate);
        heap[0] = heap[n-1];
        n--;
        heapify(heap, n, 0);
    }
}
