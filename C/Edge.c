#include "Edge.h"
#include <stdio.h>

void printEdge(Edge * e){
    printf("%d %d weight = %d\n", e->row, e->col, e->weight);
}

int compareTo(Edge * a, Edge * b){
   int result = a->weight - b->weight;
    if (result == 0){
        if (a->row - b->row == 0){
            return a->col - b->col;
        }else
            return a->row - b->row;
    }else
        return result;
}
