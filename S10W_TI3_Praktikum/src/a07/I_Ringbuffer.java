package a07;

/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 05<br>
 * 
 * Version: V0<br>
 * Aenderungen:
 * 
 * Quellen: API
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

public interface I_Ringbuffer<T> {

    public void enqueue(T item) throws RuntimeException;

    public T dequeue() throws RuntimeException;

    public T peek() throws RuntimeException;

    public boolean isEmpty();

    public boolean isFull();
}
