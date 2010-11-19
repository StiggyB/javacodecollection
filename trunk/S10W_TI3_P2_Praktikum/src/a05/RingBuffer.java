package a05;

/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 05<br>
 * 
 * Version: V0<br>
 * Aenderungen:
 * 
 * Quellen: API, Robert Sedgewick and Kevin Wayne via WWW , Buch: Java als erste Programmiersprache
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

@SuppressWarnings("unchecked")
public class RingBuffer<Item> implements I_Ringbuffer<Item> {
    private Item[] a; // queue elements
    private int N = 0; // number of elements on queue
    private int first = 0; // index of first element of queue
    private int last = 0; // index of next available slot

    // cast needed since no generic array creation in Java
    public RingBuffer(int capacity) {
        if (capacity >= 0)
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
        if (isFull()) {
            System.err.printf("Ring buffer full!\n");
            throw new RuntimeException("Ring buffer overflow");
        }
        a[last] = item;
        last = (last + 1) % a.length; // wrap-around
        N++;
    }

    public Item dequeue() {
        if (isEmpty()) {
            System.err.printf("Ring buffer empty!\n");
            throw new RuntimeException("Ring buffer underflow");
        }
        Item item = a[first];
        a[first] = null;
        N--;
        first = (first + 1) % a.length; // wrap-around
        return item;
    }

    public String toString() {
        return "Ring Buffer initialized";
    }

    public static void main(String[] args) {

    }

}
