package a06;

import java.awt.Color;
import javax.swing.JLabel;

public class ElevatorLabel extends JLabel {
    /**
     * 
     */
    private static final long serialVersionUID = 1L;
    private int x;
    private int y;
    private int boundX;
    private int boundY;
    private int groundFloor = 475;
    private int firstFloor = 360;
    private int secondFloor = 247;
    private int thirdFloor = 133;
    private int fourthFloor = 18;
    private boolean work = false;

    

    public ElevatorLabel(int elevator) {
        switch (elevator) {
            case 1:
                this.x = 25;
                this.setName("Elevator 1");
                break;
            case 2:
                this.x = 150;
                this.setName("Elevator 2");
                break;
            default:
                break;
        }// switch
        this.y = groundFloor;
        this.boundX = 100;
        this.boundY = 100;
        this.setBounds(this.x, this.y, this.boundX, this.boundY);
        this.setOpaque(true);
        this.setBackground(Color.GREEN);
        this.setName("Elevator " + elevator);
        this.setSize(100, 100);

    }// ElevatorLabel
    
//    public void increaseElevatorFloor(int elevator) throws InterruptedException {
//
//        for (ElevatorLabel eL : labelList) {
//
//            if (elevator == 1 && eL.getName() == "Elevator 1") {
//                Rectangle b = eL.getBounds();
//                for (int i = 0; i < 6; i++) {
//                    b.y -= 25;
//                    Thread.sleep(400);
//                    eL.setBounds(b);
//                }
//                // b.y -= 125;
//                // System.out.println("Bound Y nachher: " + b.y);
//                // System.out.println(eL.getBounds());
//            }
//        }
//    }// increaseElevatorFloor
    
    public void decreaseElevatorFloor() {

    }// decreaseElevatorFloor

    public void move(int destination) throws InterruptedException {
//        System.out.println("Drin!");
//        int goTo = 0;
//        switch (destination) {
//            case 0:
//                goTo = this.groundFloor;
//                break;
//            case 1:
//                goTo = this.firstFloor;
//                break;
//            case 2:
//                goTo = this.secondFloor;
//                break;
//            case 3:
//                goTo = this.thirdFloor;
//                break;
//            case 4:
//                goTo = this.fourthFloor;
//                break;
//        }//switch
////        System.out.println("goTo: "+goTo);
//        if(this.y < goTo){
////            System.out.println("In y < goTo");
//            this.y += 1;
//            this.setBounds(this.x, this.y, this.boundX, this.boundY);
//            
//        }else if(this.y > goTo){
////            System.out.println("In y > goTo");
//            this.y -= 1;
//            this.setBounds(this.x, this.y, this.boundX, this.boundY);
////            this.repaint();
////            Thread.sleep(10);
//        }else {
//            this.work = false;
//        }
    }
    public boolean isWork() {
        return work;
    }

    public void setWork(boolean work) {
        this.work = work;
    }

    public int getGroundFloor() {
        return groundFloor;
    }

    public int getFirstFloor() {
        return firstFloor;
    }

    public int getSecondFloor() {
        return secondFloor;
    }

    public int getThirdFloor() {
        return thirdFloor;
    }

    public int getFourthFloor() {
        return fourthFloor;
    }

    public int getX() {
        return x;
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
}
