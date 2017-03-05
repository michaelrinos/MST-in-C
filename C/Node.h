#ifndef NODE_H_
#define NODE_H_
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

struct Node{
    int rank;
    int marked;
    int weight;
    char * name;
    Node * predecessor;
    Node * neightbors;

};

#endif
