package a05;

public interface I_Ringbuffer<Item> {
//    Item[] a; // queue elements
    int N = 0; // number of elements on queue
    int first = 0; // index of first element of queue
    int last = 0; // index of next available slot

    public void enqueue(Item item);

    public Item dequeue();

    public Item peek();

    public boolean isEmpty();

    public boolean isFull();
}
