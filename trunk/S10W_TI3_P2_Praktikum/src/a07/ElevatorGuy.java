package a07;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;

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
    private ImageIcon icon;
    // private boolean work = false;
    public boolean move = false;
    public int direction = -1;
    private ElevatorView view;

    public ElevatorView getView() {
        return view;
    }

    public ElevatorGuy(int floorConstant) {
        this.x = 375;
        this.y = floorConstant+20;
        System.out.println("ImageLoadStatus normalGuy" + normalGuy.getImageLoadStatus());
        System.out.println("ImageLoadStatus leftGuy" + leftGuy.getImageLoadStatus());
        System.out.println("ImageLoadStatus rightGuy" + rightGuy.getImageLoadStatus());
        this.icon = new ImageIcon(ElevatorGuy.class.getResource("icons/guy.jpeg"));
//        icon = normalGuy;
        this.boundX = icon.getIconWidth();
        this.boundY = icon.getIconHeight();
        this.setBounds(this.x, this.y, this.boundX, this.boundY);
        this.setName("ElevatorGuy");
//        this.setOpaque(true);
//        this.setBackground(Color.GREEN);
//        this.setSize(boundX, boundY);
        this.setIcon(icon);
//        this.setVisible(true);
        this.setText("Hallo1111");
        
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

    public void paint(Graphics g) {
        super.paint(g);
    }

    @Override
    public void run() {
        System.out.println(Thread.currentThread().getName() + " Started!");
        while (true) {
            if (move) {
                try {
                    move();
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }// catch
            } else {
//                this.icon = normalGuy;
//                this.setIcon(icon);
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
        // left
        if (direction == 0) {
            this.x -= 5;
            this.setBounds(this.x, this.y, this.boundX, this.boundY);
            this.view.updateElevatorGuy(this);
            Thread.sleep(Constants.GUYMOVESPEED);
        }// if

        // right
        if (direction == 1) {
            this.x += 5;
            this.setBounds(this.x, this.y, this.boundX, this.boundY);
            this.view.updateElevatorGuy(this);
            Thread.sleep(Constants.GUYMOVESPEED);
        }// if

    }// move

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

    // public void setWork(boolean work) {
    // this.work = work;
    // }

    public void setIcon(ImageIcon icon) {
        this.icon = icon;
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
