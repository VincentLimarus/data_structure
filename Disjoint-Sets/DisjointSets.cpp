#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parent[100];

struct Edge{
    int src, dst;
};

struct Graph{
    int totalVertices, totalEdges;
    struct Edge* edges;
};

struct Graph* createGraph(int totalVertices, int totalEdges){
    struct Graph* newGraph = (struct Graph*)malloc(sizeof(struct Graph));

    newGraph->totalEdges = totalEdges;
    newGraph->totalVertices = totalVertices;
    newGraph->edges = (struct Edge*)malloc(sizeof(struct Edge) * totalEdges);

    return newGraph;
}
void makeSet(int size){
    for(int i = 1; i <= size; i++){
        parent[i] = i;
    }
}

int findParent(int vertices){
    if(vertices == parent[vertices]) return vertices;
    return findParent(parent[vertices]);
}

void join(int vertices1, int vertices2){   
    int parent1 = findParent(vertices1);
    int parent2 = findParent(vertices2);
    parent[parent2] = parent1;   
}

bool isDisjoint(int vertices1, int vertices2){
    if(findParent(vertices1) != findParent(vertices2)) return true;
    return false;
}

bool checkCyclic(struct Graph* graph){
    makeSet(graph->totalVertices);
    
    for(int i = 0; i < graph->totalEdges; i++){
        int parentSource = findParent(graph->edges[i].src);
        int parentDest = findParent(graph->edges[i].dst);
        if(parentSource == parentDest) return true;

        join(graph->edges[i].src, graph->edges[i].dst);
    }
    return false;
}
int main()
{
    // Test ur Code here!
    // makeSet(5);

    // join(1,3);  
    // join(3,4);
    // join(2,5);

    // if(isDisjoint(1,5)) printf("Disjoint Set\n");
    // else printf("Same Set\n");

    // struct Graph* myGraph = createGraph(5,4);
    // myGraph->edges[0].src = 1;
    // myGraph->edges[0].dst = 3;

    // myGraph->edges[1].src = 3;
    // myGraph->edges[1].dst = 4;
    
    // myGraph->edges[2].src = 4;
    // myGraph->edges[2].dst = 5;

    // myGraph->edges[3].src = 5;
    // myGraph->edges[3].dst = 2;

    // if(checkCyclic(myGraph)) printf("The Graph is Cyclic!\n");
    // else printf("The Graph is not Cyclic!\n");
    return 0;
}