/// file test_Node
/// test program to ensure a Node is working properly

#include "Node.h"   // to test
#include <stdio.h>  // printf

#define TEST_AMOUNT 7

void putNodes(Node * a, Node * b, int weight){
    putNeighbor(a, b, weight);
}

Node * testNode(Node * nodes){
    //struct Node nodes[TEST_AMOUNT+1];
 //   Node * nodes = malloc(sizeof(Node) * TEST_AMOUNT);


    for (size_t i = 0; i < TEST_AMOUNT ; i++){
        char str[TEST_AMOUNT + 1] ="";
        sprintf(str, "%zu", i);
        Node * n;
        init_node(&n, str, printNode);
        
        nodes[i] = *n;
        //nodes[i].print(&nodes[i]);
    }
    printf("\n\nCreated an array of %d Nodes\n\n", TEST_AMOUNT);
    srand(5);
    int weight;// = 1 + rand() % (7-1+1+1-1);
    for (int i = 0; i < 50; i++){
        weight =rand() % (7-1+1+1-1);
        if (weight == 0)
            printf("Weight: %d\n", weight);
        //printf("Weight: %d\n", weight);
    }


    for (size_t i = 0; i < TEST_AMOUNT; i++){
        nodes[i].print(&nodes[i]);
    }
    return nodes;

}


int main(int argc, char * argv[]) {
    Node * nodes = malloc(sizeof(Node) * TEST_AMOUNT);
    //Node * modes = testNode(nodes);
    testNode(nodes);
    
    /**for (size_t i = 0; i < TEST_AMOUNT; i++){
        modes[i].print(&modes[i]);
        //dump(modes[i].weights, 1);
    }**/

    int seed = 0;
    if (argc == 2){
       seed = atoi(argv[1]);
    }
    printf("Seed value to stop error : %d" , seed);

    return EXIT_SUCCESS;
}
