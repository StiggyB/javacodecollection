package a05;

public class RingBufferv2<Image> implements I_Ringbuffer<Image> {

    private Image[] a;
    private int N = 0; 
    private int first = 0;
    private int last = 0;
    
    @Override
    public void enqueue(Image item) {
        // TODO Auto-generated method stub

    }

    @Override
    public Image dequeue() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public boolean isEmpty() {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public boolean isFull() {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public Image peek() {
        // TODO Auto-generated method stub
        return null;
    }

}
