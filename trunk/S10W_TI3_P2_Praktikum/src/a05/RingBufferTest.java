package a05;

import static org.junit.Assert.*;

import org.junit.Test;

public class RingBufferTest {

    @Test
    public void testRingBuffer() {
        RingBuffer<Integer> ring = new RingBuffer<Integer>(5);
        assertEquals("Ring Buffer initialisation failed", "Ring Buffer initialized", ring.toString());
    }

    @Test
    public void testIsEmpty() {
        RingBuffer<Integer> ring = new RingBuffer<Integer>(5);
        assertTrue(ring.isEmpty());
        ring.enqueue(1);
        ring.enqueue(2);
        ring.dequeue();
        ring.dequeue();
        assertTrue(ring.isEmpty());
    }

    @Test
    public void testSize() {
        RingBuffer<Integer> ring = new RingBuffer<Integer>(5);
        ring.enqueue(1);
        assertEquals(1, ring.size());
    }

    @Test
    public void testIsFull() {
        RingBuffer<Integer> ring = new RingBuffer<Integer>(5);
        ring.enqueue(1);
        ring.enqueue(2);
        ring.enqueue(3);
        ring.enqueue(4);
        ring.enqueue(5);
        assertTrue(ring.isFull());
    }

    @Test
    public void testPeek() {
        RingBuffer<Integer> ring = new RingBuffer<Integer>(5);
        ring.enqueue(1);
        ring.enqueue(2);
        ring.enqueue(3);
        ring.enqueue(4);
        ring.enqueue(5);
        assertSame(1, ring.peek());
    }

    @Test
    public void testMainClasses() {
        class Test {
            String x = "default";

            Test(String x) {
                this.x = x;
            }

            public String toString() {
                return this.x;
            }
        }
        RingBuffer<Test> ring2 = new RingBuffer<Test>(5);
        try {
            ring2.enqueue(new Test("Test1"));
            ring2.enqueue(new Test("Test2"));
            ring2.enqueue(new Test("Test3"));
            ring2.enqueue(new Test("Test4"));
            ring2.enqueue(new Test("Test5"));
            assertTrue(ring2.isFull());
        }catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        System.out.println();

        while (!ring2.isEmpty()) {
            System.out.println(ring2.dequeue());
        }
    }
    //Leere Queue
    //
    @Test
    public void testEmptyQueue() throws RuntimeException {
        RingBuffer<Integer> ring = new RingBuffer<Integer>(0);
        assertTrue(ring.isEmpty());
        assertTrue(ring.isFull());
        try {
            ring.enqueue(0);
            fail("Expected RuntimeException");
            
        }catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        try {
            System.out.println(ring.dequeue());
            fail("Expected RuntimeException");
        }catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
    }
    @Test
    public void testMainIntegers() {
        RingBuffer<Integer> ring = new RingBuffer<Integer>(5);
        try {
            ring.enqueue(1);
            ring.enqueue(2);
            ring.enqueue(3);
            ring.enqueue(4);
            ring.enqueue(5);
            ring.enqueue(6);
        }catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        while (!ring.isEmpty()) {
            System.out.println(ring.dequeue());
        }
    }

    @Test
    public void testMainStrings() {
        RingBuffer<String> ring = new RingBuffer<String>(20);
        ring.enqueue("This");
        ring.enqueue("is");
        ring.enqueue("a");
        ring.enqueue("test.");

        while (!ring.isEmpty()) {
            System.out.println(ring.dequeue());
        }
    }
}
