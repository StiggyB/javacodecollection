package a05;

public interface I_Ringbuffer<Item> {

    public void enqueue(Item item);

    public Item dequeue();

    public Item peek();

    public boolean isEmpty();

    public boolean isFull();
}
