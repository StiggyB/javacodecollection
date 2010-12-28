package a07_old;

public class ElevatorThread implements Runnable {
    Thread t;
    private ElevatorLabel el;
    
    public ElevatorThread(ElevatorLabel el) {
        // TODO Auto-generated constructor stub
        this.el = el;
    }
    
    public void start(){
        t.start();
    }
    @Override
    public void run() {
        // TODO Auto-generated method stub
        int dif = 0;
        for(int i = 0; i<el.getFloorList().length; i++){
            if(el.getFloorList()[i] != false){
                dif = i - el.getActualFloor();
            }//if
            
        }
    }

}
