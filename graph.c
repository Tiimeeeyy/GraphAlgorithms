//
// Created by timis on 06/09/2024.
//

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; ++i)
    {
        graph->array[i].head = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest)
{
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void printGraph(struct Graph* graph)
{
    for (int v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

int isEulerian(struct Graph* graph)
{
    int odd = 0;
    for (int i = 0; i < graph->V; ++i)
    {
        int count = 0;
        struct AdjListNode* node = graph->array[i].head;
        while (node)
        {
            count++;
            node = node->next;
        }
        if (count % 2 != 0)
        {
            odd++;
        }
    }
    if (odd == 0)
    {
        return 2;
    }
    else if (odd == 2)
    {
        return 1;
    }
    return 0;
}

void findEulerianTour(struct Graph* graph)
{
    int check = isEulerian(graph);
    int* path = (int*)malloc(graph->V * sizeof(int));
    int pathIndex = 0;
    int* stack = (int*)malloc(graph->V * sizeof(int));
    int stackIndex = 0;
    int* visited = (int*)malloc(graph->V * sizeof(int));

    stack[stackIndex++] = 0;
    if (check != 2)
    {
        printf("The graph does not have an Eulerian tour! \n");
    }
    else
    {
        while (stackIndex > 0)
        {
            int v = stack[stackIndex--];
            struct AdjListNode* node = graph->array[v].head;
            while (node)
            {
                int u = node->dest;
                if (!visited[u])
                {
                    stack[stackIndex++] = u;
                    visited[u] = 1;
                }
                node = node->next;
            }
            path[pathIndex++] = v;
        }
        for (int i = pathIndex - 1; i >= 0; --i)
        {
            printf("%d", path[i]);
        }
        printf("\n");

        free(path);
        free(stack);
        free(visited);
    }
}

bool isSafe(int v, int path[], int pos, struct Graph* graph)
{
    struct AdjListNode* node = graph->array[path[pos - 1]].head;
    while (node)
    {
        if (node->dest == v)
        {
            break;
        }
        node = node->next;
    }
    if (node == NULL)
    {
        return false;
    }
    for (int i = 0; i < pos; ++i)
    {
        if (path[i] == v)
        {
            return false;
        }
    }
    return true;
}

bool hamCycleUtil(struct Graph* graph, int path[], int pos)
{
    if (pos == graph->V)
    {
        struct AdjListNode* node = graph->array[path[pos - 1]].head;
        while (node)
        {
            if (node->dest == path[0])
            {
                return true;
            }
            node = node->next;
        }
        return false;
    }

    for (int v = 1; v < graph->V; ++v)
    {
        if (isSafe(v, path, pos, graph))
        {
            path[pos] = v;
            if (hamCycleUtil(graph, path, pos + 1) == true)
            {
                return true;
            }
            path[pos] = -1;
        }
    }
    return false;
}

int findHamiltonianCycle(struct Graph* graph)
{
    int* path = (int*)malloc(graph->V * sizeof(int));
    for (int i = 0; i < graph->V; ++i)
    {
        path[i] = -1;
    }

    path[0] = 0;
    if (hamCycleUtil(graph, path, 1) == false)
    {
        printf("Graph does not have a Hamiltonian Cycle! \n");
        free(path);
        return 0;
    }

    printf("Hamiltonian Cycle: ");
    for (int i = 0; i < graph->V; ++i)
    {
        printf("%d", path[i]);
    }

    printf("%d\n", path[0]);

    free(path);
    return 1;
}

void generateDOTFile(struct Graph* graph, const char* fileName)
{
    FILE* file = fopen(fileName, "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "graph G {\n");
    for (int v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        while (pCrawl)
        {
            if (v < pCrawl->dest)
            {
                fprintf(file,"    %d -- %d;\n", v, pCrawl->dest);
            }
            pCrawl = pCrawl->next;
        }
    }
    fprintf(file, "}\n");

    fclose(file);
}

void renderGraph(struct Graph* graph, const char* dotFileName, const char* outputFIleName)
{
    generateDOTFile(graph, dotFileName);
    char command[256];
    snprintf(command, sizeof(command), "dot -Tpng %s -o %s && start %s", dotFileName, outputFIleName, outputFIleName);
    system(command);
}