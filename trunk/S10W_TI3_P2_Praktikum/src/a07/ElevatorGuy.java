package a07;

import java.net.URL;

import javax.swing.ImageIcon;
import javax.swing.JLabel;

@SuppressWarnings("serial")
public class ElevatorGuy extends JLabel implements Runnable{
    private int x;
    private int y;
    private int boundX;
    private int boundY;
    private ImageIcon normalGuy = new ImageIcon(ClassLoader.getSystemResource("a07/icons/guy.jpeg"));
    private ImageIcon leftGuy = new ImageIcon(ClassLoader.getSystemResource("a07/icons/guy_mL.jpeg"));
    private ImageIcon rightGuy = new ImageIcon(ClassLoader.getSystemResource("a07/icons/guy_mR.jpeg"));
    private ImageIcon icon;
    private boolean work = false;
    public boolean move = false;
    
    public ElevatorGuy(int floorConstant) {
        
        this.x = 375;
        this.y = floorConstant;
        this.boundX = 50;
        this.boundY = 80;
        this.setBounds(this.x, this.y, this.boundX, this.boundY);
        this.setName("ElevatorGuy");
        this.setSize(50, 80);
        this.icon = normalGuy;
        this.setIcon(icon);
    }
    
    @Override
    public void run() {
        System.out.println(Thread.currentThread().getName() + " Started!");
        while (true){
            if (work) {
                move();
            } else {
                this.icon = normalGuy;
                this.setIcon(icon);
                try {
                    Thread.sleep(200);
                    System.out.println("Sleeping....");
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }// catch
//                // check if there's something to do
//                if (!targets.isEmpty()) {
//                    work = true;
//                }// if
            }// else
        }
    }
    
    public void move(){
        
    }
    
    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }
    
    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getBoundX() {
        return boundX;
    }

    public int getBoundY() {
        return boundY;
    }

    public void setWork(boolean work) {
        this.work = work;
    }

}
