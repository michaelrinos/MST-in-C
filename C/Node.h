#ifndef NODE_H
#define NODE_H
#include "table.h"
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16
#define LOAD_THRESHOLD 0.75
#define RESIZE_FACTOR 2

typedef struct Node Node;
struct Node{
    int rank;
    int marked;
    size_t nSize;
    size_t nCapacity;
    char * name;
    Node * predecessor;
    Table * weights;
    void (*print)(Node * toPrint);  ///< print function for printing all info
    Node ** neighbors;
};


int compareToNode(Node * a, Node * b);
void init_node(Node ** node, char * name, void (*printNode)(Node * n));
void destroyNode(Node * n);
void printNode(Node * n);
void * putNeighbor(Node * a, Node * b, int weight);

#endif
