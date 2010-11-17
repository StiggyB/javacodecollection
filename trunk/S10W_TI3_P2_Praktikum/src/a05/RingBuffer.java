package a05;

/*************************************************************************
 *  
 *  Ring buffer (fixed size queue) implementation using a circular array
 *  (array with wrap-around).
 *  Source: Robert Sedgewick and Kevin Wayne. Found in the WWW
 *  
 *************************************************************************/

//import java.util.Iterator;
//import java.util.NoSuchElementException;

// suppress unchecked warnings in Java 1.5.0_6 and later
@SuppressWarnings("unchecked")
public class RingBuffer<Item> implements /*Iterable<Item>,*/ I_Ringbuffer<Item> {
    private Item[] a; // queue elements
    private int N = 0; // number of elements on queue
    private int first = 0; // index of first element of queue
    private int last = 0; // index of next available slot

    // cast needed since no generic array creation in Java
    public RingBuffer(int capacity) {
        if(capacity >=0)
        a = (Item[]) new Object[capacity];
        else System.err.printf("False Queue length!\n");
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public boolean isFull() {
        return N == a.length;
    }

    public Item peek() {
        if (isEmpty()) {
            throw new RuntimeException("Ring buffer underflow");
        }
        Item item = a[first];
        return item;
    }

    public void enqueue(Item item) {
        if (N == a.length) {
            System.err.printf("Ring buffer full!\n");
            throw new RuntimeException("Ring buffer overflow");
        }
        a[last] = item;
        last = (last + 1) % a.length; // wrap-around
        N++;
    }

    // remove the least recently added item - doesn't check for underflow
    public Item dequeue() {
        if (isEmpty()) {
            System.err.printf("Ring buffer empty!\n");
            throw new RuntimeException("Ring buffer underflow");
        }
        Item item = a[first];
        a[first] = null; // to help with garbage collection
        N--;
        first = (first + 1) % a.length; // wrap-around
        return item;
    }

//    public Iterator<Item> iterator() {
//        return new RingBufferIterator();
//    }
//
//    // an iterator, doesn't implement remove() since it's optional
//    private class RingBufferIterator implements Iterator<Item> {
//        private int i = 0;
//
//        public boolean hasNext() {
//            return i < N;
//        }
//
//        public void remove() {
//            throw new UnsupportedOperationException();
//        }
//
//        public Item next() {
//            if (!hasNext())
//                throw new NoSuchElementException();
//            return a[i++];
//        }
//    }
    
    public String toString(){
        return "Ring Buffer initialized";
    }

    public static void main(String[] args) {

    }

}
