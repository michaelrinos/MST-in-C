#include "Maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int factorial(int f){
    if (f == 0)
        return 1;
    return (f + factorial(f-1));
}

Maze * create_maze(size_t size){
    Maze * maze = (Maze *)malloc(sizeof(Maze));
    if ( maze == NULL ){
        assert(NULL);
    }

    maze->count = 0;

    maze->pSize = size;

    maze->mSize = size;

    maze->predecessors = (int *) malloc(sizeof(int) * maze->pSize);

    maze->matrix = (int **) malloc(sizeof(int *) * maze->mSize);
    for (size_t i = 0; i < maze->mSize; i++){
        maze->matrix[i] = (int *) malloc(sizeof(int) * maze->mSize);
        for (size_t j = 0; j < maze->mSize; j++){
            maze->matrix[i][j] = 0;
        }
    }   
    

    maze->graph = create(strHash, strEquals, strIntPrint);
    if ( maze->graph == NULL){
        assert(NULL);
    }
    return maze;
}

void canReachDFS(Maze * maze, char * start){ 
    Node * startNode = get(maze->graph, start);
    if (startNode->marked == 0){
        maze->count +=1;
    }
    startNode->marked = 1;
    Node ** allNeighbors = startNode->neighbors;
    for (size_t i = 0; i < startNode->nSize; i++){
        if (allNeighbors[i] != NULL && allNeighbors[i]->marked == 0){
            Node * tmp = allNeighbors[i];
            tmp->predecessor = startNode;
            
            canReachDFS(maze, tmp->name);
        }
    }
    startNode->marked = 2;
}



void generate(Maze * maze, int n, int seed, double p){
    maze->pSize = n;
    maze->predecessors = (int *)malloc(sizeof(int) * maze->pSize);
    maze->predecessors[0] = -1;

    for (int i = 0; i < n; i++){
        char * str = malloc(sizeof(char) * MAX_NUMS);
        sprintf(str, "%d", i);

        Node * node = malloc(sizeof(*node));
        init_node(&node, str, printNode);
        put(maze->graph, (void*)str, (void*)node);
    }

    srand(seed);
    
    while (maze->count != n){
        maze->count = 0;
        int range = 7;
		for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (i == j) continue;
                double r = (double) rand() / RAND_MAX;
                if (r <= p){
                    int weight = rand() % (range);
                    maze->matrix[i][j] = weight;
                    maze->matrix[j][i] = weight;

                    char * str_i = malloc(sizeof(char) * MAX_NUMS);
                    char * str_j = malloc(sizeof(char) * MAX_NUMS);
                    
                    sprintf(str_i, "%d", i);                                // Convert i to string
                    Node * i = get(maze->graph, str_i );                    // Get i from the graph
                    
                    sprintf(str_j, "%d", j);
                    Node * j = get(maze->graph,  str_j );
                    
                    putNeighbor(i, j, weight);                              // Set j as a neighbor of i 

                    putNeighbor(j, i, weight);                              // Set i as a neighbor of j


                    /**printf("Node %s neighbor is %s\n", str_i, str_j);
                    for (size_t q = 0; q < i->nSize; q++){
                        i->neighbors[q]->print(i->neighbors[q]);
                    }
                    **/
                }
            }
        }
        Node * zeroNode = get(maze->graph, "0");
        Node * invalidNode = malloc(sizeof(*invalidNode));
        init_node(&invalidNode, (char *)"-1", printNode);
        zeroNode->predecessor = invalidNode;

        //set the predecessor of 0 as -1
        //printf("Should loop forever without call to canReachDFS");
        canReachDFS(maze, "0");                 //Update how many nodes we can get 
                                                //to from the first node used in 
                                                //while check and set to count.
    }
}

void printMatrix(Maze * maze){
    printf("The graph as an adjacency matrix:\n\n");

	for (int i = 0; i < maze->count; i++) {
        printf(" ");
        for (int j = 0; j < maze->count; j++) {
            if (j == 0) {
                printf("%d", maze->matrix[i][j] );
            }
            else {
                printf("    %d", maze->matrix[i][j] );
            }
        }
    printf("\n\n");
    }
}

void printList(Maze * maze) {
    printf("The graph as an adjacency list:\n");
    //dump( ((Node *) get(maze->graph,"0"))->weights , 1);
    //dump( ((Node *) get(maze->graph,"6"))->weights , 1);
    for (int i = 0; i < maze->count; i++) { 
        char * str = malloc(sizeof(char) * MAX_NUMS);
        sprintf(str, "%d", i);
        ((Node *)get(maze->graph, str))->print(get(maze->graph,str));
    }
    printf("\n");
}



void DFSInfo(Maze * maze){

    printf("Depth-First Search:\n");
    printf("Vertices:  \n");
    for (int i = 0 ; i < maze->count; i++){
        printf(" %d", i);
    }
    
    printf("\nPredecessors: \n");
    
    for (int i = 0 ; i < maze->count; i++){
        char * str = malloc(sizeof(int));
        sprintf(str, "%d", i);
        printf("%s " , ( (Node*) get(maze->graph, str) )->predecessor->name );
    }
    printf("\n");
}

Edge * getMatrix(Maze * maze){
    Edge *edges = calloc(factorial(maze->count-1), sizeof(Edge) );
    int loc = 0;
    for (int i = 0; i < maze->count; i++){
        for (int j = 0; j < maze->count; j++){
            if ( i == j ) continue;
            if ( maze->matrix[i][j] == 0 ) continue;
            else {
                if (j > i){
                    Edge * e = malloc(sizeof(e));
                    e->weight = maze->matrix[i][j];
                    e->row = i;
                    e->col = j;
                    e->print = printEdge;
                    edges[loc++] = *e;
                }
            }
        }
    }
    return edges;
}

Edge * getList(Maze * maze){
    Edge * edges = malloc(factorial(maze->count -1) * sizeof(Edge) );
    Table * table = maze->graph;
    int loc = 0;
    for (int i = 0; i < maze->count - 1; i++ ){
        char * str = malloc(sizeof(char) * MAX_NUMS);
        sprintf(str, "%d", i);
        Node * n = get(table, str);
        Node ** neighbors = n->neighbors;
        for (size_t j = 0; j < n->nSize; j++){
            Node * neighbor = neighbors[j];
            if ( atoi(neighbor->name) > i ){
                Edge * e = malloc(sizeof(e));
                e->weight =(long) get(neighbor->weights, str);
                e->row = i;
                e->col = atoi(neighbor->name);
                e->print = printEdge;
                edges[loc++] = *e;
            }
        }
    }
    /**
    for ( int i = 0; i < factorial(maze->count-1); i ++){
        if (edges[i].weight)
            printEdge(&edges[i]);
    }
    **/
    return edges;
}

Node * getMatrixNodes(Maze * maze){ 
    Node * nodes = malloc(maze->count * sizeof(Node) );
    for (int i = 0; i < maze->count ; i++) {
        char * str = malloc(sizeof(char) * MAX_NUMS);
        sprintf(str, "%d", i);
        Node * n = malloc(sizeof(Node));
        init_node(&n, str, printNode);
        nodes[i] = *n;
        
    }
    for (int i = 0; i < maze->count; i++) {
        for (int j = i; j < maze->count ; j++) {
            if (i == j) continue;
            if (maze->matrix[i][j] == 0) continue;
            else {
                putNeighbor(&nodes[i], &nodes[j], maze->matrix[i][j]);
                putNeighbor(&nodes[j], &nodes[i], maze->matrix[i][j]);
            }
        }
    }
    return nodes;
}

Node * getListNodes(Maze * maze){
    Node * nodes = calloc(maze->count, sizeof(Node));
    for (int i = 0; i < maze->count; i ++){
        char * str = malloc(sizeof(char) * MAX_NUMS);
        sprintf(str, "%d", i);
        nodes[i] = *((Node *)get(maze->graph, str));
    }
    return nodes;
}
