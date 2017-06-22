#define TEST_AMOUNT 3

#include "Node.h"   //for Node
#include "Heap.h"   //for Heap, MinHeapNode
#include <limits.h> //for INT_MAX
#include <stdio.h>  //printf

void testHeap(Heap * heap){
    MinHeapNode * temp;
    for (size_t i = 0; i < TEST_AMOUNT; i ++){
        char str[TEST_AMOUNT + 1] = "";
        sprintf(str, "%zu", i);
        Node * n;
        init_node(&n, str, printNode);
        MinHeapNode * m = malloc(sizeof(MinHeapNode));
        temp = m;
        m->Node = n;
        m-> key = INT_MAX;
        heap_add(heap, m);
    }
    printf("Contains node : %d\n", contains(heap, temp));
    for (size_t i = 0; i < TEST_AMOUNT; i++){
        MinHeapNode * a = heap_remove(heap);
        printf("Node Name: %s\t Node key %d\n", a->Node->name, a->key);
    }
    printf("Heap Capacity %zu", heap->capacity);
    
}

int main( void ) {
    Heap * heap;
    heap_init(&heap);
    //testHeap(heap);
    deleteHeap(heap);
    
    return 0 ;
}

