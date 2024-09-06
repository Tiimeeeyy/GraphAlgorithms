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

void findEulerianTourUtil(struct Graph* graph, int v, int* path, int* pathIndex)
{
    struct AdjListNode* node = graph->array[v].head;
    while (node)
    {
        int u = node->dest;
        node = node->next;
        findEulerianTourUtil(graph, u, path, pathIndex);
    }
    path[(*pathIndex)++] = v;
}

void findEulerianTour(struct Graph* graph)
{
    int* path = (int*)malloc(graph->V * sizeof(int));
    int pathIndex = 0;
    findEulerianTourUtil(graph, 0, path, &pathIndex);
    for (int i = pathIndex - 1; i >= 0; --i)
    {
        printf("%d", path[i]);
    }
    free(path);
}
