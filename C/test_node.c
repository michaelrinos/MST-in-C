/// file test_Node
/// test program to ensure a Node is working properly

#include "Node.h"   // to test
#include <stdio.h>  // printf

#define TEST_AMOUNT 5

void putNodes(Node * a, Node * b, int weight){
    putNeighbor(a, b, weight);
}

Node ** testNode(){
    //struct Node nodes[TEST_AMOUNT+1];
    Node ** nodes = malloc(sizeof(Node) * TEST_AMOUNT);
    

    for (size_t i = 0; i < TEST_AMOUNT ; i++){
        char str[TEST_AMOUNT + 1] ="";
        sprintf(str, "%zu", i);
        nodes[i] = init_node(str);
        
        //nodes[i].print(&nodes[i]);
    }
    srand(5);
    int weight;
    for (int i = 0; i < TEST_AMOUNT; i++){
        weight =rand() % (7-1+1+1-1);
        putNeighbor(nodes[0], nodes[i], weight);
    }
    return nodes;
}


int main(int argc, char * argv[]) {
    Node ** nodes = testNode();
    
    //Node * n;
    //init_node(&n, "1", printNode);
    //printNode(n);
    //deleteNode(n);
    
    printf("This is node 0:\n");
    printNode(nodes[0]);
    printf("This is a copy of 0:\n");
    Node * copy = copy_node(nodes[0]);
    printNode(copy);
    printf("First Neighbor %s\n",copy->neighbors[0]->name);

    deleteNode(nodes[0]);
    nodes[0] = copy;

    for (size_t i = 0; i < TEST_AMOUNT; i++){
        printNode(nodes[i]);
        deleteNode(nodes[i]);
    }
    free(nodes);



    Node * a = init_node("a");
    Node * b = init_node("b");
    setPred(a,b, 0);
    compareToNode(a,b);
    deleteNode(a);
    printNode(b);
    deleteNode(b);



    int seed = 0;
    if (argc == 2){
       seed = atoi(argv[1]);
    }
    printf("Seed value to stop error : %d\n" , seed);

    return EXIT_SUCCESS;
}
