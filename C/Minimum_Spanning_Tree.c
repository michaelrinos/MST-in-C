#include "hash.h"
#include "Maze.h"
#include "Edge.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>






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
void quickSort(Edge * arr, int low, int high, int length) {
    if (arr == NULL || length == 0 || low >= high) return;
    int middle = low + (high - low) / 2;            // pick the pivot
    Edge pivot = arr[middle];
    int i = low, j = high;                          // make left < pivot and right > pivot
    while (i <= j) {
        while (compareTo(&pivot, &arr[i]) > 0) i++;   //pivot.compareTo(arr[i]) > 0) i++;
        while (compareTo(&pivot, &arr[j]) < 0) j++;   //pivot.compareTo(arr[j]) < 0) j--;
        if (i <= j) {
            Edge temp = arr[i];
            arr[i++] = arr[j];
            arr[j--] = temp;
        }
    }
    // recursively sort two sub parts
    if (low < j) quickSort(arr, low, j);
    if (high > i) quickSort(arr, i, high);
}


/**
* Count Sort sorts a list of Edge objects by first counting
* each occurrence of similar edges then placing the edges
* into a new array in sorted order
* @param a The edge array to be sorted
* @param k The size of the edge array to be sorted
*/
void countSort(Edge * a, int k, int length) {
    Edge copy[length];
    int c[k];
    for (int i = 0; i < length; i++) {
        copy[i] = a[i];
        c[ copy[i].weight ]++;
    }
    for (int i = 1; i < k; i++)
        c[i] += c[i-1];
    for (int i = length-1; i >= 0; i--)
        a[--c[ copy[i].weight ]] = copy[i];
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

    //int tWeight = 0;
    /**
    for (Edge temp : arr){
        if (printEdges)
            printf(temp);
        tWeight+=temp.getWeight();
        }
        if (!printEdges)
            printf("\n");

        switch (korp){
            case 1:
                printf( "\nTotal weight of MST using Kruskal:  %d\n", tWeight);
                printf( "Runtime: %lu milliseconds\n\n", runTime");
                break;
            case 2:
                printf( "\nTotal weight of MST using Prim: %d\n", tWeight);
                printf( "Runtime: %lu milliseconds\n\n", runTime");
                break;
        }
    **/
}

/**
* Function used to time and sort a array of Edges
* @param g The Maze which holds the adjacency list/matrix
* @param lorm Integer representing if the list of objects came from the adjacency list/matrix
* @param sort Integer representing which sort to use
* @param printEdges Boolean indicating whether to print the neighbors of each node
* @return the sorted list
*/
void Sorter(Maze * maze, int korp, int lorm, int sort, int printEdges, int numbers){
    time_t startTime;
    time_t endTime;
    //Edge lst[numbers];
    Edge * lst;
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
            switch (sort) {
                case 1:
                    insertionSort(lst);
                    break;
                case 2:
                    //countSort(lst, numbers + 1);
                    break;
                case 3:
                    //quickSort(lst, 0, lst.length - 1);
                    break;
            }
            //MST = kruskal(lst);
            endTime = time(0);
            break;
        case 2:
            switch (lorm){
                case 1:
                    lst = getMatrix(maze);

                    //temp = getMatrixNodes();
                    //MST = prim(temp);
                    break;
                case 2:
                    lst = getMatrix(maze);

                    //temp = getListNodes();
                    //MST = prim(temp);
                    break;
            }
            break;
    }

    //LinkedList<Edge> krus = kruskal(lst);
    printSorts(MST, korp,lorm, sort, (endTime-startTime), printEdges);
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
        printf("n must be greater than 1");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d", &seed);                                //Get seed value
    fscanf(fp, "%lf", &p);                                  //Get p value
    if (p < 0 || p > 1){                                    //Check n value is valid
        printf("p must be between 0 and 1");
        exit(EXIT_FAILURE);
    }

    printf("n %d, seed %d p %f", n, seed, p); 

    fclose(fp); //be kind rewind


    int numbers = n;
    int print=0;
    if (n < 10)
        print = 1;
    
    const time_t startTime = time(0);
    //Init maze
    Maze * maze = create_maze(numbers);
    generate(maze, n, seed, p);
    printf("Maze %d", maze->count);
    const time_t endTime = time(0);
    
    if ( print ) {
        printf("\nTEST: n= %d, seed=%d, p=%f\n", numbers, seed, p);
        printf("Time to generate the graph: %lu milliseconds\n\n", (endTime - startTime));
        printMatrix(maze);
        printList(maze);
        DFSInfo(maze);

        /**
		sorter(g, 1, 1, 1, print);
        sorter(g, 1, 1, 2, print);
        sorter(g, 1, 1, 3, print);
        sorter(g, 1, 2, 1, print);
        sorter(g, 1, 2, 2, print);
        sorter(g, 1, 2, 3, print);

        sorter(g, 2, 1, 1, print);
        sorter(g, 2, 2, 1, print);
        **/

    } else {
        printf("\nTEST: n= %d, seed=%d, p=%f\n", numbers, seed, p);
        printf("Time to generate the graph: %lu milliseconds\n\n", (endTime - startTime));
        
        /**
        sorter(g, 1, 1, 1, print);
        sorter(g, 1, 1, 2, print);
        sorter(g, 1, 1, 3, print);
        sorter(g, 1, 2, 1, print);
        sorter(g, 1, 2, 2, print);
        sorter(g, 1, 2, 3, print);

        sorter(g, 2, 1, 1, print);
        sorter(g, 2, 2, 1, print);
        **/

    }

    
    return 0;
}
