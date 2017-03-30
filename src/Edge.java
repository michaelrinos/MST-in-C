/**
 * Created by michael on 3/3/2016.
 */
public class Edge implements Comparable<Edge> {
    private int weight;
    private int row;
    private int col;

    public Edge(int weight, int row, int col){
        this.weight = weight;
        this.row = row;
        this.col = col;
    }

    public int getWeight(){return this.weight;}
    public int getRow(){return this.row;}
    public int getCol(){return this.col;}

    @Override
    public String toString() {
        return Integer.toString(row) + " " +Integer.toString(col) + " weight = " +Integer.toString(weight) +"\n";
    }

    @Override
    public int compareTo(Edge o) {
        int result = this.weight - o.weight;
        if (result == 0){
            if (this.row - o.row == 0){
                return this.col - o.col;
            } else
                return this.row -o.row;
        }
        else
            return result;
    }
}