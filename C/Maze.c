#include "Maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
    

    maze->graph = create(strHash, strEquals, strLongPrint);
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
        char * str = malloc(sizeof(int));
        sprintf(str, "%d", i);

        Node * node = malloc(sizeof(*node));
        init_node(&node, str, printNode);
        put(maze->graph, (void*)str, (void*)node);
    }

    srand(seed);
    
    while (maze->count != n){
        maze->count = 0;
        int range = n - 1 + 1;
		for (int i = 0; i < n; i++) {
                for (int j = i; j < n; j++) {
                    if (i == j) continue;
					double r = (double) rand() / RAND_MAX;
                    if (r <= p){
                        int weight = 1 + rand() % (range+1-0);
                        maze->matrix[i][j] = weight;
                        maze->matrix[j][i] = weight;

                        char * str_i = malloc(sizeof(int));
                        char * str_j = malloc(sizeof(int));
                        char * str_w = malloc(sizeof(int));

                        sprintf(str_w, "%d", weight);                           // Convert weight to string
                        
                        sprintf(str_i, "%d", i);                                // Convert i to string
                        Node * i = get(maze->graph, str_i );                    // Get i from the graph
                        
                        sprintf(str_j, "%d", j);
                        Node * j = get(maze->graph,  str_j );
                        
                        putNeighbor(i, j, weight);                              // Set j as a neighbor of i 
                        put(i->weights, (void*)str_j, (void*)str_w);            // Add j's weight in i

                        putNeighbor(j, i, weight);                              // Set i as a neighbor of j
                        put(i->weights, (void*)str_i, (void*)str_w);           // Add i's weight in j

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
    for (int i = 0; i < maze->count; i++) { 
        char * str = malloc(sizeof(int));
        sprintf(str, "%d", i);
        ((Node *)get(maze->graph, str))->print(get(maze->graph,str));
    }
    printf("\n");
}
























