#ifndef HASH_H
#define HASH_H
#include "Node.h"

typedef struct entry_s entry_s;
struct entry_s {
    char * key;
    Node * value;
    entry_s * next;

};

struct hashtable_s{
    int size;
    entry_s ** table;
};

typedef struct hashtable_s hashtable_s;

hashtable_s * ht_create (int size);

int ht_hash( hashtable_s * hashtable, char * key);

entry_s * ht_newpair( char * key, Node * value);

void ht_set( hashtable_s *hastable, char * key, Node * value);

Node * ht_get( hashtable_s * hashtable, char * key);

#endif
