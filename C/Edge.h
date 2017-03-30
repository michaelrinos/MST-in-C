#ifndef EDGE_H
#define EDGE_H

typedef struct Edge Edge;
struct Edge{
    int weight;
    int row;
    int col;
    void (*print)(Edge * toPrint);
};

void printEdge(Edge * e);
int compareTo(Edge * a, Edge * b);


#endif

