#ifndef NODE_H
#define NODE_H
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

Node * create_node(char * name);

void destroy_node(Node * n);


#endif
