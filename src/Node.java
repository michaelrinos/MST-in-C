// Imports
import java.util.*;

/**
 * Class representing a node in a graph.
 *
 * @author Michael Rinos mer8503
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//         _____ _                 _   _           _
//		  / ____| |               | \ | |         | |
//		 | |    | | __ _ ___ ___  |  \| | ___   __| | ___
//		 | |    | |/ _` / __/ __| | . ` |/ _ \ / _` |/ _ \
//		 | |____| | (_| \__ \__ \ | |\  | (_) | (_| |  __/
//		  \_____|_|\__,_|___/___/ |_| \_|\___/ \__,_|\___|
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

public class Node implements Comparator<Node>, Comparable<Node>{

	private String name;
	private int marked = 0;
	private int rank = 0;
	private Node predecessor;
	private List<Node> neighbors;
	public Map<String, Integer> weights;

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
	 * Getter for the Parent
	 * @return Paremt Node
	 */
	public Node getp() {
		return predecessor;
	}

	/**
	 * Sets the parent node
	 * @param predecessor the parent
	 */
	public void setPredecessor(Node predecessor) { this.predecessor = predecessor;}

	/**
	 * Getter for the rank
	 * @return int the rank
	 */
	public int rank() { return rank;}

	/**
	 * sets the rank of the Node
	 * @param rank
	 */
	public void setRank(int rank) {
		this.rank = rank;
	}

	public int getWeight(String whos){
		return weights.get(whos);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//              ____                 _     _     _              __  __      _   _               _
	//             / __ \               (_)   | |   | |            |  \/  |    | | | |             | |
	//            | |  | |_   _____ _ __ _  __| | __| | ___ _ __   | \  / | ___| |_| |__   ___   __| |___
	//            | |  | \ \ / / _ \ '__| |/ _` |/ _` |/ _ \ '_ \  | |\/| |/ _ \ __| '_ \ / _ \ / _` / __|
	//            | |__| |\ V /  __/ |  | | (_| | (_| |  __/ | | | | |  | |  __/ |_| | | | (_) | (_| \__ \
	//             \____/  \_/ \___|_|  |_|\__,_|\__,_|\___|_| |_| |_|  |_|\___|\__|_| |_|\___/ \__,_|___/
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	@Override
	public int compare(Node o1, Node o2) {
		return Integer.parseInt(o1.getName())-Integer.parseInt(o2.getName());
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

	@Override
	public int compareTo(Node o) {
		return Integer.parseInt(this.getName()) - Integer.parseInt(o.getName());
	}

}