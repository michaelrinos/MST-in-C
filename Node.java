import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

/**
 * Class representing a node in a graph.
 * 
 * @author Michael Rinos mer8503
 */
public class Node {

	private String name;
    private int marked = 0;
	private List<Node> neighbors;
    private Map<String, Integer> weights;

    /**
	 * Constructor.  Initialized with an empty list of neighbors.
	 * 
	 * @param name string representing the name associated with the node.
	 */
	public Node(String name) {
		this.name = name;
		this.neighbors = new LinkedList<Node>();
        this.weights = new HashMap<>();
	}

	/**
	 * Get the String name associated with this object.
	 * 
	 * @return name.
	 */
	public String getName() { 
		return name;
	}

	/**
	 * Add a neighbor to this node.  Checks if already present, and does not
	 * duplicate in this case.
	 * 
	 * @param n: node to add as neighbor.
	 */
	public void addNeighbor(Node n, int weight) {
		if(!neighbors.contains(n)) {
            this.weights.put(n.getName(), weight);
			neighbors.add(n);
		}
	}

	/**
	 * Method to return the adjacency list for this node containing all 
	 * of its neighbors.
	 * 
	 * @return the list of neighbors of the given node
	 */
	public List<Node> getNeighbors() { 
		return new LinkedList<Node>(neighbors);
	}


    /**
     * @return if node has been seen yet
     */
    public int getMarked() {
        return marked;
    }

    /**
     * @param marked set if this node has been seen
     */
    public void setMarked(int marked) {
        this.marked = marked;
    }

	/**
	 * Method to generate a string associated with the node, including the 
	 * name of the node followed by the names of its neighbors.  Overrides
	 * Object toString method.
	 * 
	 * @return string associated with the node.
	 */
	@Override
	public String toString() { 
		String result;
		result = name + "-> ";

		for(Node nbr : neighbors) { 
			result = result + nbr.getName() +"(" + weights.get(nbr.getName()) + ")" + " ";
		}
		return result;
	}

	/**
	 *  Two Node's are equal if they have the same name.
	 *  @param other The other object to check equality with
	 *  @ return true if equal; false otherwise
	 */
	@Override
	public boolean equals(Object other) {
		boolean result = false;
		if (other instanceof Node) {
			Node n = (Node) other;
			result = this.name.equals(n.name);
		}
		return result;
	}

	/**
	 * The hash code of a Node is just the hash code of the name,
	 * since no two node's can have the same name.
	 */
	@Override
	public int hashCode() {
		return this.name.hashCode();
	}
}
