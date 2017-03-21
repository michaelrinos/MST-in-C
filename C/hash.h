#ifndef HASH_H
#define HASH_H
#include "Node.h"

typedef struct entry_n {
    char * key;
    Node * value;
    entry_n * next;
}Entry;

typedef struct hashtable_n{
    size_t size;
    size_t capacity;
    long (*hash)(void* key);  ///< hash function for key
    bool (*equals)(void *key1, void* key2); ///< equals function for key comparison
    void (*print)(void *key, void* value);  ///< print function for table dump debug
    entry_n ** table;
}Table;

Table* create(long (*hash)(void* key),
              bool (*equals)(void* key1, void* key2),
              void (*print)(void* key1, void* key2));


void * htn_set( hashtable_n *hastable, void * key, void * value);

void * htn_get( hashtable_n * hashtable, void * key);

bool has(hashtable_n * hashtable, void * key);

#endif
