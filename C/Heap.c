#include "Heap.h"

void heap_init(Heap * heap){
    heap = calloc(sizeof(heap));
    heap->size = 0;
    heap->capacity = INNITIAL_CAPACITY;
}

void heap_add(Heap * heap, Void * value){
    heap->array[heap->size] = value;
    siftUp(heap, heap->size);
    heap->size++;
}
MinHeapNode * heap_remove(Heap * heap){
    MinHeapNode res = heap->array[0];
    heap->size--;
    heap->array[0] = heap->array[heap->size];
    shiftDown(heap, 0);
    return res;
}
void siftUp(Heap * heap, int startIndex){
    int i = startIndex;
    MinHeapNode * a = heap->array;
    while (i>0 && a[parent(i)]->key >= a[i]->key){
        swap(&a[parent(i)], &a[i]);
        i = parent(i);
    }
}
void siftDown(Heap * heap, int startIndex){
    int currIndex = startIndex;
    MinHeapNode * mp = heap->array;
    int swapIndex = organize(heap, currIndex);
    while (swapIndex != currIndex){
        swap(&mp[swapIndex], &mp[currIndex]);
        currIndex = swapIndex;
        swapIndex = organize(heap, currIndex);
    }
}

int organize(Heap * heap, int i){
    int lt = lChild(i);
    int rt = rChild(i);
    Node thisVal = heap->array[i];

    if ((size_t )rt < heap->size){
        Node lVal = heap->array[lt];
        Node rVal = heap->array[rt];
        if (lVal.key < thisVal.key || rVal.key < thisVal.key ){
            if (lVal.key < rVal.key){
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
        Node lVal = heap->array[lt];
        if (lVal.key < thisVal.key){
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

void swap(Node *n1, Node *n2){
    Node temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}


