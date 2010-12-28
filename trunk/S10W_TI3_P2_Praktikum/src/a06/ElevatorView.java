package a06;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;

import javax.swing.*;

public class ElevatorView extends JPanel{

    private ElevatorModel eM1, eM2;
    private JLabel eJL1, eJL2;
    private JPanel callArea, controlArea, viewArea, mainArea;

    // private JButton callGF, callF1, callF2, callF3, callF4;

    // Constructor
    ElevatorView() {
        createCallArea();
        createControlArea();
        createViewArea();
        createMainArea();

    }// ElevatorView

    private void createMainArea() {// Border Layout
        mainArea = new JPanel(new BorderLayout());
        mainArea.setPreferredSize(new Dimension(1024, 768));
        mainArea.add(controlArea, BorderLayout.NORTH);
        mainArea.add(viewArea, BorderLayout.CENTER);
        mainArea.add(callArea, BorderLayout.WEST);

    }

    private void createViewArea() {
        viewArea = new JPanel();
        viewArea.setPreferredSize(new Dimension(800, 600));
        eJL1 = new JLabel("Elevator 2");
        eJL1.setBackground(Color.GREEN);
        eJL2 = new JLabel("Elevator 1");
        eJL2.setBackground(Color.GREEN);
        eJL1.setPreferredSize(new Dimension(100, 100));
        eJL2.setPreferredSize(new Dimension(100, 100));
        eJL1.setBounds(200, 25, eJL1.getWidth(), eJL1.getHeight());
        eJL2.setBounds(400, 25, eJL2.getWidth(), eJL2.getHeight());
        
        

    }

    private void createControlArea() {// Box Layout hor
        controlArea = new JPanel();
        controlArea.setLayout(new BoxLayout((Container) controlArea, BoxLayout.X_AXIS));
        controlArea.setBorder((BorderFactory.createCompoundBorder(
                BorderFactory.createEmptyBorder(), BorderFactory
                .createEmptyBorder(10, 10, 10, 10))));
        addControlButtonsToPanel(controlArea);

    }

    private void addControlButtonsToPanel(JPanel pane) {
        addOneButton("< >", pane);
        addOneButton("< >", pane);
    }

    private void createCallArea() { // Box Layout ver
        callArea = new JPanel();
        callArea.setLayout(new BoxLayout(callArea, BoxLayout.Y_AXIS));
        callArea.setBorder((BorderFactory.createCompoundBorder(
                BorderFactory.createEmptyBorder(), BorderFactory
                .createEmptyBorder(10, 10, 10, 10))));
        addCallButtonsToPanel(callArea);
    }// createCallArea

    private void addCallButtonsToPanel(JPanel pane) {
        addOneButton("Ground floor", pane);
        addOneButton("First  floor", pane);
        addOneButton("Second floor", pane);
        addOneButton("Thrid  floor", pane);
    }// addCallButtonsToPanel

    // Method to add one button to a specified Panel
    private void addOneButton(String text, JPanel pane) {
        JButton button = new JButton(text);
        button.setAlignmentX(Component.CENTER_ALIGNMENT);
        pane.add(button);
    }// addOneButton

    /**
     * @param args
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        ShowInFrame.show("Elevator GUI", new ElevatorView());
    }

}
