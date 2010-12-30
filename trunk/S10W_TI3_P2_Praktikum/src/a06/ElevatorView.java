package a06;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Rectangle;
import java.awt.event.ActionListener;

import javax.swing.*;

public class ElevatorView extends JPanel {

    /**
     * 
     */
    private static final long serialVersionUID = 1L;
//    private ElevatorModel eM1, eM2;
    private JLabel eJL1, eJL2;
    private JPanel callArea, controlArea, viewArea, mainArea;
    private JButton[] jButtonArraY = new JButton[7];
    private ActionListener cBaL, kDOaL;

    // Constructor
    ElevatorView() {
        this.setIgnoreRepaint(true);
        this.setMinimumSize(new Dimension(1024, 768));
        this.setSize(new Dimension(1024, 768));
        this.setPreferredSize(new Dimension(1024, 768));

        createCallArea();
        createControlArea();
        createViewArea();
        createMainArea();
        this.add(mainArea);

    }// ElevatorView

    private void createMainArea() {// Border Layout
        mainArea = new JPanel(new BorderLayout());
        mainArea.add(controlArea, BorderLayout.NORTH);
        mainArea.add(viewArea, BorderLayout.CENTER);
        mainArea.add(callArea, BorderLayout.WEST);

    }

    private void createViewArea() {
        viewArea = new JPanel();
        viewArea.setLayout(null);
        viewArea.setSize(new Dimension(800, 600));
        viewArea.setPreferredSize(new Dimension(800, 600));
        viewArea.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(""), BorderFactory
                .createEmptyBorder(10, 10, 10, 10)));
        eJL1 = new JLabel();
        eJL2 = new JLabel();

        // Color settings for elevator labels
        eJL1.setOpaque(true);
        eJL2.setOpaque(true);
        eJL1.setBackground(Color.GREEN);
        eJL2.setBackground(Color.GREEN);

        // Dimension settings for elevator labels
        eJL1.setBounds(25, 475, eJL1.getWidth(), eJL1.getHeight());
        eJL2.setBounds(150, 475, eJL2.getWidth(), eJL2.getHeight());
        eJL1.setPreferredSize(new Dimension(100, 100));
        eJL2.setPreferredSize(new Dimension(100, 100));
        eJL1.setSize(new Dimension(100, 100));
        eJL2.setSize(new Dimension(100, 100));

        viewArea.add(eJL1);
        viewArea.add(eJL2);
    }

    private void createControlArea() {// Box Layout hor
        controlArea = new JPanel();
        controlArea.setLayout(new BoxLayout(controlArea, BoxLayout.X_AXIS));
        controlArea.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(""), BorderFactory
                .createEmptyBorder(10, 10, 10, 10)));

        addArrayControlButtonsToPanel(controlArea);
    }// createControlArea

    private void createCallArea() { // Grid Layout ver
        callArea = new JPanel();
        callArea.setLayout(new GridLayout(5, 1, 5, 5));
        callArea.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(""), BorderFactory
                .createEmptyBorder(10, 10, 10, 10)));

        addArrayCallButtonsToPanel(callArea);
    }// createCallArea

    private void addOneButtonToButtonArray(String text, JPanel pane, int index, int i) {
        JButton button = new JButton(text);
        button.setName(text + " Elevator " + i);
        button.setAlignmentX(Component.CENTER_ALIGNMENT);
        jButtonArraY[index] = button;
        if (jButtonArraY[index] != null) {
            System.out.println("Init of jButtonArraY[" + index + "] with name: " + jButtonArraY[index].getText()
                    + " successfull!");
            pane.add(jButtonArraY[index]);
        }else {
            System.out.println("Init of jButtonArraY[" + index + "] with name: " + jButtonArraY[index].getText()
                    + " failed!");
        }// else
    }// addOneButtonToButtonArray

    private void addArrayCallButtonsToPanel(JPanel pane) {
        addOneButtonToButtonArray("Fourth floor", pane, 4, 1);
        addOneButtonToButtonArray("Thrid  floor", pane, 3, 1);
        addOneButtonToButtonArray("Second floor", pane, 2, 1);
        addOneButtonToButtonArray("First  floor", pane, 1, 1);
        addOneButtonToButtonArray("Ground floor", pane, 0, 1);
    }// addArrayCallButtonsToPanel

    private void addArrayControlButtonsToPanel(JPanel pane) {
        addOneButtonToButtonArray("< >", pane, 5, 1);
        addOneButtonToButtonArray("< >", pane, 6, 2);
    }// addArrayCallButtonsToPanel

    private void registerButtonActionListeners(JButton button) {
        System.out.println(button.getName() + button.getText());
        if (button.getText().contains("floor")) {
            button.addActionListener(cBaL);
            System.out.println("ActionListener cBaL added for button: " + button.getText());
        }//if
        if (button.getText().contains("< >")) {
            button.addActionListener(kDOaL);
        }//if
    }// registerButtonActionListeners

    public void registerButtonActionListener() {
        for (int i = 0; i < 7; i++) {
            registerButtonActionListeners(jButtonArraY[i]);
        }//for
    }// registerButtonActionListener

    public void setCallButtonActionListener(ActionListener aL) {
        this.cBaL = aL;
        System.out.println("CallButtonActionListener set up complete!");
    }// setCallButtonActionListener

    public void setKeepDoorsOpenActionListener(ActionListener aL) {
        this.kDOaL = aL;
        System.out.println("KeepDoorsOpenActionListener set up complete!");
    }// setKeepDoorsOpenActionListener

    public void increaseElevatorFloor(int elevator) throws InterruptedException{
        if(elevator == 1){
            Rectangle b = eJL1.getBounds();
//            System.out.println("Bound Y vorher: " + b.y);
            b.y -= 125;
//            System.out.println("Bound Y nachher: " + b.y);
            Thread.sleep(2000);
            eJL1.setBounds(b);
            System.out.println(eJL1.getBounds());
        }
    }//increaseElevatorFloor
    
    public void decreaseElevatorFloor(){
        
    }//decreaseElevatorFloor
    /**
     * @param args
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        ShowInFrame.show("Elevator GUI", new ElevatorView());
    }

}
