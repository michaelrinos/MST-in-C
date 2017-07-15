#include "hash.h"
#include "Maze.h"
#include "Edge.h"
#include "Heap.h"
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>


int numbers = 0;


///////////////////////////////////////////////////////////////////////////////
//    _____      _           _        _____ _          __  __
//   |  __ \    (_)         ( )      / ____| |        / _|/ _|
//   | |__) | __ _ _ __ ___ |/ ___  | (___ | |_ _   _| |_| |_
//   |  ___/ '__| | '_ ` _ \  / __|  \___ \| __| | | |  _|  _|
//   | |   | |  | | | | | | | \__ \  ____) | |_| |_| | | | |
//   |_|   |_|  |_|_| |_| |_| |___/ |_____/ \__|\__,_|_| |_|
//
///////////////////////////////////////////////////////////////////////////////

Edge * prim(Node * a){
    Node parent[numbers];
    int key[numbers];
    Edge * MST = malloc(numbers * sizeof(Edge));
    Heap * minHeap;
    heap_init(&minHeap);

    for (int i = 1; i < numbers ; i++) {
        Node * n = init_node("-1");
        parent[i] = *n;
        key[i] = INT_MAX;
        MinHeapNode * m = malloc(sizeof(MinHeapNode));
        m->Node = &a[i];
        m->key = key[i];
        heap_add(minHeap, m);
    }

    key[0] = 0;
    MinHeapNode * m = malloc(sizeof(MinHeapNode));
    m->Node = &a[0];
    m->key = key[0];
    heap_add(minHeap, m);


    while ( minHeap->size != 0){                 //!minHeap.isEmpty() ){
        MinHeapNode * u = heap_remove(minHeap);

        Node ** neighbors = u->Node->neighbors;
        for (size_t i = 0; i < u->Node->nSize;i++){
            Node * v = neighbors[i];
            int name = atoi(v->name);
            int weight =  (long) get(v->weights, (void *)u->Node->name);
            MinHeapNode * neighbor = malloc(sizeof(MinHeapNode));
            neighbor->Node = v;
            neighbor->key = key[name];
            if (contains(minHeap, neighbor) // If the node isn't in the MST
                    && weight < key[name]
                    ){
                key[name] = weight;
                
                parent[name] = *(u->Node);
                
                MinHeapNode * t = &(struct MinHeapNode){ .Node = v, .key = weight};
                
                decreaseKey(minHeap, t);
               
            }
        }
        free(u);
    }
    size_t count = 0;
    for (int i = 1; i < numbers ; i++) {
        if ( &parent[i]) {
            char * str = malloc(sizeof(char) * MAX_NUMS);
            sprintf(str, "%d", i);
            Edge * e = malloc(sizeof(Edge));
            
            e->weight = (long) get(parent[i].weights, (void *) str);
            e->row = atoi(parent[i].name);
            e->col = i;
            e->print = printEdge;
            MST[count++] = *e;
        }
    }
    
    deleteHeap(minHeap); 
    return MST;
}





///////////////////////////////////////////////////////////////////////////////
//    _                   _     _         _    _____ _          __  __
//   | |                 | |   | |       | |  / ____| |        / _|/ _|
//   | | ___ __ _   _ ___| |__ | | ____ _| | | (___ | |_ _   _| |_| |_
//   | |/ / '__| | | / __| '_ \| |/ / _` | |  \___ \| __| | | |  _|  _|
//   |   <| |  | |_| \__ \ | | |   < (_| | |  ____) | |_| |_| | | | |
//   |_|\_\_|   \__,_|___/_| |_|_|\_\__,_|_| |_____/ \__|\__,_|_| |_|
//
///////////////////////////////////////////////////////////////////////////////

/**
* Given a Node in the tree find recursively traverses up the
* tree until finding the root which it then sets as the
* root of all children so that when its called on the same
* Node it doesn't have to traverse up the tree again
* @param p The root or any of its children of a tree
* @return The root of the Tree
*/
Node * find(Node * p) {
    Node * pp = p->predecessor;
    if (compareToNode(p, pp) != 0){          //!(p.equals( p.getp() ) )
        Node * daPred = find(pp);
        setPred(p, daPred);
    }
    return p->predecessor;
}

/**
* Union takes two Nodes U and V from which it determined each
* Nodes rank and automatically sets the smaller tree
* as a subtree of the larger tree. If both trees are the
* same size then V becomes the subtree for U and the rank
* of U increments by 1
* @param u A Node in a tree of Nodes
* @param v A Node in a tree of Nodes
*/
void Union(Node * u, Node * v) {
    
    Node * i = find(u);
    Node * j = find(v);

    if (i->rank > j->rank) {
        setPred(j, i);
    } else {
        setPred(i, j);
        //i->predecessor = j;
        if (i->rank == j->rank) {
            j->rank = j->rank + 1;
        }
    }
}

/**
* Given a list of sorted edges, add an edge to the MST
* as long as a cycle is not formed with the previously
* added edges.
* @param a The list of sorted edges
* @return the Minimum spanning tree
*/
Edge * kruskal(Edge * a){
    Node * b[numbers];
    for (int i = 0; i < numbers ; i++) {
        char * str_i = malloc(sizeof(char) * MAX_NUMS);
        sprintf(str_i, "%d", i);        

        Node * n = init_node( str_i );
        b[i] = n;
        free(str_i);
    }

    int includedCount = 0;
    int edges = 0;

    Edge * MST = calloc(numbers, sizeof(Edge));
    int size = 0;

    while (includedCount < numbers-1){
        Node * root1 = b[ a[edges].row ];
        Node * root2 = b[ a[edges].col ];
        
        if (!root1->predSet){
            setPred(root1, root1); 
        }
        

        if (!root2->predSet){
            setPred(root2, root2);
        }

        root1 = find(root1);
        root2 = find(root2);
        
        if ( compareToNode(root1, root2) != 0 ){
            MST[size++] = a[edges];
            includedCount+=1;
            Union( root1 , root2 );
        }
        edges++;
    }

    for (int i = 0; i < numbers; i++){
        deleteNode(b[i]);
    }

    return MST;
}

//////////////////////////////////////////////////////////////////////////////
//
//     _____            _   _                _____ _          __  __
//    / ____|          | | (_)              / ____| |        / _|/ _|
//   | (___   ___  _ __| |_ _ _ __   __ _  | (___ | |_ _   _| |_| |_
//    \___ \ / _ \| '__| __| | '_ \ / _` |  \___ \| __| | | |  _|  _|
//    ____) | (_) | |  | |_| | | | | (_| |  ____) | |_| |_| | | | |
//   |_____/ \___/|_|   \__|_|_| |_|\__, | |_____/ \__|\__,_|_| |_|
//                                   __/ |
//                                  |___/
///////////////////////////////////////////////////////////////////////////////


/**
* Quicksort sorts a list of objects by choosing a trivial point
* in the list then ensuring that everything to the left is smaller
* and everything to the right is greater than or equal to that initial
* point then recursively calling itself on the left and right half of the
* list till only nothing remains then concatenating the lists back into
* sorted order
* @param arr List of objects to be sorted
* @param low The first item in the list
* @param high The last item in the list
*/
void quickSort(Edge * arr, int low, int high) {
    if (arr == NULL || low >= high) return;
    int middle = low + (high - low) / 2;            // pick the pivot
    Edge pivot = arr[middle];
    int i = low, j = high;                          // make left < pivot and right > pivot
    while (i <= j) {
        while (compareTo(&arr[i], &pivot) < 0) i++;   //pivot.compareTo(arr[i]) > 0) i++;
        while (compareTo(&arr[j], &pivot) > 0) j--;   //pivot.compareTo(arr[j]) < 0) j--;
        if (i <= j) {
            Edge temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    // recursively sort two sub parts
    if (low < j) quickSort(arr, low, j);
    if (high > i) quickSort(arr, i, high );
}


/**
* Count Sort sorts a list of Edge objects by first counting
* each occurrence of similar edges then placing the edges
* into a new array in sorted order
* @param a The edge array to be sorted
* @param k The size of the edge array to be sorted
*/
void countSort(Edge * a, int k) {
    Edge copy[k];
    int c[k], i;
    memset(c, 0, sizeof(c));
 

    for (i = 0; i < k; i++) {
        //memcpy(&copy[i], &a[i], sizeof(Edge));
        ++c[ a[i].weight ];
    }
    for (i = 1; i < k; i++)
        c[i] += c[i-1];

    for (i = 0; i < k; i++){
        copy[c[a[i].weight]-1] = a[i];
        --(c[a[i].weight]);
    }

    for (i = 0; i < k; i++){
        a[i] = copy[i];
    }


}

/**
* Insertion Sort sorts a list of edges by taking the smallest/
* larggest item in the list and then placing it at the beginning/end
* of the list and repeating this procedure till all items in the list
* are in sorted order
* @param arr The edge array to be sorted
*/
void insertionSort(Edge * arr, int length) {
    int i, j;
    Edge newValue;
    for (i = 1; i < length; i++) {
        newValue = arr[i];
        j = i;
        while (j > 0 && compareTo(&newValue, &(arr[j - 1]) ) < 0) {
            arr[j] = arr[j - 1];
            j--;
        }
    arr[j] = newValue;
    }
}
 
/**
* Helper function to print a sorted list of objects
* @param arr The array of items to print
* @param morl Integer representing adjacency list or adjacency matrix items
* @param sort The sort used to sort the array of items
* @param runTime The time taken for converting from adjacency list/matrix and sorting
* @param printEdges Weather or not to print the neighbors of each node
*/
void printSorts(Edge * arr,int korp, int morl, int sort, long runTime, int printEdges) {
    printf("===================================\n");
    switch (korp){
        case 1:
            printf("KRUSKAL WITH ");
            switch (morl){
                case 1:
                    printf("MATRIX USING ");
                    break;
                case 2:
                    printf("LIST USING ");
                    break;
            }
            switch (sort) {
                case 1:
                    printf("INSERTION SORT\n");
                    break;
                case 2:
                    printf("COUNT SORT\n");
                    break;
                case 3:
                    printf("QUICKSORT\n");
                    break;
            }
            break;
        case 2:
            printf("PRIM WITH ADJACENCY ");
            switch (morl){
                case 1:
                    printf("MATRIX\n");
                    break;
                case 2:
                    printf("LIST\n");
                    break;
            }
            break;
    }
    int tWeight = 0;
    for (int i = 0; i < numbers-1; i++){
        if (&arr[i]){
            Edge temp = arr[i];
            
            if (printEdges){
                temp.print(&temp);
            }
            tWeight+=temp.weight;
        }
    }
    if (!printEdges)
        printf("\n");

    switch (korp){
        case 1:
            printf( "\nTotal weight of MST using Kruskal:  %d\n", tWeight);
            printf( "Runtime: %lu milliseconds\n\n", runTime);
            break;
        case 2:
            printf( "\nTotal weight of MST using Prim: %d\n", tWeight);
            printf( "Runtime: %lu milliseconds\n\n", runTime);
            break;
    }
    free(arr);
    
}

/**
* Function used to time and sort a array of Edges
* @param g The Maze which holds the adjacency list/matrix
* @param lorm Integer representing if the list of objects came from the adjacency list/matrix
* @param sort Integer representing which sort to use
* @param printEdges Boolean indicating whether to print the neighbors of each node
* @return the sorted list
*/
void sorter(Maze * maze, int korp, int lorm, int sort, int printEdges){
    time_t startTime;
    time_t endTime;
    //Edge lst[numbers];
    Edge * lst;
    Edge * MST;
    Node * temp;
    switch (korp) {
        case 1:
            switch (lorm) {
                case 1:
                    startTime = time(0);
                    lst = getMatrix(maze);
                    break;
                case 2:
                    startTime = time(0);
                    lst = getList(maze);
                    break;
                default:
                    lst = getMatrix(maze);
                    break;
            }
            
            int length = 0;
            for (int i = 0; i < factorial(numbers-1); i++){
                if (lst[i].print){
                    length++;
                }
                else break;
            }
            switch (sort) {
                case 1:
                    insertionSort(lst, length);
                    break;
                case 2:
                    countSort(lst, length);
                    break;
                case 3:
                    quickSort(lst, 0, length);
                    break;
            }
            MST = kruskal(lst);
            free(lst);
            endTime = time(0);
            break;
        case 2:
            switch (lorm){
                case 1:
                    temp = getMatrixNodes(maze);
                    MST = prim(temp);
                    
                    break;
                case 2:
                    temp = getListNodes(maze);
                    MST = prim(temp);
                    break;
            }
            break;
    }

    printSorts(MST, korp, lorm, sort, (endTime-startTime), printEdges);
    //return lst;
} 



int main(int argc, const char* argv[]){
    if( argc !=2){
        printf("Input file not found \n");
        exit(EXIT_FAILURE);
    }
    const char * filename = argv[1];

    FILE * fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Failed to open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    int n, seed;
    double p;

    fscanf(fp, "%d", &n);                                   //Get n value
    if (n < 2){                                             //Check n value is valid
        printf("n must be greater than 1\n");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d", &seed);                                //Get seed value
    if (!seed){
        printf("failed to retrieve seed value\n");
        exit(EXIT_FAILURE);
    }
    fscanf(fp, "%lf", &p);                                  //Get p value
    if (p < 0 || p > 1){                                    //Check n value is valid
        printf("p must be between 0 and 1\n");
        exit(EXIT_FAILURE);
    }

    fclose(fp); //be kind rewind


    numbers = n;
    int print=0;
    if (n < 10)
        print = 1;
    
    const time_t startTime = time(0);
    //Init maze
    Maze * maze = create_maze(numbers);
    generate(maze, n, seed, p);
    const time_t endTime = time(0);
    assert(maze != NULL);
    
    if ( print ) {
        printf("TEST: n= %d, seed=%d, p=%f\n", numbers, seed, p);
        printf("Time to generate the graph: %lu milliseconds\n\n", (endTime - startTime));
        printMatrix(maze);
        printList(maze);
        DFSInfo(maze);

        
		sorter(maze, 1, 1, 1, print);
        sorter(maze, 1, 1, 2, print);
        sorter(maze, 1, 1, 3, print);
        sorter(maze, 1, 2, 1, print);
        sorter(maze, 1, 2, 2, print);
        sorter(maze, 1, 2, 3, print);

        /**
        sorter(maze, 2, 1, 1, print);
        sorter(maze, 2, 2, 1, print);
        **/

    } else {
        printf("\nTEST: n= %d, seed=%d, p=%f\n", numbers, seed, p);
        printf("Time to generate the graph: %lu milliseconds\n\n", (endTime - startTime));
        
        sorter(maze, 1, 1, 1, print);
        sorter(maze, 1, 1, 2, print);
        sorter(maze, 1, 1, 3, print);
        sorter(maze, 1, 2, 1, print);
        sorter(maze, 1, 2, 2, print);
        sorter(maze, 1, 2, 3, print);

        sorter(maze, 2, 1, 1, print);
        sorter(maze, 2, 2, 1, print);

    }
    deleteMaze(maze);

    
    return 0;
}
