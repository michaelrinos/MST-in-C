import java.io.File;
import java.io.FileNotFoundException;
import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Minimum_Spanning_Tree {
    private static int numbers;

    public static void main(String[] args) throws InterruptedException {
        if (args.length != 1) {
            System.out.println("Input file not found");
            System.exit(0);
        }
        try {
            String filename = args[0];
            File file = new File(filename);
            Scanner in = new Scanner(file);
            int n = 0;
            int seed = 0;
            float p = 0;
            while (in.hasNextLine()) {
                try {
                    n = Integer.parseInt(in.nextLine());
                    if (n < 2) {
                        System.out.println("n must be greater than 1");
                        System.exit(1);
                    }
                    seed = Integer.parseInt(in.nextLine());
                } catch (NumberFormatException e) {
                    System.out.println("n and seed must be integers");
                    System.exit(1);
                }
                try {
                    p = Float.parseFloat(in.nextLine());
                    if (p < 0 || p > 1) {
                        System.out.println("p must be between 0 and 1");
                        System.exit(1);
                    }
                } catch (NumberFormatException e) {
                    System.out.println("p must be a real number");
                    System.exit(1);
                } catch (NoSuchElementException e) {
                    System.out.println("Missing the p value");
                    System.exit(1);
                }
            }
            numbers = n;
            boolean print = false;
            if (n < 10) {
                print = true;
            }
            //print = true;
            final long startTime = System.currentTimeMillis();
            Maze g = new Maze(n, seed, p);
            final long endTime = System.currentTimeMillis();

            if (print) {
                System.out.println();
                System.out.println("TEST: n=" + n + ", seed=" + seed + ", p=" + p);
                System.out.println("Time to generate the graph: " + (endTime - startTime) + " milliseconds\n");
                g.printMatrix();
                g.printList();
                g.DFSInfo();

                sorter(g, 1, 1, print);
                sorter(g, 1, 2, print);
                sorter(g, 1, 3, print);
                sorter(g, 2, 1, print);
                sorter(g, 2, 2, print);
                sorter(g, 2, 3, print);

            } else {
                System.out.println();
                System.out.println("TEST: n=" + n + ", seed=" + seed + ", p=" + p);
                System.out.println("Time to generate the graph: " + (endTime - startTime) + " milliseconds\n");

                sorter(g, 1, 1, print);
                sorter(g, 1, 2, print);
                sorter(g, 1, 3, print);
                sorter(g, 2, 1, print);
                sorter(g, 2, 2, print);
                sorter(g, 2, 3, print);
            }

        } catch (FileNotFoundException e) {
            System.out.println("Input file not found");
            System.exit(0);
        }
    }

    /**
     * Function used to time and sort a array of Edges
     * @param g The Maze which holds the adjacency list/matrix
     * @param lorm Integer representing if the list of objects came from the adjacency list/matrix
     * @param sort Integer representing which sort to use
     * @param printEdges Boolean indicating whether to print the neighbors of each node
     * @return the sorted list
     */
    public static Edge[] sorter(Maze g, int lorm, int sort, boolean printEdges) {
        final long startTime;
        final long endTime;
        Edge[] lst;
        switch (lorm){
            case 1:
                startTime = System.currentTimeMillis();
                lst = g.getMatrix();
                break;
            case 2:
                startTime = System.currentTimeMillis();
                lst = g.getList();
                break;
            default:
                startTime = 0;
                lst = g.getMatrix();
                break;
        }
        switch (sort) {
            case 1:
                insertionSort(lst);
                endTime = System.currentTimeMillis();
                break;
            case 2:
                countSort(lst, numbers + 1);
                endTime = System.currentTimeMillis();
                break;
            case 3:
                quickSort(lst, 0, lst.length - 1);
                endTime = System.currentTimeMillis();
                break;
            default:
                endTime = 0;
                break;
        }
        LinkedList<Edge> krus = kruskal(lst);
        printSorts(krus, lorm, sort, (endTime-startTime), printEdges);
        return lst;
    }

    /**
     * Helper function to print a sorted list of objects
     * @param arr The array of items to print
     * @param morl Integer representing adjacency list or adjacency matrix items
     * @param sort The sort used to sort the array of items
     * @param runTime The time taken for converting from adjacency list/matrix and sorting
     * @param printEdges Weather or not to print the neighbors of each node
     */
    public static void printSorts(LinkedList<Edge> arr, int morl, int sort, long runTime, boolean printEdges) {
        System.out.println("===================================");
        System.out.print("KRUSKAL WITH ");
        switch (morl){
            case 1:
                System.out.print("MATRIX USING ");
                break;
            case 2:
                System.out.print("LIST USING ");
                break;
        }
        switch (sort) {
            case 1:
                System.out.println("INSERTION SORT");
                break;
            case 2:
                System.out.println("COUNT SORT");
                break;
            case 3:
                System.out.println("QUICKSORT");
                break;
        }
        /*int tWeight = 0;
        for (int i = 0; i < arr.length; i++) {
            Edge temp = arr[i];
            if (printEdges)
                System.out.print(temp);
            tWeight+=temp.getWeight();
        }
        if (!printEdges)
            System.out.println();*/

        int tWeight = 0;
        for (Edge temp : arr){
            if (printEdges)
                System.out.print(temp);
            tWeight+=temp.getWeight();
        }
        if (!printEdges)
            System.out.println();

        System.out.println("Total weight = "+tWeight);
        System.out.println("Runtime: "+ runTime +" milliseconds\n");
    }

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
    public static void quickSort(Edge[] arr, int low, int high) {
        if (arr == null || arr.length == 0 || low >= high) return;
        int middle = low + (high - low) / 2;            // pick the pivot
        Edge pivot = arr[middle];
        int i = low, j = high;                          // make left < pivot and right > pivot
        while (i <= j) {
            while (pivot.compareTo(arr[i]) > 0) i++;
            while (pivot.compareTo(arr[j]) < 0) j--;
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
     * Insertion Sort sorts a list of edges by taking the smallest/
     * larggest item in the list and then placing it at the beginning/end
     * of the list and repeating this procedure till all items in the list
     * are in sorted order
     * @param arr The edge array to be sorted
     */
    public static void insertionSort(Edge[] arr) {
        int i, j;
        Edge newValue;
        for (i = 1; i < arr.length; i++) {
            newValue = arr[i];
            j = i;
            while (j > 0 && newValue.compareTo(arr[j - 1]) < 0) {
                arr[j] = arr[j - 1];
                j--;
            }
            arr[j] = newValue;
        }
    }

    /**
     * Count Sort sorts a list of Edge objects by first counting
     * each occurrence of similar edges then placing the edges
     * into a new array in sorted order
     * @param a The edge array to be sorted
     * @param k The size of the edge array to be sorted
     */
    public static void countSort(Edge[] a, int k) {
        Edge[] copy = new Edge[a.length];
        int c[] = new int[k];
        for (int i = 0; i < a.length; i++) {
            copy[i] = a[i];
            c[copy[i].getWeight()]++;
        }
        for (int i = 1; i < k; i++)
            c[i] += c[i-1];
        for (int i = copy.length-1; i >= 0; i--)
            a[--c[copy[i].getWeight()]] = copy[i];
    }

    /**
     * Given a list of sorted edges, add an edge to the MST
     * as long as a cycle is not formed with the previously
     * added edges.
     * @param a The list of sorted edges
     * @return the Minimum spanning tree
     */
    public static LinkedList<Edge> kruskal(Edge[] a){
        Node[] b = new Node[numbers];
        for (int i = 0; i < numbers ; i++) {
            b[i] = new Node(Integer.toString(i));
        }
        int includedCount = 0;
        int edges = 0;
        LinkedList<Edge> MST = new LinkedList<>();
        while (includedCount< numbers-1){
            Node root1 = b[a[edges].getRow()];
            Node root2 = b[a[edges].getCol()];

            if (root1.getp() == null){
                root1.setPredecessor(root1);
            }
            if (root2.getp() == null){
                root2.setPredecessor(root2);
            }

            root1 = find(root1);
            root2 = find(root2);

            if (!(root1.equals(root2))){
                MST.add(a[edges]);
                includedCount+=1;
                Union(root1, root2);
            }
            edges++;
        }
        return MST;
    }

    /**
     * Given a Node in the tree find recursively traverses up the
     * tree until finding the root which it then sets as the
     * root of all children so that when its called on the same
     * Node it doesn't have to traverse up the tree again
     * @param p The root or any of its children of a tree
     * @return The root of the Tree
     */
    public static Node find(Node p) {
        if (!(p.equals(p.getp()))){
            p.setPredecessor(find(p.getp()));
        }
        return p.getp();
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
    public static void Union(Node u, Node v) {
        Node i = find(u);
        Node j = find(v);

        if (i.rank() > j.rank()) {
            j.setPredecessor(i);
        } else {
            i.setPredecessor(j);
            if (i.rank() == j.rank()) {
                j.setRank(j.rank() + 1);
            }
        }
    }

}