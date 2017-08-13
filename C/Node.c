#include "Node.h"
#include "hash.h"

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
    return node;
}

Node * copy_node(Node * other){
    Node * node = malloc(sizeof(Node));
    node->rank = other->rank;
    node->marked = other->marked;
    node->predSet = other->predSet;
    if (node->predSet) node->predecessor = copy_node(other->predecessor);
    node->nSize = 0;
    node->name = strdup(other->name);
    node->nCapacity = other->nCapacity;
    node->neighbors = calloc(node->nCapacity, sizeof(Node *));
    if ( node->neighbors == NULL )  assert(NULL);
    node->weights = create(strHash, strEquals, strLongPrint );
    node->print = printNode;
    for ( size_t i = 0; i < other->nSize; i++){
        putNeighbor(node, 
                other->neighbors[i], 
                (long) get(other->weights, (void *)other->neighbors[i]->name) 
                ) ;
    }
    return &(*node);
}

void deleteNode(Node * n){
    //printf("\nBefore deleting checking n: %p, %d, %s\n", (void*)n, !n, n->name);
    //printf("Deleting Node %s\n", n->name);
    if ( n->print){
    if (n->predSet){
        //printf("Deleting %s's predecessor %s\n", n->name, n->predecessor->name);
        //printf("My name: %s\t Pred Name %s\n", n->name, n->predecessor->name);
        deleteNode(n->predecessor);
    }
    //printf("Neighbors have been taken care of continuing deletion of %s\n", n->name);
    free(n->neighbors);
    free(n->name);
    destroy(n->weights);
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
        if (n->neighbors[i] != NULL && get(n->weights, (void *)n->neighbors[i]->name) != NULL){

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
    if (who->predSet){
        deleteNode(who->predecessor);
    }
    if (compareToNode(who, pred) == 0){
        who->predecessor = pred;
        who->predSet = 0;
    }
    else{
        who->predecessor = copy_node(pred);
        who->predSet = 1;
    }
}



