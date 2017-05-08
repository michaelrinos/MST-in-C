#define _GNU_SOURCE

#include "Node.h"
#include "hash.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void init_node(Node ** node, char * name, void (*printNode)(Node * n)){
    *node = (Node *) malloc(sizeof(Node));
    if ( node == NULL ){
        assert(NULL);
    }
    (*node)->rank=0;
    (*node)->marked=0;
    (*node)->nSize=0;
    (*node)->name=strdup(name);
    (*node)->predecessor=(Node *)malloc(sizeof(Node));
    if ( (*node)->predecessor == NULL ){
        assert(NULL);
    }
    (*node)->nCapacity = INITIAL_CAPACITY;
    (*node)->neighbors=(Node **)calloc((*node)->nCapacity, sizeof(Node *));
    if ( (*node)->neighbors == NULL ){
        assert(NULL);
    }
    (*node)->weights = create(strHash, strEquals, strLongPrint );
    (*node)->print = printNode;
}

void destroyNode(Node * n){
    free(n->predecessor);
    for (size_t i = 0; i < n->nCapacity; i++){
        if (n->neighbors[i]){
            free(n->neighbors[i]);
        }    
    }
    free(n->neighbors);
    free(n->name);
    destroy(n->weights);
    free(n);
}


void * putNeighbor(Node * a, Node * b, int weight){
    a->neighbors[a->nSize] = b;
    put(a->weights, (void *)b->name, (void *) (long) weight);
    a->nSize++;

    if ( a->nSize > a->nCapacity * LOAD_THRESHOLD ){
        size_t oldCap = a->nCapacity;
        Node ** oldNeighbors = a->neighbors;
        
        a->nCapacity = oldCap * RESIZE_FACTOR;
        a->neighbors = (Node **)(calloc(a->nCapacity, sizeof(Node *)));
        a->nSize = 0;
        
        for (size_t i = 0; i < oldCap; i++){
            if(oldNeighbors[i] != NULL){
                int x = atoi( oldNeighbors[i]->name );
                printf("X: %d\n\n\n", x); 
                putNeighbor(a, b, *( (int *) get(a->weights, &x )) );
                free(oldNeighbors[i]);
            }
        }
        free(oldNeighbors);
    }
    return NULL;
}

void printNode(Node * n){
    char * result = calloc(sizeof(char), 256);
    strcpy(result , n->name);
    strcat(result , "-> ");

    for( size_t i = 0; i < n->nCapacity; i++){
        if (n->neighbors[i] == NULL){
            continue;   
        }
        if (get(n->weights, (void *)n->neighbors[i]->name) != NULL){

            long weight = (long) get(n->weights, (void *)n->neighbors[i]->name);
            char * weight_s = malloc(sizeof(char) * 100);
            sprintf(weight_s, "%ld", weight);

            

            strcat(result, n->neighbors[i]->name);
            strcat(result, "(");
            strcat(result, weight_s);
            strcat(result, ") ");


        }
    }
    strcat(result, "\n");
    printf("%s", result);
    free(result);
}


int compareToNode(Node * a, Node * b){
    return strcmp(a->name, b->name);

}


