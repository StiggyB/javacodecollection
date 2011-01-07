package a07;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

import javax.swing.JButton;
import javax.swing.JCheckBox;

/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 06<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen: API, http://blog.bigbasti.com/tutorial-model-view-controller-mvc-struktur-in-java- projekten-nutzen/
 * 
 * <br>
 * <br>
 * <b>Description:</b> <br>
 * This class represents the controller in MVC-Pattern<br>
 * The Controller holds each model and each view which are used. It initializes the GUI (view) and the elevators
 * (models), adds the ActionListeners and starts the elevator threads.
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 * <br>
 * 
 */

public class ElevatorControl extends Thread {

    private ElevatorModel elevator1;
    private ElevatorModel elevator2;
    private ElevatorView view;
    private ElevatorGuy guy1;
    private ThreadPoolExecutor threadPool;
    private int poolSize = Constants.FLOORNO;
    private int maxPoolSize = Constants.FLOORNO;
    private long keepAliveTime = 10;
    private final ArrayBlockingQueue<Runnable> queue = new ArrayBlockingQueue<Runnable>(5);

    /**
     * @see ElevatorControl Class discription
     */
    public ElevatorControl() {
        this.threadPool = new ThreadPoolExecutor(poolSize, maxPoolSize, keepAliveTime, TimeUnit.SECONDS, queue);
        this.guy1 = new ElevatorGuy(Constants.GROUNDFLOORYPOS, "Guy 1");
        this.view = new ElevatorView();
        this.view.setElevatorGuy(this.guy1);
        this.view.initElevatorView();
        this.guy1.setView(view);
        
        this.elevator1 = new ElevatorModel("Elevator 1", view);
        this.elevator2 = new ElevatorModel("Elevator 2", view);
        addListener();
        threadPool.submit(elevator1);
        threadPool.submit(elevator2);
        threadPool.submit(guy1);
    }// ElevatorControl

     /**
     * Initializes a new CallButtonActionListener
     * @return ActionListener: CallButtonActionListener
     */
     public KeyListener getElevatorGuyKeyListener() {
     KeyListener kL = new ElevatorGuyKeyListener();
     return kL;
     }// getCallButtonActionListener

    /**
     * Sets the CallButtonActionListener of the view and registers them in the view.
     */
    private void addListener() {
        view.setCallButtonActionListener(new CallButtonActionListener());
        view.setCheckBoxButtonActionListener(new CheckBoxButtonActionListener());
        view.setKeepDoorsOpenMouseListener(new KeepDoorsOpenButtonActionListener());
        view.setElevatorGuyListener(new ElevatorGuyKeyListener());
        view.registerButtonActionListener();
        view.registerCheckBoxButtonActionListener();
        view.registerElevatorGuyKeyListener();

    }// addListener

    /**
     * Inner class for CallButtonActionListener.<br>
     * Handles the events when a button is pressed.
     * 
     * 
     */
    private class CallButtonActionListener implements ActionListener {
        public void actionPerformed(ActionEvent ev) {
            JButton source = (JButton) ev.getSource();

            if (source.getText().contains("Ground floor")) {
                if (source.getName().contains("Elevator 1")) {
                    elevator1.callElevator(0);
                } else if (source.getName().contains("Elevator 2")) {
                    elevator2.callElevator(0);
                }// else
            }// if

            if (source.getText().contains("First  floor")) {
                if (source.getName().contains("Elevator 1")) {
                    elevator1.callElevator(1);
                } else if (source.getName().contains("Elevator 2")) {
                    elevator2.callElevator(1);
                }// else
            }// if
            if (source.getText().contains("Second floor")) {
                if (source.getName().contains("Elevator 1")) {
                    elevator1.callElevator(2);
                } else if (source.getName().contains("Elevator 2")) {
                    elevator2.callElevator(2);
                }// else
            }// if
            if (source.getText().contains("Third  floor")) {
                if (source.getName().contains("Elevator 1")) {
                    elevator1.callElevator(3);
                } else if (source.getName().contains("Elevator 2")) {
                    elevator2.callElevator(3);
                }// else
            }// if
            if (source.getText().contains("Fourth floor")) {
                if (source.getName().contains("Elevator 1")) {
                    elevator1.callElevator(4);
                } else if (source.getName().contains("Elevator 2")) {
                    elevator2.callElevator(4);
                }// else
            }// if
        }// actionPerformed
    }// CallButtonActionListener

    private class CheckBoxButtonActionListener implements ActionListener {
        public void actionPerformed(ActionEvent ev) {
            JCheckBox source = (JCheckBox) ev.getSource();
            if (source.getText().contains("Priority Drive 1")) {
                if (source.getName().contains("Elevator 1")) {
                    if (source.isSelected()) {
                        elevator1.setPriorityDrive(true);
                    } else {
                        elevator1.setPriorityDrive(false);
                    }// else
                }// if
            }// if
            if (source.getText().contains("Priority Drive 2")) {
                if (source.getName().contains("Elevator 2")) {
                    if (source.isSelected()) {
                        elevator2.setPriorityDrive(true);
                    } else {
                        elevator2.setPriorityDrive(false);
                    }// else
                }// if
            }// if
        }// actionPerformed
    }// CheckBoxButtonActionListener

    private class KeepDoorsOpenButtonActionListener implements MouseListener {

        @Override
        public void mouseClicked(MouseEvent arg0) {
        }

        @Override
        public void mouseEntered(MouseEvent arg0) {
        }

        @Override
        public void mouseExited(MouseEvent arg0) {
        }

        @Override
        public void mousePressed(MouseEvent me) {
            JButton source = (JButton) me.getSource();
//            System.out.println("Button <" + (source.getText().contains("1") ? 1 : 2) + "> pressed!");
            if (source.getText().contains("< 1 >")) {
                if (source.getName().contains("Elevator 1")) {
                    elevator1.setKeepDoorsOpen(true);
                }// if
            }// if
            if (source.getText().contains("< 2 >")) {
                if (source.getName().contains("Elevator 2")) {
                    elevator2.setKeepDoorsOpen(true);
                }// if
            }// if
        }// mousePressed

        @Override
        public void mouseReleased(MouseEvent me) {
            JButton source = (JButton) me.getSource();
//            System.out.println("Button <" + (source.getText().contains("1") ? 1 : 2) + "> released!");
            if (source.getText().contains("< 1 >")) {
                if (source.getName().contains("Elevator 1")) {
                    elevator1.setKeepDoorsOpen(false);
                }// if
            }// if
            if (source.getText().contains("< 2 >")) {
                if (source.getName().contains("Elevator 2")) {
                    elevator2.setKeepDoorsOpen(false);
                }// if
            }// if
        }// mouseReleased
    }// KeepDoorsOpenButtonActionListener

    private class ElevatorGuyKeyListener implements KeyListener {
        @Override
        public void keyPressed(KeyEvent kE) {
            if (kE.getKeyCode() == KeyEvent.VK_LEFT) {
                guy1.direction = 0;
                guy1.move = true;
//                guy1.setIcon(guy1.getLeftGuy());
//                guy1.repaint();
            }//if
            if (kE.getKeyCode() == KeyEvent.VK_RIGHT) {
                guy1.direction = 1;
                guy1.move = true;
//                guy1.setIcon(guy1.getRightGuy());
//                guy1.repaint();
            }//if
        }//keyPressed

        @Override
        public void keyReleased(KeyEvent kE) {
            if (kE.getKeyCode() == KeyEvent.VK_LEFT) {
                guy1.move = false;
//                guy1.setIcon(guy1.getNormalGuy());
//                guy1.repaint();
                guy1.direction = -1;
            }//if
            if (kE.getKeyCode() == KeyEvent.VK_RIGHT) {
                guy1.move = false;
//                guy1.setIcon(guy1.getNormalGuy());
//                guy1.repaint();
                guy1.direction = -1;
            }//if
        }//keyReleased

        @Override
        public void keyTyped(KeyEvent kE) {
            // TODO Auto-generated method stub

        }
    }

    public ElevatorView getView() {
        return view;
    }// getView

    public ThreadPoolExecutor getThreadPool() {
        return threadPool;
    }
}// ElevatorControl
