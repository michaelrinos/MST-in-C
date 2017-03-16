#ifndef HASH_H
#define HASH_H
#include "Node.h"

typedef struct entry_n entry_n;
struct entry_n {
    char * key;
    Node * value;
    entry_n * next;
};
/**
typedef struct entry_i entry_i;
struct entry_i {
    int * value;
    char * key;
    entry_i * next;
};
**/

typedef struct hashtable_n hashtable_n;
struct hashtable_n{
    int size;
    entry_n ** table;
};
/**
typedef struct hashtable_i hashtable_i;
struct hastable_i{
    int size;
    entry_i ** table;
};
**/

hashtable_n * htn_create (int size);
//hashtable_i * hti_create (int size);

int htn_hash( hashtable_n * hashtable, char * key);
//int hti_hash( hashtable_i * hashtable, char * key);

entry_n * htn_newpair( char * key, Node * value);
//entry_i * hti_newpair( char * key, int value);

void htn_set( hashtable_n *hastable, char * key, Node * value);
//void hti_set( hashtable_i *hastable, char * key, int value);

Node * htn_get( hashtable_n * hashtable, char * key);
//int hti_get( hashtable_i * hashtable, char * key);

#endif
