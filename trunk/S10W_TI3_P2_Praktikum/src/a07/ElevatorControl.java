package a07;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.Executor;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

import javax.swing.JButton;

/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 06<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen: API, http://blog.bigbasti.com/tutorial-model-view-controller-mvc-struktur-in-java-
 * projekten-nutzen/
 * 
 * <br><br><b>Description:</b> <br>This class represents the controller in MVC-Pattern<br>
 * The Controller holds each model and each view which are used. It initializes the GUI (view) and the elevators (models),
 * adds the ActionListeners and starts the elevator threads.
 *  
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br><br>
 * 
 */

public class ElevatorControl extends Thread {

    private ElevatorModel elevator1;
    private ElevatorModel elevator2;
    private ElevatorView view;
    private ThreadPoolExecutor threadPool;
    private int poolSize = 2;
    private int maxPoolSize = 2;
    private long keepAliveTime = 10; 
    private final ArrayBlockingQueue<Runnable> queue = new ArrayBlockingQueue<Runnable>(5);



    /**
     * @see ElevatorControl Class discription
     */
    public ElevatorControl() {
        this.view = new ElevatorView();
        this.elevator1 = new ElevatorModel("Elevator 1", view);
        this.elevator2 = new ElevatorModel("Elevator 2", view);
        this.threadPool = new ThreadPoolExecutor(poolSize, maxPoolSize, keepAliveTime, TimeUnit.SECONDS, queue);
        addListener();
        //        elevator1.start();
//        elevator2.start();
        threadPool.submit(elevator1);
        threadPool.submit(elevator2);
    }// ElevatorControl

    /**
     * Initializes a new CallButtonActionListener
     * @return ActionListener: CallButtonActionListener
     */
    public ActionListener getCallButtonActionListener() {
        ActionListener aL = new CallButtonActionListener();
        return aL;
    }// getCallButtonActionListener

    /**
     * Sets the CallButtonActionListener of the view and registers them in the view.
     */
    private void addListener() {
        view.setCallButtonActionListener(new CallButtonActionListener());
        view.registerButtonActionListener();

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
            }//if
            if (source.getText().contains("Thrid  floor")) {
                if (source.getName().contains("Elevator 1")) {
                    elevator1.callElevator(3);
                } else if (source.getName().contains("Elevator 2")) {
                    elevator2.callElevator(3);
                }// else
            }//if
            if (source.getText().contains("Fourth floor")) {
                if (source.getName().contains("Elevator 1")) {
                    elevator1.callElevator(4);
                } else if (source.getName().contains("Elevator 2")) {
                    elevator2.callElevator(4);
                }// else
            }//if
        }// actionPerformed
    }// CallButtonActionListener
 
    public ElevatorView getView() {
        return view;
    }//getView
}// ElevatorControl
