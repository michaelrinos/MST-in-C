#include "Heap.h"
#include "Node.h"
#include <stdio.h>

void siftUp(Heap * heap, int startIndex);
void siftDown(Heap * heap, int startIndex);
int parent(int index);
void swap(MinHeapNode * n1, MinHeapNode * n2);
int lChild(int index);
int rChild(int index);

void heap_init(Heap ** heap){
    (*heap) = malloc(sizeof(heap));
    (*heap)->size = 0;
    (*heap)->capacity = NODES;
    (*heap)->array = calloc(NODES, sizeof(MinHeapNode));
}

void heap_add(Heap * heap, MinHeapNode * value){
    heap->array[heap->size] = value;
    siftUp(heap, heap->size);
    heap->size++;
}
MinHeapNode * heap_remove(Heap * heap){
    MinHeapNode * res =  (MinHeapNode *)heap->array[0];
    heap->size--;
    heap->array[0] = heap->array[heap->size];
    siftDown(heap, 0);
    return res;
}
void siftUp(Heap * heap, int startIndex){
    int i = startIndex;
    MinHeapNode ** a = (MinHeapNode **)heap->array;
    while (i>0 && a[(parent(i))]->key >= a[i]->key){
        swap(a[parent(i)], a[i]);
        i = parent(i);
    }
}
void siftDown(Heap * heap, int startIndex){
    int currIndex = startIndex;
    MinHeapNode ** mp =(MinHeapNode **)heap->array;
    int swapIndex = organize(heap, currIndex);
    while (swapIndex != currIndex){
        swap(mp[swapIndex], mp[currIndex]);
        currIndex = swapIndex;
        swapIndex = organize(heap, currIndex);
    }
}

int organize(Heap * heap, int i){
    int lt = lChild(i);
    int rt = rChild(i);
    MinHeapNode * thisVal = (MinHeapNode *)heap->array[i];

    if ((size_t )rt < heap->size){
        MinHeapNode * lVal = (MinHeapNode *)heap->array[lt];
        MinHeapNode * rVal = (MinHeapNode *)heap->array[rt];
        if (lVal->key < thisVal->key || rVal->key < thisVal->key ){
            if (lVal->key < rVal->key){
                return lt;
            }
            else{
                return rt;
            }
        }
        else{
            return i;
        }
    }
    else if ((size_t)lt < heap->size){
        MinHeapNode * lVal = (MinHeapNode*)heap->array[lt];
        if (lVal->key < thisVal->key){
            return lt;
        }
        else{
            return i;
        }
    }
    else{
        return i;
    }
}

int parent(int index){
    return (index - 1)/2;
}

//@param index
//@description
//@return
int lChild(int index){
    return (2*index)+1;
}

//@param index
//@description
//@return
int rChild(int index){
    return (2*index)+2;
}

void swap(MinHeapNode * n1, MinHeapNode * n2){
    MinHeapNode temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

int contains(Heap * heap, MinHeapNode * what){
    for (size_t i = 0; i < heap->capacity; i++){
        MinHeapNode * temp = heap->array[i];
        if (compareToNode(temp->Node, what->Node)){
            return 1;
        }
    }
    return 0;
}
int decreaseKey(Heap * heap, MinHeapNode * who){
    for (size_t i = 0; i < heap->capacity; i++){
        MinHeapNode * temp = heap->array[i];
        if (compareToNode(temp->Node, who->Node) == 0){
            temp->key = who->key;
            siftUp(heap, i);
            return 1;
        }
    }
    return 0;
}
