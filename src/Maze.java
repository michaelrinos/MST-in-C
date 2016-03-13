import java.io.FileNotFoundException;
import java.lang.reflect.Array;
import java.util.*;


/**
 * Graph class.  Holds representation of a graph as well as functions to
 * interact with the graph.
 *
 * @author Michael Rinos mer8503
 */
public class Maze {

    private static final int MIN_WEIGHT = 1;
    private Map<String, Node> graph;
    private int[] predecessors;
    private int MAX_WEIGHT;
    private int matrix[][];
    private int count;


    /**
     * Constructor.  Loads graph from a given filename.  Assumes that each line
     * in the input file contains the names of two nodes.  Creates nodes
     * as necessary as well as undirected edges between the nodes.
     * Returns the graph in the form of a map having the names of the
     * nodes as keys, and the nodes themselves as values.
     *
     * @param n the number of nodes in the graph
     * @param seed seed value for random number generator
     * @param p the value which determines if there is a weight for a node
     */
    public Maze(int n, int seed, float p) throws FileNotFoundException, InterruptedException {
        // create the graph
        graph = new HashMap<String, Node>();

        MAX_WEIGHT = n;
        predecessors = new int[n];
        predecessors[0] = -1;


        for (int r = 0; r < n; r++) {
            String name = Integer.toString(r);
            graph.put(name, new Node(name));
        }

        Random edgeRand = new Random(seed);
        Random weightRand = new Random(2 * seed);
        while (count != n) {
            this.matrix =new int[n][n];
            count = 0;
            int range = MAX_WEIGHT - MIN_WEIGHT + 1;
            for (int i = 0; i < n; i++) {
                for (int j = i; j < n; j++) {
                    if (i == j) continue;
                    double r = edgeRand.nextDouble();
                    if (r <= p) {
                        int weight = MIN_WEIGHT + weightRand.nextInt(range);
                        //Adds a neighbor to adjacency matrix
                        matrix[i][j] = weight;
                        matrix[j][i] = weight;
                        //Adds a neighbor to actual graph
                        graph.get(Integer.toString(i)).addNeighbor(graph.get(Integer.toString(j)), weight);
                        graph.get(Integer.toString(j)).addNeighbor(graph.get(Integer.toString(i)), weight);
                    }
                }
            }
            count = canReachDFS(Integer.toString(0),0);
        }
    }


    /**
     * Method to generate a string associated with the graph.  The string
     * comprises one line for each node in the graph. Overrides
     * Object toString method.
     *
     * @return string associated with the graph.
     */
    public String toString() {
        String result = "";
        for (String name : graph.keySet()) {
            result = result + graph.get(name) + "\n";
        }
        return result;
    }

    public int canReachDFS(String start, int count) {

        Node startNode = graph.get(start);
        int name =Integer.parseInt(start);
        if (startNode.getMarked() == 0){
            count+=1;
        }

        startNode.setMarked(1);
        for (Node temp : startNode.getNeighbors()) {
            if (temp.getMarked() == 0) {
                int tName = Integer.parseInt(temp.getName());
                predecessors[tName] = name;
                count = canReachDFS(temp.getName(), count);
            }
        }
        startNode.setMarked(2);

        return count;
    }

    public void printMatrix(){
        System.out.println("The graph as an adjacency matrix:\n");
        for (int i = 0; i < MAX_WEIGHT; i++) {
            System.out.print(" ");
            for (int j = 0; j < MAX_WEIGHT; j++) {
                if (j == 0) System.out.print(matrix[i][j]);
                else System.out.print("   "+matrix[i][j]);
            }
            System.out.println("\n");
        }
    }

    public void printList() {
        System.out.println("The graph as an adjacency list:");
        for (int i = 0; i < MAX_WEIGHT; i++) {
            System.out.println(graph.get(Integer.toString(i)));
        }
        System.out.println();
    }

    public void DFSInfo(){
        System.out.println("Depth-First Search:");
        System.out.println("Vertices:  ");
        for (int i = 0; i < MAX_WEIGHT; i++) {
            System.out.print(" "+i);
        }
        System.out.println("\nPredecessors: ");
        for (int temp: predecessors){
            System.out.print(temp + " ");
        }
        System.out.println();
    }

    public Edge[] getMatrix() {
        ArrayList<Edge> edges = new ArrayList<>();
        for (int i = 0; i < MAX_WEIGHT; i++) {
            for (int j = i; j < MAX_WEIGHT; j++) {
                if (i == j) continue;
                if (matrix[i][j] == 0) continue;
                else {
                    edges.add(new Edge(matrix[i][j], i, j));
                }
            }
        }
        Edge[] temp = new Edge[edges.size()];
        temp = edges.toArray(temp);
        return temp;
    }

    public Edge[] getList(){
        ArrayList<Edge> edges = new ArrayList<>();
        for (int i = 0; i < MAX_WEIGHT-1 ; i++) {
            for (Node temp : graph.get(Integer.toString(i)).getNeighbors()){
                if (Integer.parseInt(temp.getName()) > i) {
                    edges.add(new Edge(
                            temp.weights.get(Integer.toString(i)),
                            i,
                            Integer.parseInt(temp.getName())));
                }
            }
        }
        Edge[] temp = new Edge[edges.size()];
        temp = edges.toArray(temp);
        return temp;
    }
}