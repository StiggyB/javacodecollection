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
    private JPanel callArea, callArea2, viewArea, mainArea;
    private List<ElevatorLabel> labelList = new ArrayList<ElevatorLabel>();
    private JButton[] jButtonArraY = new JButton[10];

    private ActionListener cBaL;

    // Constructor
    ElevatorView() {
        this.setIgnoreRepaint(true);
        this.setMinimumSize(new Dimension(1024, 768));
        this.setSize(new Dimension(1024, 768));
        this.setPreferredSize(new Dimension(1024, 768));

        createCallArea();
        createViewArea();
        createMainArea();
        this.add(mainArea);

    }// ElevatorView

    private void createMainArea() {// Border Layout
        mainArea = new JPanel(new BorderLayout());
        mainArea.add(viewArea, BorderLayout.CENTER);
        mainArea.add(callArea, BorderLayout.WEST);
        mainArea.add(callArea2, BorderLayout.EAST);

    }

    private void createViewArea() {
        viewArea = new JPanel();
        viewArea.setLayout(null);
        viewArea.setPreferredSize(new Dimension(225, 600));
        viewArea.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(""), BorderFactory.createEmptyBorder(10, 10, 10, 10)));

        labelList.add(new ElevatorLabel(1));
        labelList.add(new ElevatorLabel(2));

        for (ElevatorLabel eL : labelList) {
            viewArea.add(eL);
        }// for
    }

    private void createCallArea() { // Grid Layout vert
        callArea = new JPanel();
        callArea2 = new JPanel();
        callArea.setLayout(new GridLayout(5, 1, 5, 5));
        callArea.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(""), BorderFactory.createEmptyBorder(10, 10, 10, 10)));
        callArea2.setLayout(new GridLayout(5, 1, 5, 5));
        callArea2.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(""), BorderFactory.createEmptyBorder(10, 10, 10, 10)));

        addArrayCallButtonsToPanel(callArea);
        addArrayCallButtonsToPanel(callArea2);

    }// createCallArea

    private void addOneButtonToButtonArray(String text, JPanel pane, int index, int i) {
        JButton button = new JButton(text);
        button.setName(text + " Elevator " + i);
        button.setAlignmentX(Component.CENTER_ALIGNMENT);
        jButtonArraY[index] = button;
        if (jButtonArraY[index] != null) {
            pane.add(jButtonArraY[index]);
        } else {
            System.out.println("Init of jButtonArraY[" + index + "] with name: " + jButtonArraY[index].getText() + " failed!");
        }// else
    }// addOneButtonToButtonArray

    private void addArrayCallButtonsToPanel(JPanel pane) {
        if (pane == callArea) {
            addOneButtonToButtonArray("Fourth floor", pane, 4, 1);
            addOneButtonToButtonArray("Thrid  floor", pane, 3, 1);
            addOneButtonToButtonArray("Second floor", pane, 2, 1);
            addOneButtonToButtonArray("First  floor", pane, 1, 1);
            addOneButtonToButtonArray("Ground floor", pane, 0, 1);
        } else if (pane == callArea2) {
            addOneButtonToButtonArray("Fourth floor", pane, 9, 2);
            addOneButtonToButtonArray("Thrid  floor", pane, 8, 2);
            addOneButtonToButtonArray("Second floor", pane, 7, 2);
            addOneButtonToButtonArray("First  floor", pane, 6, 2);
            addOneButtonToButtonArray("Ground floor", pane, 5, 2);
        }// else
    }// addArrayCallButtonsToPanel

    private void registerButtonActionListeners(JButton button) {
        if (button.getText().contains("floor")) {
            button.addActionListener(cBaL);
        }// if
    }// registerButtonActionListeners

    public void registerButtonActionListener() {
        for (int i = 0; i < jButtonArraY.length; i++) {
            registerButtonActionListeners(jButtonArraY[i]);
        }// for
    }// registerButtonActionListener

    public void setCallButtonActionListener(ActionListener aL) {
        this.cBaL = aL;
    }// setCallButtonActionListener

    public void updateElevatorLabel(ElevatorLabel eL) {
        for (ElevatorLabel eL2 : labelList) {
            if (eL.equals(eL2)) {
                eL2.setBounds(eL.getBounds());
                eL2.repaint();
            }// if
        }// for
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
