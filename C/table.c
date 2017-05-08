#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/// Create a new hash table.
/// @param hash The key's hash function
/// @param equals The key's equal function for comparison
/// @param print A print function for the key/value, used for dump debugging
/// @exception Assert fails if can't allocate space
/// @return A newly created table
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


/// Destroy a table 
/// @param t The table to destroy
void destroy(Table* t){
	for (unsigned int i =0; i < t->capacity;i++){
		free(t->table[i]);
	}
	free(t->table);
	free(t);
}

/// Print out information about the hash table (size,
/// capacity, collisions, rehashes).  If full is
/// true, it will also print out the entire contents of the hash table,
/// using the registered print function with each non-null entry.
/// @param t The table to display
/// @param full Do a full dump of entire table contents

void dump(Table* t, bool full){
	printf("Size: %zu\n", t->size );
	printf("Capacity: %zu\n", t->capacity );
	if (full){
		for (unsigned long i = 0; i < t->capacity; i++){
			if(t->table[i]==NULL){
				printf("%lu: null\n",i);
				
			}
			else{
				printf("%lu: (", i);
				t->print(t->table[i]->key,t->table[i]->value);
				printf(")\n");
			}
		}
	}
}

/// Get the value associated with a key from the table.  This function
/// uses the registered hash function to locate the key, and the
/// registered equals function to check for equality.
/// @pre The table must have the key, or else it will assert fail
/// @param t The table
/// @param key The key
/// @return The associated value of the key
void* get(Table* t, void* key){
	long index =(t->hash(key)%(t->capacity));
	long startIndex = (t->hash(key)%(t->capacity));
	while(t->table[index] != NULL && !t->equals(t->table[index]->key,key)){
		index = ((index+1) % (t->capacity));
		if (index == startIndex){
			assert(NULL);
		}
	}
    if (t->table[index])
    	return t->table[index]->value;
    return NULL;
}


/// Check if the table has a key.  This function uses the registered hash
/// function to locate the key, and the registered equals function to
/// check for equality.
/// @param t The table
/// @param key The key
/// @return Whether the key exists in the table.
bool has(Table* t, void* key){
	long index =(t->hash(key)%(t->capacity));
	
	long startIndex = (t->hash(key)%(t->capacity));
	while(t->table[index] != NULL && !t->equals(t->table[index]->key,key)){
		index = ((index+1) % (t->capacity));
		if (index == startIndex){
			return (bool)false;
		}
	}
	return t->table[index] != NULL;
}


/// Get the collection of keys from the table.  This function allocates
/// space to store the keys, which the caller is responsible for freeing.
/// @param t The table
/// @exception Assert fails if can't allocate space
/// @return A dynamic array of keys
void** keys(Table* t){
	void** daKeys = calloc(t->size,sizeof(Entry*));
	if (daKeys==NULL){
		assert(NULL);
	}
	size_t count =0;
	size_t index=0;
	while(index < t->capacity){
		if (t->table[index]== NULL){

		}
		else {
			daKeys[count] = t->table[index]->key;
			count++;
		}
		index = ((index+1) % (t->capacity+1));
	}
	return daKeys;
}


/// Add a key value pair to the table, or update an existing key's value.
/// This function uses the registered hash function to locate the key,
/// and the registered equals function to check for equality.
/// @param t The table
/// @param key The key
/// @param value The value
/// @exception Assert fails if can't allocate space
/// @return The old value in the table, if one exists.
void* put(Table* t, void* key, void* value){
	unsigned long hold = t->hash(key) % t->capacity;
	while (t->table[hold] != NULL){
		
		
		if (t->equals(t->table[hold]->key, key)){
			void* temp = t->table[hold]->value;
			t->table[hold]->value = value;
			return temp;
		}
		hold = ((hold+1) % (t->capacity));
	}

	Entry* new = (Entry*) malloc(sizeof(Entry));
	if (new == NULL){
		fprintf(stderr, "table::put() failed to allocate space");
		assert(NULL);
	}
	new->key = key;
	new->value = value;
	t->table[hold] = new;
	t->size++;
	// rehash
	
	if(t->size>=t->capacity * LOAD_THRESHOLD){
		size_t oldCap = t->capacity;
		Entry** oldTable = t->table;

		t->capacity = oldCap*RESIZE_FACTOR;
		t->table = (Entry**)(calloc(t->capacity,sizeof(Entry*)));
		t->size=0;

		for (size_t i = 0; i<oldCap; ++i){
			if(oldTable[i]!=NULL){
				put(t, oldTable[i]->key, oldTable[i]->value);
				//free(oldTable[i]);
			}

		}
		free(oldTable);
		
	}
	
	return NULL;

}

/// Get the collection of values from the table.  This function allocates
/// space to store the values, which the caller is responsible for freeing.
/// @param t The table
/// @exception Assert fails if can't allocate space
/// @return A dynamic array of values
void** values(Table* t){
	void** daKeys = calloc(t->size,sizeof(Entry*));
	size_t count =0;
	size_t index=0;
	while(index < t->capacity){
		if (t->table[index]== NULL){
		}
		else {
			daKeys[count] = t->table[index]->value;
			count++;
		}
		index = ((index+1) % (t->capacity+1));
	}
	return daKeys;
}
