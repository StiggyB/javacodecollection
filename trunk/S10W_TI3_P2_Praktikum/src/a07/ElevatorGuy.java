package a07;

import java.awt.Color;
import javax.swing.ImageIcon;
import javax.swing.JLabel;

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

    // TODO Elevator & Guy bewegen synchronisiert!

    public ElevatorView getView() {
        return view;
    }

    public ElevatorGuy(int floorConstant, String name) {
        this.x = 375;
        this.y = floorConstant + 20;
        this.boundX = normalGuy.getIconWidth();
        this.boundY = normalGuy.getIconHeight();
        this.setBounds(this.x, this.y, this.boundX, this.boundY);
        this.setName("Elevator "+name);
        this.setSize(boundX, boundY);
        this.setIcon(normalGuy);
    }

    protected ImageIcon createImageIcon(String path, String description) {
        java.net.URL imgURL = getClass().getResource(path);
        if (imgURL != null) {
            return new ImageIcon(imgURL, description);
        } else {
            System.err.println("Couldn't find file: " + path);
            return null;
        }
    }

    @Override
    public void run() {
//        System.out.println(Thread.currentThread().getName() + " Started!");
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
                // this.icon = normalGuy;
                // this.setIcon(icon);
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
     * Direction: 0 = left, 1 = right
     * 
     * @throws InterruptedException
     */
    public void move() throws InterruptedException {
        if (this.x >= 51) {

            // left

            if (eL1.getY() == (this.y - (eL1.getBoundY() - this.boundY)) && eL1.getBackground().equals(Color.GREEN)
                    && this.x <= Constants.ELEVATORRIGHTENTRY - this.boundX) {// Elevator is on same floor as Guy & is
                                                                              // open
                moveLeft();
            } else if ((this.x-Constants.GUYSTEPS) >= Constants.ELEVATORLEFTENTRY && this.x <= Constants.ELEVATORRIGHTENTRY - this.boundX) {// Guy
                                                                                                                       // is
                                                                                                                       // between
                                                                                                                       // elevators
                moveLeft();
            } else if (this.x >= Constants.ELEVATORRIGHTENTRY-this.boundX && eL2.getY() == (this.y - (eL2.getBoundY() - this.boundY)) && eL2.getBackground().equals(Color.GREEN)) {// Guy
                                                                                                                                                                       // is
                                                                                                                                                                       // in
                                                                                                                                                                       // right
                                                                                                                                                                       // elevator
                moveLeft();
            }// if
        }// if
        if (this.x <= 699) {

            // right
            // about to enter right elevator
            if (eL2.getY() == (this.y - (eL2.getBoundY() - this.boundY)) && eL2.getBackground().equals(Color.GREEN) && this.x >= Constants.ELEVATORLEFTENTRY) {// Elevator
                                                                                                                                                               // is
                                                                                                                                                               // on
                                                                                                                                                               // same
                                                                                                                                                               // floor
                                                                                                                                                               // as
                                                                                                                                                               // Guy
                                                                                                                                                               // &
                                                                                                                                                               // is
                                                                                                                                                               // open
                moveRight();
            } else if ((this.x+Constants.GUYSTEPS) <= Constants.ELEVATORRIGHTENTRY - this.boundX && this.x >= Constants.ELEVATORLEFTENTRY) {// Guy
                                                                                                                       // is
                                                                                                                       // between
                                                                                                                       // elevators
                moveRight();
            } else if (this.x <= Constants.ELEVATORLEFTENTRY && eL1.getY() == (this.y - (eL1.getBoundY() - this.boundY)) && eL1.getBackground().equals(Color.GREEN)) {// Guy
                                                                                                                                                                      // is
                                                                                                                                                                      // in
                                                                                                                                                                      // left
                                                                                                                                                                      // elevator
                moveRight();
            }// if
        }// if
        if (this.x <= Constants.ELEVATORLEFTENTRY - this.boundX || this.x >= Constants.ELEVATORRIGHTENTRY) {
            this.setVisible(false);
        }// if
    }// move

    /**
     * @throws InterruptedException
     */
    private void moveLeft() throws InterruptedException {
        this.setVisible(true);
        if (direction == 0) {// Enter left elevator
            this.setIcon(leftGuy); // repaint?
            this.x -= Constants.GUYSTEPS;
            this.setBounds(this.x, this.y, this.boundX, this.boundY);
            this.view.updateElevatorGuy(this);
            Thread.sleep(Constants.GUYSLEEP);
            this.setIcon(normalGuy); // repaint?
        }// if
    }

    /**
     * @throws InterruptedException
     */
    private void moveRight() throws InterruptedException {
        this.setVisible(true);
        if (direction == 1) {// Enter right elevator
            this.setIcon(rightGuy); // repaint?
            this.x += Constants.GUYSTEPS;
            this.setBounds(this.x, this.y, this.boundX, this.boundY);
            this.view.updateElevatorGuy(this);
            Thread.sleep(Constants.GUYSLEEP);
            this.setIcon(normalGuy); // repaint?
        }// if
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
