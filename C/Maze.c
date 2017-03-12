#include "Maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Maze * create (size_t size){
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

    maze->map = ht_create( 65536 );
    if ( maze->map == NULL){
        assert(NULL);
    }
    return maze;
}
void generate(Maze * maze, int n, int seed, double p){
    maze->pSize = n;
    maze->predecessors = (int *)malloc(sizeof(int) * maze->pSize);
    maze->predecessors[0] = -1;

    for (int i = 0; i < n; i++){
        Node node = create( (char) i );
        ht_set(maze->map, (char) i, node);
    }

    srand(seed);
    
    while (maze->count != n){
        maze->count = 0;
        int range = n - 1 + 1;
		for (int i = 0; i < n; i++) {
                for (int j = i; j < n; j++) {
                    if (i == j) continue;
					double r = (double) rand() / (double)((unsigned)RAND_MAX + 1);
                    if (r <= p){
                        //int weight = MIN_WEIGHT + weightRand.nextInt(range);
                    }
                    maze->matrix[i][j] = weight;
                    maze->matrix[j][i] = weight;
                    //Add j as a neighbor to i
                    //Add i as a neighbor to j
                }
        }
        //set the predecessor of 0 as -1
        canReachDFS((char) 0, maze->count);     //Update how many nodes we can get 
                                                //to from the first node used in 
                                                //while check and set to count.
    }
}
