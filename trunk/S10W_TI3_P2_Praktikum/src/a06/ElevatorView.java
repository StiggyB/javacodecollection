package a06;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionListener;

import javax.swing.*;

public class ElevatorView extends JPanel {

    /**
     * 
     */
    private static final long serialVersionUID = 1L;
    private ElevatorModel eM1, eM2;
    private JLabel eJL1, eJL2;
    private JPanel callArea, controlArea, viewArea, mainArea;
    private JButton floor0, floor1, floor2, floor3, floor4;
    private JButton kDO1, kDO2;
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
        eM1 = new ElevatorModel("Elevator 1");
        eM2 = new ElevatorModel("Elevator 2");


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
        
        //Color settings for elevator labels
        eJL1.setOpaque(true);
        eJL2.setOpaque(true);
        eJL1.setBackground(Color.GREEN);
        eJL2.setBackground(Color.GREEN);     
        
        //Dimension settings for elevator labels
        eJL1.setBounds(25, 25, eJL1.getWidth(), eJL1.getHeight());
        eJL2.setBounds(150, 25, eJL2.getWidth(), eJL2.getHeight());
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
        addControlButtonsToPanel(controlArea);

    }

    private void addControlButtonsToPanel(JPanel pane) {
        addOneButton("< >", pane, kDO1, 1);
        addOneButton("< >", pane, kDO2, 2);
    }

    private void createCallArea() { // Grid Layout ver
        callArea = new JPanel();
        callArea.setLayout(new GridLayout(5, 1, 5, 5));
        callArea.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(""), BorderFactory
                .createEmptyBorder(10, 10, 10, 10)));
        addCallButtonsToPanel(callArea);
    }// createCallArea

    private void addCallButtonsToPanel(JPanel pane) {
        addOneButton("Ground floor", pane, this.floor0, 1);
        addOneButton("First  floor", pane, this.floor1, 1);
        addOneButton("Second floor", pane, this.floor2, 1);
        addOneButton("Thrid  floor", pane, this.floor3, 1);
        addOneButton("Fourth floor", pane, this.floor4, 1);
    }// addCallButtonsToPanel

    // Method to add one button to a specified Panel
    private void addOneButton(String text, JPanel pane, JButton button, int i) {
        button = new JButton(text);
        button.setName(text + " Elevator " + i);
        button.setAlignmentX(Component.CENTER_ALIGNMENT);
        pane.add(button);
        System.out.println("Button " + button.getName() + " added with " + text);
    }// addOneButton
    
    private void registerButtonActionListeners(JButton button){
        System.out.println(button.getName() + button.getText());
        if(button.getText().contains("floor")){
            button.addActionListener(cBaL);
            System.out.println("ActionListener added for button: " + button.getText());
        }
        if(button.getText().contains("< >")){
            button.addActionListener(kDOaL);
        }
    }//registerButtonActionListeners
   
    public void setUpButtons(){
        registerButtonActionListeners(this.floor0);
        registerButtonActionListeners(this.floor1);
        registerButtonActionListeners(this.floor2);
        registerButtonActionListeners(this.floor3);
        registerButtonActionListeners(this.floor4);
        registerButtonActionListeners(this.kDO1);
        registerButtonActionListeners(this.kDO2);
    }
    
    public void setCallButtonActionListener(ActionListener aL){
        this.cBaL = aL;
        
        
    }//setCallButtonActionListener
    
    public void setKeepDoorsOpenActionListener(ActionListener aL){
        this.kDOaL = aL;
        
    }
    
    public ElevatorModel geteM1() {
        return eM1;
    }

    public void seteM1(ElevatorModel eM1) {
        this.eM1 = eM1;
    }

    public ElevatorModel geteM2() {
        return eM2;
    }

    public void seteM2(ElevatorModel eM2) {
        this.eM2 = eM2;
    }
    
    
    /**
     * @param args
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        ShowInFrame.show("Elevator GUI", new ElevatorView());
    }

}
