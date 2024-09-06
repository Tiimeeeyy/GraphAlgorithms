#include <stdio.h>
#include "graph.h"

int main() {
    int V = 5;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printGraph(graph);

    int res = isEulerian(graph);
    if (res == 0)
        printf("Graph is not Eulerian\n");
    else if (res == 1)
        printf("Graph has an Eulerian Path\n");
    else
        printf("Graph has an Eulerian Circuit\n");

    if (res != 0) {
        printf("Eulerian Tour: ");
        findEulerianTour(graph);
        printf("\n");
    }

    return 0;
}