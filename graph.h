#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NODES 50

// Adjacency list node
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

// Graph structure
typedef struct Graph {
    int numVertices;
    Node* adjList[MAX_NODES];
} Graph;

// Graph functions
Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest, int weight);
void displayGraph(Graph* graph);
Node* createNode(int vertex, int weight);

#endif
