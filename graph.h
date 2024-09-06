//
// Created by timis on 06/09/2024.
//

#ifndef GRAPH_H
#define GRAPH_H

struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

struct AdjList
{
    struct AdjListNode* head;
};

struct Graph
{
    int V;
    struct AdjList* array;
};

struct AdjListNode* new_adj_list_node(int dest);

struct Graph* createGraph(int v);

void addEdge(struct Graph* graph, int source, int dest);

void printGraph(struct Graph* graph);
int isEulerian(struct Graph* graph);
void findEulerianTour(struct Graph* graph);
int findHamiltonianCycle(struct Graph* graph);
void generateDOTFile(struct Graph* graph, const char* fileName);
void renderGraph(struct Graph* graph, const char* dotFileName, const char* outputFileName);
#endif //GRAPH_H
