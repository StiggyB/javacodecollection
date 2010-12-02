package a07;

import java.io.File;

import javax.swing.ImageIcon;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.filechooser.FileNameExtensionFilter;

public class ElevatorLabel extends JLabel{
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
        currentIcon = elevatorOpenIcon;
        
        this.boundX = currentIcon.getIconWidth();
        this.boundY = currentIcon.getIconHeight();
        this.setBounds(this.x, this.y, this.boundX, this.boundY);
        this.setIcon(currentIcon);
        this.setSize(824, 723);
        this.setPreferredSize(new java.awt.Dimension(824, 723));
        
    }
    
    public void selectFloor (Floors floor){
        this.floorList[floor.toInteger()] = true;
        
    }
    
    public void move(){
        
    }
    
    public static void main (String[] args){
        ElevatorLabel el = new ElevatorLabel(2);
        ShowInFrame.show(el);
    }
    
}
