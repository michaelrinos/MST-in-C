#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux.  See feature_test_macros(7) */
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>


Table* create(long (*hash)(void* key),
              bool (*equals)(void* key1, void* key2),
              void (*print)(void* key1, void* key2)){

    Table* myTable =(Table*)malloc(sizeof(Table));
    if (myTable==NULL){
        assert(NULL);
    }
    myTable-> table = (Entry**)calloc(INITIAL_CAPACITY, sizeof(Entry*));
    myTable-> size = 0;
    myTable-> capacity = INITIAL_CAPACITY;
    myTable-> hash = hash;
    myTable-> equals = equals;
    myTable-> print = print;
    
    return myTable;
}

void * htn_set( hashtable_n *hastable, void * key, void * value){
    
}

void * htn_get( hashtable_n * hashtable, void * key){
    long hash = hashtable->hash(key);
    if (hashtable->table[key] == NULL){
        assert(NULL);
    }

    if (hashtable->size >= hashtable.capacity * LOAD_THRESHOLD){
        Entry ** oldTable = hashtable->table;
        size_t oldSize = hashtable->size;
        hashtable->capacity = oldSize * RESIZE_FACTOR;
        hashtable->table = (Entry**) calloc(hashtable->capacity, sizeof(Entry*));
        for (size_t i = 0; i <= oldSize; i++){  //Wrong
            htn_set(hashtable. 
        }
    }
}

bool has(hashtable_n * hashtable, void * key){

}

