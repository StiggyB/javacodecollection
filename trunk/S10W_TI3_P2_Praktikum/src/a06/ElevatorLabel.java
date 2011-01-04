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
  

    public ElevatorLabel(int elevator) {
        switch (elevator) {
            case 1:
                this.x = 0;
                this.setName("Elevator 1");
                break;
            case 2:
                this.x = 125;
                this.setName("Elevator 2");
                break;
            default:
                break;
        }// switch
        this.y = Constants.groundFloor;
        this.boundX = 100;
        this.boundY = 100;
        this.setBounds(this.x, this.y, this.boundX, this.boundY);
        this.setOpaque(true);
        this.setBackground(Color.GREEN);
        this.setName("Elevator " + elevator);
        this.setSize(100, 100);

    }// ElevatorLabel

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
