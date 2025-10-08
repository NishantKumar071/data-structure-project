#include <stdio.h>
#include "graph.h"
#include "dijkstra.h"
#include "heap.h"

int main() {
    int vertices = 6;
    Graph* graph = createGraph(vertices);

    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 3);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 2);
    addEdge(graph, 2, 3, 4);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 4, 5, 6);

    int accidentRates[] = {10, 40, 35, 50, 20, 15};
    int choice, src;

    do {
        printf("\n====== SMART TRAFFIC NAVIGATOR ======\n");
        printf("1. Display Road Network\n");
        printf("2. Find Shortest Route (Dijkstra)\n");
        printf("3. Detect Accident Hotspots\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                displayGraph(graph);
                break;
            case 2:
                printf("Enter source vertex: ");
                scanf("%d", &src);
                dijkstra(graph, src);
                break;
            case 3:
                detectHotspots(accidentRates, vertices);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 4);

    return 0;
}
