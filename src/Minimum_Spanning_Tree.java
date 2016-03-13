import java.io.File;
import java.io.FileNotFoundException;
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

    public static void sorter(Maze g, int lorm, int sort, boolean printEdges) {
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
        printSorts(lst, lorm, sort, (endTime-startTime), printEdges);
    }

    public static void printSorts(Edge[] arr, int morl, int sort, long runTime, boolean printEdges) {
        System.out.println("===================================");
        System.out.print("SORTED EDGES WITH ");
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
        int tWeight = 0;
        for (int i = 0; i < arr.length; i++) {
            Edge temp = arr[i];
            if (printEdges)
                System.out.print(temp);
            tWeight+=temp.getWeight();
        }
        if (!printEdges)
            System.out.println();

        System.out.println("Total weight = "+tWeight);
        System.out.println("Runtime: "+ runTime +" milliseconds\n");
    }

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
}