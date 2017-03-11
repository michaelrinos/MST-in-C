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

