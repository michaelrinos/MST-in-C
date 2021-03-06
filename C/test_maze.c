/// file test_Node
/// test program to ensure a Node is working properly

#include "Maze.h"   // to test
#include <stdlib.h> // malloc
#include <stdio.h>  // printf

#define TEST_AMOUNT 2


int main(int argc, char * argv[]) {
    Maze * maze = create_maze(TEST_AMOUNT);
    double p = .5;
    int seed = 100000;
    generate(maze, TEST_AMOUNT, seed, p);
    printMatrix(maze);
    printList(maze);
    
    Edge * temp1 = getList(maze);
    printf("Size of temp1: %lu\n", sizeof(temp1));
    free(temp1);
    
    Edge * temp2 = getMatrix(maze);
    free(temp2);
    
    Node ** temp3 = getMatrixNodes(maze);
    for (int i = 0; i < TEST_AMOUNT; i++){
        printNode(temp3[i]);
        deleteNode(temp3[i]);
    }
    free(temp3);
        
    /*
    Node * temp4 = getListNodes(maze);
    free(temp4);
    */

    deleteMaze(maze);

    int see = 0;
    if (argc == 2){
       seed = atoi(argv[1]);
    }
    printf("Seed value to stop error : %d\n" , see);

    return EXIT_SUCCESS;
}
