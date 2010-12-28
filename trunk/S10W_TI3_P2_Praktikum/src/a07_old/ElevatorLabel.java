package a07_old;

import java.io.File;

import javax.swing.ImageIcon;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.filechooser.FileNameExtensionFilter;

public class ElevatorLabel extends JLabel implements Runnable{
    private boolean [] floorList = new boolean[4];
    private int actualFloor;
    private boolean doorOpen;
    private boolean priorityDrive;
    private int x;
    private int y;
    private int boundX;
    private int boundY;
    private ImageIcon currentIcon;
    private ImageIcon elevatorOpenIcon = new ImageIcon(getClass().getClassLoader().getResource("a07/icons/elevatorOpen.jpg"));
    private ImageIcon elevatorClosedIcon = new ImageIcon(getClass().getClassLoader().getResource("a07/icons/elevatorClosed.jpg"));
    
    
    public ElevatorLabel(int shaft){
        this.actualFloor = 0;
        this.doorOpen = true;
        this.priorityDrive = false;
        if (shaft == 1){
            this.x = 123;
            this.y = 577;
        }else if(shaft == 2){
            this.x = 599;
            this.y = 577;
        }
        this.currentIcon = elevatorOpenIcon;
        
        this.boundX = currentIcon.getIconWidth();
        this.boundY = currentIcon.getIconHeight();
        this.setBounds(this.x, this.y, this.boundX, this.boundY);
        this.setIcon(currentIcon);
        this.setSize(824, 723);
        this.setPreferredSize(new java.awt.Dimension(824, 723));
        
    }//constructor Elevator Label
    
    public void selectFloor (Floors floor){
        this.floorList[floor.toInteger()] = true;
        
    }
    
    public ImageIcon getCurrentIcon() {
        return currentIcon;
    }

    public void setCurrentIcon(ImageIcon currentIcon) {
        this.currentIcon = currentIcon;
    }

    public boolean[] getFloorList() {
        return floorList;
    }

    public void setFloorList(boolean[] floorList) {
        this.floorList = floorList;
    }

    public int getActualFloor() {
        return actualFloor;
    }

    public void setActualFloor(int actualFloor) {
        this.actualFloor = actualFloor;
    }

    public boolean isDoorOpen() {
        return doorOpen;
    }

    public void setDoorOpen(boolean doorOpen) {
        this.doorOpen = doorOpen;
    }

    public boolean isPriorityDrive() {
        return priorityDrive;
    }

    public void setPriorityDrive(boolean priorityDrive) {
        this.priorityDrive = priorityDrive;
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

    public void setBoundX(int boundX) {
        this.boundX = boundX;
    }

    public int getBoundY() {
        return boundY;
    }

    public void setBoundY(int boundY) {
        this.boundY = boundY;
    }

    public ImageIcon getElevatorOpenIcon() {
        return elevatorOpenIcon;
    }

    public ImageIcon getElevatorClosedIcon() {
        return elevatorClosedIcon;
    }

    @Override
    public void run() {
        // TODO Auto-generated method stub
        while (true){
            
        }
    }
    
    public static void main (String[] args){
        ElevatorLabel el = new ElevatorLabel(2);
        ShowInFrame.show(el);
    }

    
    
}
