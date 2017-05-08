#ifndef HEAP_H
#define HEAP_H
#include "Node.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_BITS    8
#define NODES       1<<NUM_BITS


typedef struct MinHeapNode MinHeapNode;
struct MinHeapNode {
    int key;
    Node * Node;
};


typedef struct Heap_S Heap;
struct Heap_S {
    size_t capacity;
    size_t size;
    MinHeapNode ** array;

};

int contains(Heap * heap, MinHeapNode * what);
void heap_init(Heap ** heap);
void heap_add(Heap * heap, MinHeapNode * value);
MinHeapNode * heap_remove(Heap * heap);
void siftUp(Heap * heap, int startIndex);
void siftDown(Heap * heap, int startIndex);
int organize(Heap * heap, int i);
int parent(int index);
void lchild(int index);
void rchild(int index);
void swap(MinHeapNode * n1, MinHeapNode * n2);
int decreaseKey(Heap * heap, MinHeapNode * who);
void hDump(Heap * heap, int full);
void deleteHeap(Heap * heap);

#endif
