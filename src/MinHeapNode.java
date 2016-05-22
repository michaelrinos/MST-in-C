/**
 * Created by Owner on 5/6/2016.
 */
public class MinHeapNode implements Comparable<MinHeapNode>{

    private Node node;
    private int key;

    public MinHeapNode(){
        key = Integer.MAX_VALUE;
    }

    public MinHeapNode(Node n, int k){
        this.node = n;
        this.key = k;
    }


    // Getters and Setters
    public int getKey() {
        return key;
    }

    public void setKey(int key) {
        this.key = key;
    }

    public Node getNode() {
        return node;
    }

    public void setNode(Node node) {
        this.node = node;
    }

    @Override
    public String toString() {
        return "MinHeapNode{" +
                "node=" + node +
                ", key=" + key +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        boolean result = false;
        if (o instanceof MinHeapNode){
            MinHeapNode n = (MinHeapNode) o;
            result = this.node.equals(n.node);
        }
        return result;
    }

    @Override
    public int compareTo(MinHeapNode o) {
        return this.key-o.key;
    }
}
