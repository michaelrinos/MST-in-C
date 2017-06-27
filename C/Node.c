#define _GNU_SOURCE

#include "Node.h"
#include "hash.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_STRING_SIZE 16

Node * init_node(char * name){
    Node * node = malloc(sizeof(Node));
    if (!node){
        assert(NULL);
    }
    node->rank=0;
    node->marked=0;
    node->predSet=0;
    node->nSize=0;
    node->name=strdup(name);
    /*node->predecessor=malloc(sizeof(Node));
    if ( node->predecessor == NULL ){
        assert(NULL);
    }*/
    node->nCapacity = INITIAL_CAPACITY;
    node->neighbors=calloc(node->nCapacity, sizeof(Node *));
    if ( node->neighbors == NULL ){
        assert(NULL);
    }
    node->weights = create(strHash, strEquals, strLongPrint );
    node->print = printNode;
    printf("Creaded Node: %s\n", node->name);
    return node;
}

void deleteNode(Node * n){
    //printf("\nBefore deleting checking n: %p, %d, %s\n", (void*)n, !n, n->name);
    if (n->print){
    //printf("Deleting Node %s\n", n->name);
    if (n->predSet){
        //printf("Deleting %s's predecessor %s\n", n->name, n->predecessor->name);
        deleteNode(n->predecessor);
    }
    else{
        //printf("Predecessor not set deleting malloc\n");
        free(n->predecessor);   
    }
    //printf("Neighbors have been taken care of continuing deletion of %s\n", n->name);
    free(n->neighbors);
    free(n->name);
    destroy(n->weights);
    memset(n, 0, sizeof(Node));
    free(n);
    }
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
                char * weight = malloc(sizeof(char) * MAX_STRING_SIZE);
                sprintf(weight, "%d", x);
                putNeighbor(a, oldNeighbors[i], (long)  get(a->weights, weight ) );
                free(weight);
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
            free(weight_s);

        }
    }
    strcat(result, "\n");
    printf("%s", result);
    free(result);
}


int compareToNode(Node * a, Node * b){
    return strcmp(a->name, b->name);

}


void setPred(Node * who, Node * pred){
    who->predecessor = pred;
    who->predSet = 1;
}



