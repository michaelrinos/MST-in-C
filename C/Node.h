#define _GNU_SOURCE

#ifndef NODE_H
#define NODE_H
#include "table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define INITIAL_CAPACITY 16
#define LOAD_THRESHOLD 0.75
#define RESIZE_FACTOR 2
#define MAX_STRING_SIZE 16

typedef struct Node Node;
struct Node{
    int rank;
    int marked;
    int predSet;
    size_t nSize;
    size_t nCapacity;
    char * name;
    Node * predecessor;
    Table * weights;
    void (*print)(Node * toPrint);  ///< print function for printing all info
    Node ** neighbors;
};


int compareToNode(Node * a, Node * b);
Node * init_node(char * name);
void deleteNode(Node * n);
void printNode(Node * n);
void * putNeighbor(Node * a, Node * b, int weight);
void setPred(Node * who, Node * pred);

#endif
