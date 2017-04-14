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

void destroy_node(Node * n){
    free(n->predecessor);
    free(n->neighbors);
    free(n);
}


void * putNeighbor(Node * a, Node * b, long weight){
    a->neighbors[a->nSize] = b;
    put(a->weights, (void *)b->name, (void *)weight);
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
                putNeighbor(a, b,(long) get(a->weights, &x ));
                free(oldNeighbors[i]);
            }
        }
        free(oldNeighbors);
    }
    return NULL;
}

void printNode(Node * n){
    /**
    printf("Name : %s, rank : %d, marked : %d\n", n->name, n->rank, n->marked);
    printf("\tNum neighbors : %lu \n\tNeighbor cap : %lu\n", n->nSize, n->nCapacity);
    printf("\tPredecessor Name : %s\n", n->predecessor->name);
    **/
    char * result = calloc(sizeof(char*), 7);
    strcpy(result , n->name);
    strcat(result , "-> ");

    for( size_t i = 0; i < n->nCapacity; i++){
        if (n->neighbors[i] == NULL){
            continue;   
        }
        if (get(n->weights, (void *)n->neighbors[i]->name) != NULL){

            unsigned long weight = (unsigned long) get(n->weights, (void *)n->neighbors[i]->name);
            char * weight_s = malloc(sizeof(char *) * 50);
            sprintf(weight_s, "%lu", weight);

            strcat(result, n->neighbors[i]->name);
            strcat(result, "(");
            strcat(result, weight_s);
            strcat(result, ") ");

            //printf("\t\t%s (%lu)\n", n->neighbors[i]->name, (long)(get(n->weights, (void *)n->neighbors[i]->name)));

        }
    }
    strcat(result, "\n");
    printf("%s", result);
}


int compareToNode(Node * a, Node * b){
    int a_num = atoi(a->name);
    int b_num = atoi(b->name);
    return a_num - b_num;
}


