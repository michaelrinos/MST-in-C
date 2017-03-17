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
    }   

    maze->graph = htn_create( 65536 );
    if ( maze->graph == NULL){
        assert(NULL);
    }
    return maze;
}
void generate(Maze * maze, int n, int seed, double p){
    maze->pSize = n;
    maze->predecessors = (int *)malloc(sizeof(int) * maze->pSize);
    maze->predecessors[0] = -1;

    for (int i = 0; i < n; i++){
        char * str = "";
        sprintf(str, "%d", i);

        Node * node = create_node(str );
        htn_set(maze->graph, str, node);
    }

    srand(seed);
    
    while (maze->count != n){
        maze->count = 0;
        int range = n - 1 + 1;
		for (int i = 0; i < n; i++) {
                for (int j = i; j < n; j++) {
                    if (i == j) continue;
					double r = (double) rand() / (double)(1+1-0);
                    if (r <= p){
                        int weight = 1 + rand() % (range+1-0);
                        maze->matrix[i][j] = weight;
                        maze->matrix[j][i] = weight;

                        char * str_i = "";
                        char * str_j = "";
                        char * str_w = "";

                        sprintf(str_w, "%d", weight);           // Convert weight to string
                        
                        sprintf(str_i, "%d", i);                // Convert i to string
                        Node * i = htn_get(maze->graph, str_i );  // Get i from the graph
                        
                        sprintf(str_j, "%d", j);
                        Node * j = htn_get(maze->graph,  str_j );

                        i->neighbors[i->nSize++] = *j;          // Set j as a neighbor of i
                        ht_set(i->weights, str_j, str_w);      // Add j's weight in i

                        j->neighbors[j->nSize++] = *i;          // Set i as a neighbor of j
                        ht_set(i->weights, str_i, str_w);      // Add i's weight in j
                    }
                }
        }
        Node * zeroNode = htn_get(maze->graph, "0");
        Node * invalidNode = create_node("-1");
        zeroNode->predecessor = invalidNode;

        //set the predecessor of 0 as -1
//        canReachDFS(maze, "0");                 //Update how many nodes we can get 
                                                //to from the first node used in 
                                                //while check and set to count.
    }
}
/**
void canReachDFS(Maze * maze, char * start){ 
    Node * startNode = htn_get(maze->graph, start);
    int name = atoi(start);
    if (startNode->marked == 0){
        maze->count +=1;
    }
    startNode->marked = 1;
    Node * allNeighbors = starNode->neighbors;
    for (size_t i = 0; i < startNode->nSize; i++){
        if (allNeighbors[i]->marked == 0){
            char * tName = allNeighbors->name;
            
        }
    }
    
    

}
**/


























