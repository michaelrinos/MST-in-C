/// \file test_table.c
/// \brief A test program for the hash table.

#include <assert.h>  // assert
#include <stdio.h>   // printf, fprintf
#include <stdlib.h>  // rand, srand, EXIT_SUCCESS
#include <string.h>  // strcmp
#include <time.h>    // time
#include "hash.h"    // longHash, longEquals, longStrPrint, strHash, strEquals
                     // strLongPrint, longlongPrint
#include "table.h"   // create, destroy, dump, get, has, put


/// Test function for c-string keys with long values.  It doesn't re-test
/// a put update, keys, or values
void testStrLong() {
    // Same data as the first, just associated the other way
    char* names[] = {"ten","twenty","thirty","forty","fifty","sixty","seventy",
            "eighty","ninety","one hundred","one hundred ten","one hundred twenty",
            "one hundred thirty","one hundred forty","one hundred fifty",
            "one hundred sixty"};
    long elements[] = {10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160};
    int NUM_ELEMENTS = INITIAL_CAPACITY;
    char* missing = "missing";

    printf("testStrInt()...\n");
    Table* t = create(strHash, strEquals, strLongPrint);

    // rehash happens with 13th name, "one hundred thirty"
    for (int i=0; i<NUM_ELEMENTS; ++i) {
        put(t, (void*)names[i], (void*)elements[i]);
    }
    dump(t, true);

    // check that all keys are found
    for (int i=0; i<NUM_ELEMENTS; ++i) {
        printf("has(%s)? %d\n", names[i], has(t, (void*)names[i]));
    }
    printf("has(missing)? %d\n", has(t, missing));  // missing key

    // check that all values are retrievable for all keys
    for (int i=0; i<NUM_ELEMENTS; ++i) {
        printf("get(%s): %lu\n", names[i], (long)get(t, (void*)names[i]));
    }
    
    dump(t, true);
    destroy(t);
    
}

/// The main function runs the three test functions.
/// Usage: test_table #
/// @param argc command line argument count
/// @param argv command line arguments
/// @return EXIT_SUCCESS
int main(int argc, char* argv[]) {
    testStrLong();  // first test for long keys and c-string values
    // If no number is specified on the command line, seed on current time
    int seed = time(0);
    if (argc == 2) {
        seed = atoi(argv[1]);
    }
    printf("Seed for error: %d\n", seed);

    return EXIT_SUCCESS;
}
