package a07;

import java.awt.Color;
import javax.swing.ImageIcon;
import javax.swing.JLabel;

/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 07<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen: API
 * 
 * <br>
 * <br>
 * <b>Description:</b> <br>
 * This class sets the ElevatorGuy settings <br>
 * and loads the Images to display in which direction the guy is moving.
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 * <br>
 * 
 */
@SuppressWarnings("serial")
public class ElevatorGuy extends JLabel implements Runnable {
    private int x;
    private int y;
    private int boundX;
    private int boundY;
    private ImageIcon normalGuy = new ImageIcon((ElevatorGuy.class.getResource("icons/guy.jpeg")));
    private ImageIcon leftGuy = new ImageIcon((ElevatorGuy.class.getResource("icons/guy_mL.jpeg")));
    private ImageIcon rightGuy = new ImageIcon((ElevatorGuy.class.getResource("icons/guy_mR.jpeg")));
    public boolean move = false;
    public boolean elevatorMove = true;
    public int direction = -1;
    private ElevatorView view;
    private ElevatorLabel eL1;
    private ElevatorLabel eL2;

    /**
     * Sets guys start floor where he appears and his name.<br>
     * 
     * @param floorConstant
     *            : the floor level
     * @param name
     *            : his name
     */
    public ElevatorGuy(int floorConstant, String name) {
        this.x = 375;
        this.y = floorConstant + 20;
        this.boundX = normalGuy.getIconWidth();
        this.boundY = normalGuy.getIconHeight();
        this.setBounds(this.x, this.y, this.boundX, this.boundY);
        this.setName("Elevator " + name);
        this.setSize(boundX, boundY);
        this.setIcon(normalGuy);
    }

    // protected ImageIcon createImageIcon(String path, String description) {
    // java.net.URL imgURL = getClass().getResource(path);
    // if (imgURL != null) {
    // return new ImageIcon(imgURL, description);
    // } else {
    // System.err.println("Couldn't find file: " + path);
    // return null;
    // }
    // }

    /**
     * Runnables run() searches the 2 elevator labels and sets them to the private variables. while (true) {<br>
     * if the guy is being moved, it calls the move(). Otherwise the thread sleeps for 200ms.<br>
     * }
     */
    @Override
    public void run() {
        for (ElevatorLabel eL : view.getLabelList()) {
            if (eL.getName().equals("Elevator 1")) {
                this.eL1 = eL;
            }// if
            if (eL.getName().equals("Elevator 2")) {
                this.eL2 = eL;
            }// if
        }// for
        while (true) {
            if (move) {
                try {
                    move();
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }// catch
            } else {
                try {
                    Thread.sleep(200);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }// catch
            }// else
        }// while
    }// run

    /**
     * Checks if the guy may move left or right and calls the moveLeft() or moveRight().<br>
     * <br>
     * Direction: 0 = left, 1 = right
     * 
     * @throws InterruptedException
     */
    public void move() throws InterruptedException {
        if (this.x >= 51) {

            // left
            if (eL1.getY() == (this.y - (eL1.getBoundY() - this.boundY)) && eL1.getBackground().equals(Color.GREEN)
                    && this.x <= Constants.ELEVATORRIGHTENTRY - this.boundX) {
                // Elevator is on same floor as Guy & is open
                moveLeft();
            } else if ((this.x - Constants.GUYSTEPS) >= Constants.ELEVATORLEFTENTRY && this.x <= Constants.ELEVATORRIGHTENTRY - this.boundX) {
                // Guy is between elevators
                moveLeft();
            } else if (this.x >= Constants.ELEVATORRIGHTENTRY - this.boundX && eL2.getY() == (this.y - (eL2.getBoundY() - this.boundY))
                    && eL2.getBackground().equals(Color.GREEN)) {
                // Guy is in right elevator
                moveLeft();
            }// if
        }// if
        if (this.x <= 699) {

            // right
            if (eL2.getY() == (this.y - (eL2.getBoundY() - this.boundY)) && eL2.getBackground().equals(Color.GREEN) && this.x >= Constants.ELEVATORLEFTENTRY) {
                // Elevator is on same floor as Guy & is open
                moveRight();
            } else if ((this.x + Constants.GUYSTEPS) <= Constants.ELEVATORRIGHTENTRY - this.boundX && this.x >= Constants.ELEVATORLEFTENTRY) {
                // Guy is between elevators
                moveRight();
            } else if (this.x <= Constants.ELEVATORLEFTENTRY && eL1.getY() == (this.y - (eL1.getBoundY() - this.boundY)) && eL1.getBackground().equals(Color.GREEN)) {
                // Guy is in left elevator
                moveRight();
            }// if
        }// if
        if (this.x <= Constants.ELEVATORLEFTENTRY - this.boundX || this.x >= Constants.ELEVATORRIGHTENTRY) {
            this.setVisible(false);
        }// if
    }// move

    /**
     * Sets the ElevatorGuyLabel visible, sets the guys icon to left and moves him one GUYSTEP left.<br>
     * Updates the bounds and calls the views updateElevatorGuy(), sleeps for GUYSLEEP ms and sets the guys icon to
     * normal.<br>
     * 
     * @throws InterruptedException
     */
    private void moveLeft() throws InterruptedException {
        this.setVisible(true);
        if (direction == 0) {
            this.setIcon(leftGuy);
            this.x -= Constants.GUYSTEPS;
            this.setBounds(this.x, this.y, this.boundX, this.boundY);
            this.view.updateElevatorGuy(this);
            Thread.sleep(Constants.GUYSLEEP);
            this.setIcon(normalGuy);
        }// if
    }// moveLeft

    /**
     * Sets the ElevatorGuyLabel visible, sets the guys icon to right and moves him one GUYSTEP right.<br>
     * Updates the bounds and calls the views updateElevatorGuy(), sleeps for GUYSLEEP ms and sets the guys icon to
     * normal.<br>
     * 
     * @throws InterruptedException
     */
    private void moveRight() throws InterruptedException {
        this.setVisible(true);
        if (direction == 1) {
            this.setIcon(rightGuy);
            this.x += Constants.GUYSTEPS;
            this.setBounds(this.x, this.y, this.boundX, this.boundY);
            this.view.updateElevatorGuy(this);
            Thread.sleep(Constants.GUYSLEEP);
            this.setIcon(normalGuy);
        }// if
    }// moveRight

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

    public ImageIcon getNormalGuy() {
        return normalGuy;
    }

    public ImageIcon getLeftGuy() {
        return leftGuy;
    }

    public ImageIcon getRightGuy() {
        return rightGuy;
    }

    public void setView(ElevatorView view) {
        this.view = view;
    }

}
