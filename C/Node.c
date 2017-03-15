#include "Node.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


Node * create_node(char * name){
    Node * node = (Node *) malloc(sizeof(Node));
    if ( node == NULL ){
        assert(NULL);
    }
    node->rank=0;
    node->marked=0;
    node->name=name;
    node->predecessor=(Node *)malloc(sizeof(Node));
    if ( node->predecessor == NULL ){
        assert(NULL);
    }
    node->neighbors=(Node *)malloc(sizeof(Node));
    if ( node->neighbros == NULL ){
        assert(NULL);
    }
    return node;
}

void destroy_node(Node * n){
    free(n->predecessor);
    free(n->neighbors);
    free(n);
}



