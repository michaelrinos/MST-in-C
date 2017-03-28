#ifndef MAZE_H
#define MAZE_H
#include "Node.h"
#include "hash.h"
#include <stdio.h>


struct Maze{
    int count;
    size_t pSize;
    size_t mSize;
    int * predecessors;
    int ** matrix;
    Table * graph;

};

typedef struct Maze Maze;

Maze* create_maze(size_t size);
void generate(Maze * maze, int number, int seed, double value);
void printMatrix(Maze * maze);
void printList(Maze * maze);

#endif