#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

#define INF 99999

typedef struct MinHeapNode {
    int vertex;
    int distance;
} MinHeapNode;

typedef struct MinHeap {
    int size;
    int capacity;
    int *pos;
    MinHeapNode **array;
} MinHeap;

// --- Helper Functions ---
MinHeapNode* newMinHeapNode(int v, int dist);
MinHeap* createMinHeap(int capacity);
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);
void minHeapify(MinHeap* minHeap, int idx);
MinHeapNode* extractMin(MinHeap* minHeap);
void decreaseKey(MinHeap* minHeap, int v, int dist);
int isInMinHeap(MinHeap *minHeap, int v);

// --- Implementation ---
MinHeapNode* newMinHeapNode(int v, int dist) {
    MinHeapNode* node = (MinHeapNode*) malloc(sizeof(MinHeapNode));
    node->vertex = v;
    node->distance = dist;
    return node;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*) malloc(sizeof(MinHeap));
    minHeap->pos = (int*) malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**) malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && 
        minHeap->array[left]->distance < minHeap->array[smallest]->distance)
        smallest = left;

    if (right < minHeap->size && 
        minHeap->array[right]->distance < minHeap->array[smallest]->distance)
        smallest = right;

    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->vertex] = idx;
        minHeap->pos[idxNode->vertex] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

MinHeapNode* extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0) return NULL;

    MinHeapNode* root = minHeap->array[0];
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->vertex] = minHeap->size - 1;
    minHeap->pos[lastNode->vertex] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v];
    minHeap->array[i]->distance = dist;

    while (i && minHeap->array[i]->distance < 
           minHeap->array[(i - 1) / 2]->distance) {
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap *minHeap, int v) {
    return minHeap->pos[v] < minHeap->size;
}

// Dijkstra Algorithm
void dijkstra(Graph* graph, int src) {
    int V = graph->numVertices;
    int dist[V];
    MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; v++) {
        dist[v] = INF;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    dist[src] = 0;
    minHeap->array[src]->distance = 0;
    minHeap->size = V;

    while (minHeap->size) {
        MinHeapNode* minNode = extractMin(minHeap);
        int u = minNode->vertex;

        Node* temp = graph->adjList[u];
        while (temp != NULL) {
            int v = temp->vertex;
            if (isInMinHeap(minHeap, v) && dist[u] != INF &&
                temp->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + temp->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    printf("\nShortest distances from source %d:\n", src);
    for (int i = 0; i < V; i++)
        printf("Vertex %d : %d\n", i, dist[i]);
}
