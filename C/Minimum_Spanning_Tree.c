#include "hash.h"
#include "Maze.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



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
                    //insertionSort(lst);
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
