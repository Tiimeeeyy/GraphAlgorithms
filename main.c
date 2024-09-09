#include <stdio.h>
#include "graph.h"

int main() {
    int V[] = {0, 1, 2, 3, 4, 5};
    int E[][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0},
        {0, 2}, {2, 4}, {4, 0}
    };
    int V_size = sizeof(V) / sizeof(V[0]);
    int E_size = sizeof(E) / sizeof(E[0]);

    struct Graph* graph;
    createGraphFromSet(V, V_size, E, E_size, &graph);

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
    }

    findHamiltonianCycle(graph);

    renderGraph(graph, "graph2.dot", "graph2.png");

    return 0;
}