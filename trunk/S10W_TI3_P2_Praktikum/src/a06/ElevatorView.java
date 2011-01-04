package a06;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

import javax.swing.*;

public class ElevatorView extends JPanel {

    /**
     * 
     */
    private static final long serialVersionUID = 1L;
    // private ElevatorModel eM1, eM2;
    // private JLabel eJL1, eJL2;
    private JPanel callArea, controlArea, viewArea, mainArea;
    private List<ElevatorLabel> labelList = new ArrayList<ElevatorLabel>();
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

        labelList.add(new ElevatorLabel(1));
        labelList.add(new ElevatorLabel(2));

        for (ElevatorLabel eL : labelList) {
            viewArea.add(eL);
        }// for
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
        }// if
        if (button.getText().contains("< >")) {
            button.addActionListener(kDOaL);
        }// if
    }// registerButtonActionListeners

    public void registerButtonActionListener() {
        for (int i = 0; i < 7; i++) {
            registerButtonActionListeners(jButtonArraY[i]);
        }// for
    }// registerButtonActionListener

    public void setCallButtonActionListener(ActionListener aL) {
        this.cBaL = aL;
        System.out.println("CallButtonActionListener set up complete!");
    }// setCallButtonActionListener

    public void setKeepDoorsOpenActionListener(ActionListener aL) {
        this.kDOaL = aL;
        System.out.println("KeepDoorsOpenActionListener set up complete!");
    }// setKeepDoorsOpenActionListener

    
    
    public void updateElevatorLabel(ElevatorLabel eL){
        for (ElevatorLabel eL2 : labelList) {
            if(eL.equals(eL2)){
                eL2.setBounds(eL.getBounds());
                eL2.repaint();
            }//if
                
        }//for
    }



    public JButton[] getjButtonArraY() {
        return jButtonArraY;
    }

    public void setLabelList(List<ElevatorLabel> labelList) {
        this.labelList = labelList;
    }

    public List<ElevatorLabel> getLabelList() {
        return labelList;
    }

    /**
     * @param args
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        // ShowInFrame.show("Elevator GUI", new ElevatorView());
    }

}
