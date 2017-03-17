#ifndef NODE_H
#define NODE_H
#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;
struct Node{
    int rank;
    int marked;
    int nSize;
    char * name;
    Node * predecessor;
    Node * neighbors;
    hashtable_s * weights;

};

Node * create_node(char * name);

void destroy_node(Node * n);


#endif
