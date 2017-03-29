#include "Edge.h"
#include <stdio.h>

void printEdge(Edge * e){
    printf("%d %d weight = %d\n", e->row, e->col, e->weight);
}
