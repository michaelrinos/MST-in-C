#ifndef HASH_H
#define HASH_H

typedef struct entry_s entry_s;
struct entry_s {
    char * key;
    char * value;
    entry_s * next;

};

struct hashtable_s{
    int size;
    entry_s ** table;
};

typedef struct hashtable_s hashtable_s;

hashtable_s * ht_create (int size);

int ht_hash( hashtable_s * hashtable, char * key);

entry_s * ht_newpair( char * key, char * value);

void ht_set( hashtable_s *hastable, char * key, char * value);

char * ht_get( hashtable_s * hashtable, char * key);

#endif
