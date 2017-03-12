#ifndef MAZE_H
#define MAZE_H

#include "hash.h"
#include <stdio.h>


struct Maze{
    int count;
    size_t pSize;
    size_t mSize;
    int * predecessors;
    int ** matrix;
    hashtable_s * map;

};

typedef struct Maze Maze;

Maze* create(size_t size);
void generate(int number, int seed, double value);

#endif
