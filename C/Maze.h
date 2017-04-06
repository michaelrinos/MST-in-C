#ifndef MAZE_H
#define MAZE_H
#include "Node.h"
#include "hash.h"
#include "Edge.h"
#include <stdio.h>

#define MAX_NUMS 16

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
void DFSInfo(Maze * maze);
Edge * getMatrix(Maze * maze);
Edge * getList(Maze * maze);
Node * getMatrixNodes(Maze * maze);

#endif
