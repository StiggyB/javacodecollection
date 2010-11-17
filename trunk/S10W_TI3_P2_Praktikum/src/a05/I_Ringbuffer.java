package a05;

public interface I_Ringbuffer<T> {

    public void enqueue(T item) throws RuntimeException;

    public T dequeue() throws RuntimeException;

    public T peek() throws RuntimeException;

    public boolean isEmpty();

    public boolean isFull();
}
