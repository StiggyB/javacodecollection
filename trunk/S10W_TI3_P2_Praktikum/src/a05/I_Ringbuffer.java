package a05;

public interface I_Ringbuffer<T> {

    public void enqueue(T item);

    public T dequeue();

    public T peek();

    public boolean isEmpty();

    public boolean isFull();
}
