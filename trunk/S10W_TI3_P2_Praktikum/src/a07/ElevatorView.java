package a07;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

import javax.swing.*;

/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 06<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing
 * 
 * <br><br><b>Description:</b> <br>This class represents the GUI or the view in MVC-Pattern.<br>
 * Including the JPanels for the different Areas, the LabelList for the ElevatorLabels,
 * the JButton[] for the CallButtons and the ActionListener for the Buttons 
 *  
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br><br>
 * 
 */

public class ElevatorView extends JPanel {

    private static final long serialVersionUID = 1L;
    private JPanel callArea, callArea2, controlArea, viewArea, mainArea;
    private List<ElevatorLabel> labelList = new ArrayList<ElevatorLabel>();
    private JButton[] jButtonArray = new JButton[((Constants.FLOORNO*2)+Constants.ELEVATORNO)];
    private JCheckBox[] jCheckBoxArray = new JCheckBox[Constants.ELEVATORNO];

    private ActionListener cBaL;

    /**
     * Constructor to create the other JPanel Areas
     */
    ElevatorView() {
        createCallArea();
        createControlArea();
        createViewArea();
        createMainArea();
        this.add(mainArea);
    }// ElevatorView

    /**
     * Creates the mainArea and adds sub panels to its BorderLayout.<br>
     * viewArea = CENTER<br>
     * callArea = WEST<br>
     * callArea2 = EAST<br>
     */
    private void createMainArea() {// Border Layout
        mainArea = new JPanel(new BorderLayout());
        mainArea.add(viewArea, BorderLayout.CENTER);
        mainArea.add(callArea, BorderLayout.WEST);
        mainArea.add(callArea2, BorderLayout.EAST);
    }//createMainArea

    /**
     * Creates the viewArea panel with nullLayout and sets its size and border.<br>
     * Also creates and adds the ElevatorLabels to the panel.
     */
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
    }//createViewArea
    
    private void createControlArea() {
        controlArea = new JPanel();
        controlArea.setLayout(new BoxLayout(controlArea, BoxLayout.X_AXIS));
        addOneCheckBoxToCheckBoxArray("",panel,index,elevator);
        
    }

    /**
     * Creates the callAreas panels with GridLayouts (vert) and borders.<br>
     * Also creates and adds the callButtons to the panel
     */
    private void createCallArea() { // Grid Layout vert
        callArea = new JPanel();
        callArea2 = new JPanel();
        callArea.setLayout(new GridLayout(5, 1, 5, 5));
        callArea.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(""), BorderFactory.createEmptyBorder(10, 10, 10, 10)));
        callArea2.setLayout(new GridLayout(5, 1, 5, 5));
        callArea2.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(""), BorderFactory.createEmptyBorder(10, 10, 10, 10)));

        addCallButtonsToPanel(callArea);
        addCallButtonsToPanel(callArea2);
    }// createCallArea

    /**
     * Adds one button to the JButtonArray and adds them to the specified panel.
     * 
     * @param text String: JButtons text
     * @param pane JPanel: Panel to add button to
     * @param index int: JButtonArray index number
     * @param i int: Elevator number
     */
    private void addOneButtonToButtonArray(String text, JPanel pane, int index, int i) {
        JButton button = new JButton(text);
        button.setName(text + " Elevator " + i);
        button.setAlignmentX(Component.CENTER_ALIGNMENT);
        jButtonArray[index] = button;
        if (jButtonArray[index] != null) {
            pane.add(jButtonArray[index]);
        } else {
            System.out.println("Init of jButtonArraY[" + index + "] with name: " + jButtonArray[index].getText() + " failed!");
        }// else
    }// addOneButtonToButtonArray
    
    private void addOneCheckBoxToCheckBoxArray(String text, JPanel pane, int index, int i) {
        JCheckBox checkBox = new JCheckBox(text);
        checkBox.setName(text + " Elevator " + i);
        checkBox.setAlignmentX(Component.CENTER_ALIGNMENT);
        jCheckBoxArray[index] = checkBox;
        if (jCheckBoxArray[index] != null) {
            pane.add(jCheckBoxArray[index]);
        } else {
            System.out.println("Init of jCheckBoxArray[" + index + "] with name: " + jCheckBoxArray[index].getText() + " failed!");
        }// else
    }// addOneButtonToButtonArray

    /**
     * Calls the addOneButtonToButtonArray for the specified buttons  
     * 
     * @param pane Panel: Panel to add callButtons to
     * @see ElevatorView#addOneButtonToButtonArray addOneButtonToButtonArray
     */
    private void addCallButtonsToPanel(JPanel pane) {
        if (pane == callArea) {
            addOneButtonToButtonArray("Fourth floor", pane, 4, 1);
            addOneButtonToButtonArray("Third  floor", pane, 3, 1);
            addOneButtonToButtonArray("Second floor", pane, 2, 1);
            addOneButtonToButtonArray("First  floor", pane, 1, 1);
            addOneButtonToButtonArray("Ground floor", pane, 0, 1);
        } else if (pane == callArea2) {
            addOneButtonToButtonArray("Fourth floor", pane, 9, 2);
            addOneButtonToButtonArray("Third  floor", pane, 8, 2);
            addOneButtonToButtonArray("Second floor", pane, 7, 2);
            addOneButtonToButtonArray("First  floor", pane, 6, 2);
            addOneButtonToButtonArray("Ground floor", pane, 5, 2);
        }// else
    }// addArrayCallButtonsToPanel

    /**
     * Adds the actionListener to the button
     * 
     * @param button JButton: Button to addActionListener
     */
    private void registerButtonActionListener(JButton button) {
        if (button.getText().contains("floor")) {
            button.addActionListener(cBaL);
        }// if
    }// registerButtonActionListeners

    /**
     * Calls the registerButtonActionListener(JButton) for each button from jButtonArray[]
     * @see ElevatorView#registerButtonActionListener(JButton) registerButtonActionListener
     */
    public void registerButtonActionListener() {
        for (int i = 0; i < jButtonArray.length; i++) {
            registerButtonActionListener(jButtonArray[i]);
        }// for
    }// registerButtonActionListener

    /**
     * Sets the callButtons actionListener
     * @param aL ActionListener for the callButtons
     */
    public void setCallButtonActionListener(ActionListener aL) {
        this.cBaL = aL;
    }// setCallButtonActionListener

    /**
     * Updates the ElevatorLabels
     * @param eL ElevatorLabel to be updated
     */
    public void updateElevatorLabel(ElevatorLabel eL) {
        for (ElevatorLabel eL2 : labelList) {
            if (eL.equals(eL2)) {
                eL2.setBounds(eL.getBounds());
                eL2.repaint();
            }// if
        }// for
    }//updateElevatorLabel

    public void setLabelList(List<ElevatorLabel> labelList) {
        this.labelList = labelList;
    }//setLabelList

    public List<ElevatorLabel> getLabelList() {
        return labelList;
    }//getLabelList
}//ElevatorView
