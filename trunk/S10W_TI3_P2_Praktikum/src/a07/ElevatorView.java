package a07;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionListener;
import java.awt.event.KeyListener;
import java.awt.event.MouseListener;
import java.util.ArrayList;
import java.util.List;

import javax.swing.*;

/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 07<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing
 * 
 * <br>
 * <br>
 * <b>Description:</b> <br>
 * This class represents the GUI or the view in MVC-Pattern.<br>
 * Including the JPanels for the different Areas, the LabelList for the ElevatorLabels, the JButton[] for the
 * CallButtons and the ActionListener for the Buttons.
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 * <br>
 * 
 */

public class ElevatorView extends JPanel {

    private static final long serialVersionUID = 1L;
    private JPanel callArea, callArea2, controlArea, viewArea, mainArea;
    private List<ElevatorLabel> elevatorLabelList = new ArrayList<ElevatorLabel>();
    private List<ElevatorGuy> guyLabelList = new ArrayList<ElevatorGuy>();
    private JButton[] jButtonArray = new JButton[((Constants.FLOORNO * 2) + Constants.ELEVATORNO)];
    private JCheckBox[] jCheckBoxArray = new JCheckBox[Constants.ELEVATORNO];
    private ActionListener cBaL, cBBaL;
    private MouseListener kDOmL;
    private KeyListener eGkL;

    /**
     * Empty Constructor.<br>
     * To create the other JPanel Areas call initElevatorView().
     */
    ElevatorView() {
        //Empty
    }// ElevatorView

    /**
     * Creates the JPanel Areas, adds the mainArea to this panel and repaints it.
     */
    public void initElevatorView() {
        createCallArea();
        createControlArea();
        createViewArea();
        createMainArea();
        this.add(mainArea);
        this.repaint();
    }// initElevatorView

    /**
     * Creates the mainArea and adds sub panels to its BorderLayout.<br>
     * controlArea = NORTH<br>
     * viewArea = CENTER<br>
     * callArea = WEST<br>
     * callArea2 = EAST<br>
     */
    private void createMainArea() {// Border Layout
        mainArea = new JPanel(new BorderLayout());
        mainArea.add(controlArea, BorderLayout.NORTH);
        mainArea.add(viewArea, BorderLayout.CENTER);
        mainArea.add(callArea, BorderLayout.WEST);
        mainArea.add(callArea2, BorderLayout.EAST);
    }// createMainArea

    /**
     * Creates the viewArea panel with nullLayout and sets its size and border.<br>
     * Also creates and adds the ElevatorLabels and ElevatorGuy to the panel.
     */
    private void createViewArea() {
        viewArea = new JPanel();
        viewArea.setLayout(null);
        viewArea.setPreferredSize(new Dimension(800, 600));
        viewArea.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(""), BorderFactory
                .createEmptyBorder(10, 10, 10, 10)));

        elevatorLabelList.add(new ElevatorLabel(1));
        elevatorLabelList.add(new ElevatorLabel(2));

        for (ElevatorLabel eL : elevatorLabelList) {
            viewArea.add(eL);
        }// for
        for (ElevatorGuy eGuy : guyLabelList) {
            viewArea.add(eGuy);
            eGuy.repaint();
        }// for
    }// createViewArea

    /**
     * Creates the controlArea panel with BoxLayout (X_AXIS) and sets its border.<br>
     * Also creates and adds the priorityDrive and keepDoorsOpen buttons to the panel.
     */
    private void createControlArea() {
        controlArea = new JPanel();
        controlArea.setLayout(new BoxLayout(controlArea, BoxLayout.X_AXIS));
        controlArea.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(""), BorderFactory
                .createEmptyBorder(10, 10, 10, 10)));
        addOneCheckBoxToCheckBoxArray("Priority Drive 1", controlArea, 0, 1);
        addOneCheckBoxToCheckBoxArray("Priority Drive 2", controlArea, 1, 2);
        addOneButtonToButtonArray("< 1 >", controlArea, 10, 1);
        addOneButtonToButtonArray("< 2 >", controlArea, 11, 2);
    }// createControlArea

    /**
     * Creates the callAreas panels with GridLayouts (vert) and borders.<br>
     * Also creates and adds the callButtons to the panel
     */
    private void createCallArea() { // Grid Layout vert
        callArea = new JPanel();
        callArea2 = new JPanel();
        callArea.setLayout(new GridLayout(5, 1, 5, 5));
        callArea.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(""), BorderFactory
                .createEmptyBorder(10, 10, 10, 10)));
        callArea2.setLayout(new GridLayout(5, 1, 5, 5));
        callArea2.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createTitledBorder(""), BorderFactory
                .createEmptyBorder(10, 10, 10, 10)));

        addCallButtonsToPanel(callArea);
        addCallButtonsToPanel(callArea2);
    }// createCallArea

    /**
     * Adds one button to the JButtonArray and adds it to the specified panel.
     * 
     * @param text
     *            String: JButtons text
     * @param pane
     *            JPanel: Panel to add button to
     * @param index
     *            int: JButtonArray index number
     * @param i
     *            int: Elevator number
     */
    private void addOneButtonToButtonArray(String text, JPanel pane, int index, int i) {
        JButton button = new JButton(text);
        button.setName(text + " Elevator " + i);
        button.setAlignmentX(Component.CENTER_ALIGNMENT);
        jButtonArray[index] = button;
        if (jButtonArray[index] != null) {
            pane.add(jButtonArray[index]);
        }else {
            System.out.println("Init of jButtonArraY[" + index + "] with name: " + jButtonArray[index].getText()
                    + " failed!");
        }// else
    }// addOneButtonToButtonArray

    /**
     * Adds one button to the CheckBoxArray and adds it to the specified panel.
     * 
     * @param text
     *            String: JButtons text
     * @param pane
     *            JPanel: Panel to add button to
     * @param index
     *            int: JButtonArray index number
     * @param i
     *            int: Elevator number
     */
    private void addOneCheckBoxToCheckBoxArray(String text, JPanel pane, int index, int i) {
        JCheckBox checkBox = new JCheckBox(text);
        checkBox.setName(text + " Elevator " + i);
        checkBox.setAlignmentX(Component.CENTER_ALIGNMENT);
        jCheckBoxArray[index] = checkBox;
        if (jCheckBoxArray[index] != null) {
            pane.add(jCheckBoxArray[index]);
        }else {
            System.out.println("Init of jCheckBoxArray[" + index + "] with name: " + jCheckBoxArray[index].getText()
                    + " failed!");
        }// else
    }// addOneButtonToButtonArray

    /**
     * Calls the addOneButtonToButtonArray for the specified buttons
     * 
     * @param pane
     *            Panel: Panel to add callButtons to
     * @see ElevatorView#addOneButtonToButtonArray addOneButtonToButtonArray
     */
    private void addCallButtonsToPanel(JPanel pane) {
        if (pane == callArea) {
            addOneButtonToButtonArray("Fourth floor", pane, 4, 1);
            addOneButtonToButtonArray("Third  floor", pane, 3, 1);
            addOneButtonToButtonArray("Second floor", pane, 2, 1);
            addOneButtonToButtonArray("First  floor", pane, 1, 1);
            addOneButtonToButtonArray("Ground floor", pane, 0, 1);
        }else if (pane == callArea2) {
            addOneButtonToButtonArray("Fourth floor", pane, 9, 2);
            addOneButtonToButtonArray("Third  floor", pane, 8, 2);
            addOneButtonToButtonArray("Second floor", pane, 7, 2);
            addOneButtonToButtonArray("First  floor", pane, 6, 2);
            addOneButtonToButtonArray("Ground floor", pane, 5, 2);
        }// else
    }// addArrayCallButtonsToPanel

    /**
     * Adds the listeners to the button
     * 
     * @param button
     *            JButton: Button to addListener to
     */
    private void registerButtonListener(JButton button) {
        if (button.getText().contains("floor")) {
            button.addActionListener(cBaL);
            button.addKeyListener(eGkL);
        }else if (button.getText().contains("< ") && button.getText().contains(" >")) {
            button.addMouseListener(kDOmL);
            button.addKeyListener(eGkL);
        }// else
    }// registerButtonActionListeners

    /**
     * Adds the listener to the checkBox
     * 
     * @param checkBox
     *            JCheckBox: CheckBox to addListener to
     */
    private void registerCheckBoxButtonActionListener(JCheckBox checkBox) {
        if (checkBox.getText().contains("Priority")) {
            checkBox.addActionListener(cBBaL);
            checkBox.addKeyListener(eGkL);
        }// if
    }// registerButtonActionListeners

    /**
     * Calls the registerButtonListener(JButton) for each button from jButtonArray[]
     * 
     * @see ElevatorView#registerButtonListener(JButton) registerButtonActionListener
     */
    public void registerButtonActionListener() {
        for (int i = 0; i < jButtonArray.length; i++) {
            registerButtonListener(jButtonArray[i]);
        }// for
    }// registerButtonActionListener

    /**
     * Calls the registerCheckBoxButtonActionListener(JCheckBox) for each CheckBox from jCheckBoxArray[]
     * 
     * @see ElevatorView#registerCheckBoxButtonActionListener(JCheckBox) registerCheckBoxButtonActionListerner
     */
    public void registerCheckBoxButtonActionListener() {
        for (int i = 0; i < jCheckBoxArray.length; i++) {
            registerCheckBoxButtonActionListener(jCheckBoxArray[i]);
        }// for
    }// registerButtonActionListener

    /**
     * Registers the ElevatorGuyKeyListener to the mainArea and sets the mainArea Focusable.
     */
    public void registerElevatorGuyKeyListener() {
        this.mainArea.setFocusable(true);
        this.mainArea.addKeyListener(eGkL);
    }// registerButtonActionListener

    /**
     * Sets the callButtons actionListener
     * 
     * @param aL
     *            ActionListener for the callButtons
     */
    public void setCallButtonActionListener(ActionListener aL) {
        this.cBaL = aL;
    }// setCallButtonActionListener

    /**
     * Sets the checkBoxButtons actionListener
     * 
     * @param aL
     */
    public void setCheckBoxButtonActionListener(ActionListener aL) {
        this.cBBaL = aL;
    }// setCallButtonActionListener

    /**
     * Sets the keepDoorsOpen mouseListener
     * 
     * @param mL
     */
    public void setKeepDoorsOpenMouseListener(MouseListener mL) {
        this.kDOmL = mL;
    }// setCallButtonActionListener

    /**
     * Sets the elevatorGuys keyListener
     * 
     * @param kL
     */
    public void setElevatorGuyListener(KeyListener kL) {
        this.eGkL = kL;
    }// setCallButtonActionListener

    /**
     * Updates the ElevatorLabels
     * 
     * @param eL
     *            ElevatorLabel to be updated
     */
    public void updateElevatorLabel(ElevatorLabel eL) {
        for (ElevatorLabel eL2 : elevatorLabelList) {
            if (eL.equals(eL2)) {
                eL2.setBounds(eL.getBounds());
                eL2.repaint();
            }// if
        }// for
    }// updateElevatorLabel

    /**
     * Updates the ElevatorGuy
     * 
     * @param eG
     *            ElevatorGuy to be updated
     */
    public void updateElevatorGuy(ElevatorGuy eG) {
        eG.repaint();
    }// updateElevatorLabel

    public void setLabelList(List<ElevatorLabel> labelList) {
        this.elevatorLabelList = labelList;
    }// setLabelList

    public List<ElevatorLabel> getLabelList() {
        return elevatorLabelList;
    }// getLabelList

    public void setElevatorGuy(ElevatorGuy eG) {
        if (eG != null) {
        }
        this.guyLabelList.add(eG);
    }// setCallButtonActionListener

    public List<ElevatorGuy> getGuyLabelList() {
        return guyLabelList;
    }// getGuyLabelList

}// ElevatorView
