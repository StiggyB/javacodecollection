package a07;

import java.awt.Color;
import javax.swing.JLabel;

/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 07<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing
 * 
 * <br>
 * <br>
 * <b>Description:</b> <br>
 * This class sets the ElevatorLabel settings <br>
 * depending on the chosen number to initiate on constuctor.
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 * <br>
 * 
 */
@SuppressWarnings("serial")
public class ElevatorLabel extends JLabel {

    private int x;
    private int y;
    private int boundX;
    private int boundY;

    /**
     * Sets labels x-position and its name
     * 
     * @param elevator
     *            int: elevator number
     */
    public ElevatorLabel(int elevator) {
        switch (elevator) {
            case 1:
                this.x = 0;
                break;
            case 2:
                this.x = 700;
                break;
            default:
                System.out.println("Elevator Number not supported! Only Values from 1-2!");
                break;
        }// switch
        this.y = Constants.GROUNDFLOORYPOS;
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
}// ElevatorLabel