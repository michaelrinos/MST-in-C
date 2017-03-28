/// file test_Node
/// test program to ensure a Node is working properly

#include "Node.h"   // to test
#include <stdio.h>  // printf

#define TEST_AMOUNT 3

void testNode(){
    //struct Node nodes[TEST_AMOUNT+1];
    Node * nodes = malloc(sizeof(Node) * TEST_AMOUNT);

    /**
    Node * a = malloc(sizeof(*a));
    init_node(&a, "0", printNode);
    Node * b = malloc(sizeof(*b));
    init_node(&b, "1", printNode);
    a->print(a);
    b->print(b);
    nodes[0] = *a;
    nodes[1] = *b;
    
    nodes[0].print(&nodes[0]);
    nodes[0].print(&nodes[1]);
    **/

    for (size_t i = 0; i < TEST_AMOUNT ; i++){
        char str[TEST_AMOUNT + 1] ="";
        sprintf(str, "%zu", i);
        Node * n;
        init_node(&n, str, printNode);
        
        nodes[i] = *n;
        //nodes[i].print(&nodes[i]);
    }
    printf("\n\nCreated an array of %d Nodes\n\n", TEST_AMOUNT);
    putNeighbor(&nodes[0], &nodes[1], 5);
    for (size_t i = 0; i < TEST_AMOUNT; i++){
        nodes[i].print(&nodes[i]);
    }

}


int main(int argc, char * argv[]) {
    testNode();
    int seed = 0;
    if (argc == 2){
       seed = atoi(argv[1]);
    }
    printf("Seed value to stop error : %d" , seed);

    return EXIT_SUCCESS;
}
