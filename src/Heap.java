import java.time.chrono.MinguoEra;
import java.util.Arrays;
import java.util.NoSuchElementException;

class Heap
{
    /** The number of children each node has **/
    private static final int d = 2;
    private int heapSize;
    private MinHeapNode[] heap;

    /** Constructor **/
    public Heap(int capacity)
    {
        heapSize = 0;
        heap = new MinHeapNode[capacity + 1];
        Arrays.fill(heap, new MinHeapNode(new Node("-1"),Integer.MAX_VALUE));
    }

    /** Function to check if heap is empty **/
    public boolean isEmpty( )
    {
        return heapSize == 0;
    }

    /** Check if heap is full **/
    public boolean isFull( )
    {
        return heapSize == heap.length;
    }

    /** Clear heap */
    public void makeEmpty( )
    {
        heapSize = 0;
    }

    /** Function to  get index parent of i **/
    private int parent(int i)
    {
        return (i - 1)/d;
    }

    /** Function to get index of k th child of i **/
    private int kthChild(int i, int k)
    {
        return d * i + k;
    }

    /** Function to insert element */
    public void insert(MinHeapNode x)
    {
        if (isFull( ) )
            throw new NoSuchElementException("Overflow Exception");
        /** Percolate up **/
        heap[heapSize++] = x;
        heapifyUp(heapSize - 1);
    }

    /** Function to find least element **/
    public MinHeapNode findMin( )
    {
        if (isEmpty() )
            throw new NoSuchElementException("Underflow Exception");
        return heap[0];
    }

    /** Function to delete min element **/
    public MinHeapNode deleteMin()
    {
        MinHeapNode keyItem = heap[0];
        delete(0);
        return keyItem;
    }

    /** Function to delete element at an index **/
    public MinHeapNode delete(int ind)
    {
        if (isEmpty() )
            throw new NoSuchElementException("Underflow Exception");
        MinHeapNode keyItem = heap[ind];
        heap[ind] = heap[heapSize - 1];
        heapSize--;
        heapifyDown(ind);
        return keyItem;
    }

    /** Function heapifyUp  **/
    private void heapifyUp(int childInd)
    {
        MinHeapNode tmp = heap[childInd];
        while (childInd > 0 && tmp.compareTo(heap[parent(childInd)])< 0)
        {
            heap[childInd] = heap[ parent(childInd) ];
            childInd = parent(childInd);
        }
        heap[childInd] = tmp;
    }

    /** Function heapifyDown **/
    private void heapifyDown(int ind)
    {
        int child;
        MinHeapNode tmp = heap[ ind ];
        while (kthChild(ind, 1) < heapSize)
        {
            child = minChild(ind);
            if (heap[child].compareTo(tmp) < 0)
                heap[ind] = heap[child];
            else
                break;
            ind = child;
        }
        heap[ind] = tmp;
    }

    /** Function to get smallest child **/
    private int minChild(int ind)
    {
        int bestChild = kthChild(ind, 1);
        int k = 2;
        int pos = kthChild(ind, k);
        while ((k <= d) && (pos < heapSize))
        {
            if (heap[pos].compareTo(heap[bestChild]) < 0)
                bestChild = pos;
            pos = kthChild(ind, k++);
        }
        return bestChild;
    }

    /** Function to print heap **/
    public void printHeap()
    {
        System.out.println("\nHeap = ");
        for (int i = 0; i < heapSize; i++)
            System.out.println(heap[i].getNode().getName()+": "+heap[i] +" ");
        System.out.println();
    }
    public boolean contains(MinHeapNode who){
        for (int i = 0; i < heapSize ; i++) {
            MinHeapNode temp = heap[i];
            if (temp.equals(who)){
                return true;
            }
        }
        return false;
    }
    public boolean decreaseKey(MinHeapNode who) {
        for (int i = 0; i < heap.length; i++) {
            MinHeapNode temp = heap[i];
            if (temp.getNode().equals(who.getNode())) {
                temp.setKey(who.getKey());
                heapifyUp(i);
                return true;
            }
        }
        return false;
    }
}