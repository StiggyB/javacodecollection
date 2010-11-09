package a05;

public interface I_Ringbuffer<Item> {
    private Item[] a;            // queue elements
    private int N = 0;           // number of elements on queue
    private int first = 0;       // index of first element of queue
    private int last  = 0;       // index of next available slot
    public void enqueue( Item item);
    public void dequeue( Item item);
    public Item peek ();
    public boolean isEmpty();
    public oolean isFull();
}
