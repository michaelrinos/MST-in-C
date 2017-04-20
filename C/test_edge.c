/// file test_Node
/// test program to ensure a Node is working properly

#include "Edge.h"   // to test
#include <stdlib.h> // malloc
#include <stdio.h>  // printf

#define TEST_AMOUNT 3

Edge * testEdge(Edge * edges){
    for (int i = 0; i < TEST_AMOUNT ; i++){
        Edge * e = malloc(sizeof(Edge));;
		e->weight = i;
		e->row = i;
		e->col = i;
		e->print = printEdge;
        edges[i] = *e;
    }
    printf("\n\nCreated an array of %d Edges\n\n", TEST_AMOUNT);
    for (size_t i = 0; i < TEST_AMOUNT; i++){
        edges[i].print(&edges[i]);
    }
    return edges;

}


int main(int argc, char * argv[]) {
    Edge * edges = malloc(sizeof(Edge) * TEST_AMOUNT);
    Edge * adges = testEdge(edges);

    for (size_t i = 0; i < TEST_AMOUNT; i++){
        adges[i].print(&adges[i]);
    }

    int seed = 0;
    if (argc == 2){
       seed = atoi(argv[1]);
    }
    printf("Seed value to stop error : %d" , seed);

    return EXIT_SUCCESS;
}
