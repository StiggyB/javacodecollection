package tester.threads;

public class ThreadTest extends Thread{
    
    int i = 0;
    
    public void run(){
        while (true) {
            //Thread ausführung
            System.out.println(i++);
            try {
                Thread.sleep(1000);
            }catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }
    
    public static void main(String[] Arg){
        Thread t = new ThreadTest();
        t.start();
    }
    
}
