package a07;

import java.awt.Color;

/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 06<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen: API
 * 
 * <br>
 * <br>
 * <b>Description:</b> <br>
 * This class represents the ElevatorModel or the (data-)model in MVC-Pattern.<br>
 * 
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 * <br>
 * 
 */

public class ElevatorModel implements Runnable {

    private int actualFloor;
    private boolean doorOpen;
    private boolean keepDoorsOpen;
    private String elevatorInfo;
    private ElevatorView view;
    private boolean priorityDrive = false;
    private boolean work = true;
    private ElevatorLabel eL;
    private RingBuffer<Integer> targets;
    private ElevatorGuy eG;

    /**
     * 
     * @param info
     *            String: Elevator Name
     * @param view
     *            ElevatorView: GUI
     */
    // Constructor
    public ElevatorModel(String info, ElevatorView view) {
        this.targets = new RingBuffer<Integer>(Constants.FLOORNO); 
        this.view = view;
        this.actualFloor = 0; // GroundFloor
        this.doorOpen = true;
        this.keepDoorsOpen = false;
        this.elevatorInfo = info;
    }// ElevatorModel

    /**
     * Calls the Elevator to a specific floor with priority drive function
     * 
     * @param floor
     *            int: number of floor
     */
    public void callElevator(int floor) {
        System.out.println("Elevator called!");
        if (floor < Constants.FLOORNO) {
            if (this.priorityDrive) {
                if (!this.targets.isEmpty()) {
                    for (; !this.targets.isEmpty();) { // Delete queue
                        this.targets.dequeue();
                    }// for
                }// if
                this.targets.enqueue(floor);
            } else if (!this.targets.isFull()) {
                this.targets.enqueue(floor);
            }// else
        } else {
            System.out.println(this.elevatorInfo + "'s floor does not exist!");
        }// else
    }// callElevator

    /**
     * Elevators move() to move the elevator to the target from targetList
     * and to move the elevatorGuy if hes in the elevator.<br>
     * 
     * @throws InterruptedException
     */
    private void move() throws InterruptedException {
        boolean priorityFired = false;
        while (work) {
            if (!targets.isEmpty()) {
                int target = targets.peek();
                if (target == this.actualFloor) { // if selected floor equals actualFloor
                    targets.dequeue(); // remove target from targetList
                } else {
                    // check if selected floor is smaller than actualFloor
                    if (target < this.actualFloor) {
                        if (this.doorOpen) {
                            lightBarrierCheck();
                            this.doorOpen = false;
                            eL.setBackground(Color.RED);
                            System.out.println(this.elevatorInfo + " Door closed.");
                            Thread.sleep(500);
                            System.out.println(this.elevatorInfo + " Moving from Floor " + this.actualFloor + " to Floor " + target);
                        }// if
                        if (priorityFired) {
                            System.out.println(this.elevatorInfo + " moving on to Floor " + target);
                        }// if
                        for (; target != this.actualFloor;) {
                            this.actualFloor--;
                            moveGuy(0);
                            moveLabel(0);
                            System.out.println(this.elevatorInfo + " now on Floor " + this.actualFloor);
                        }// for
                        // if elevator has reached selected floor and target is still the actual target
                        if (targets.peek() == target) {
                            targets.dequeue();// remove target from targetList
                            System.out.println(this.elevatorInfo + " has reached destination Floor " + this.actualFloor);
                            this.doorOpen = true;
                            eL.setBackground(Color.GREEN);
                            System.out.println(this.elevatorInfo + " Door opened.");
                            if (this.keepDoorsOpen) {
                                keepDoorsOpen();
                            } else {
                                Thread.sleep(1000);
                            }// else
                            priorityFired = false;
                        } else {
                            priorityFired = true;
                        }// else
                    } else {
                        if (doorOpen) {
                            lightBarrierCheck();
                            this.doorOpen = false;
                            eL.setBackground(Color.RED);
                            System.out.println(this.elevatorInfo + " Door closed.");
                            Thread.sleep(500);
                            System.out.println(this.elevatorInfo + " Moving from Floor " + this.actualFloor + " to Floor " + target);
                        }// if
                        if (priorityFired) {
                            System.out.println(this.elevatorInfo + " moving on to Floor " + target);
                        }// if
                        for (; target != this.actualFloor;) {
                            actualFloor++;
                            moveGuy(1);
                            moveLabel(1);
                            System.out.println(this.elevatorInfo + " now on Floor " + this.actualFloor);
                        }// for
                        // if elevator has reached selected floor and target is still the actual target
                        if (targets.peek() == target) {
                            targets.dequeue(); // remove target from targetList
                            System.out.println(this.elevatorInfo + " has reached destination Floor " + this.actualFloor);
                            this.doorOpen = true;
                            eL.setBackground(Color.GREEN);
                            System.out.println(this.elevatorInfo + " Door opened.");
                            if (this.keepDoorsOpen) {
                                keepDoorsOpen();
                            } else {
                                Thread.sleep(1000);
                            }// else
                            priorityFired = false;
                        } else {
                            priorityFired = true;
                        }
                    }// else
                }// else
            } else {
                work = false;
            }// else
        }// while
    }// move

    /**
     * Implements a light barrier of the elevator to be sure that the elevator only moves when no one is between the doors.<br>
     * @throws InterruptedException
     */
    private void lightBarrierCheck() throws InterruptedException {

        if (this.elevatorInfo == "Elevator 1") {
            if (eG.getY() - 20 == eL.getY()) {
                while (eG.getX() < Constants.ELEVATORLEFTENTRY && eG.getX() > eL.getX() + eL.getBoundX() - eG.getBoundX()) {
                    System.out.println(this.elevatorInfo + ": Person in light barrier.");
                    Thread.sleep(500);
                }//while
            }//if
        }//if

        if (this.elevatorInfo == "Elevator 2") {
            System.out.println((this.eG.getY() - 20) + " == " + this.eL.getY());
            System.out.println("Checking " + this.elevatorInfo + "s light barrier");
            // if(eG.getX() > Constants.ELEVATORRIGHTENTRY-eG.getBoundX()){
            if (eG.getY() - 20 == eL.getY()) {
                System.out.println(eG.getName() + "is on same floor as " + this.elevatorInfo);
                // while(eG.getX() < eL.getX() && ){
                while (eG.getX() > 650 && eG.getX() < 700) {
                    System.out.println(this.elevatorInfo + ": Person in light barrier.");
                    Thread.sleep(500);
                }//while
            }//if
        }//if
    }//lightBarrierCheck

    /**
     * Keeps the elevators doors for max 5 seconds open.
     * @throws InterruptedException
     */
    private void keepDoorsOpen() throws InterruptedException {
        System.out.printf("Keeping Doors Open");
        int counter = 0;
        while (this.keepDoorsOpen && counter < Constants.MAXKEEPDOORSOPENTIME) {
            counter += 500;
            System.out.printf(".");
            Thread.sleep(500);
        }// while
        System.out.printf("\n");
    }// keepDoorsOpen

    /**
     * Moves the elevators label to specified direction
     * 
     * @param direction
     *            int: up = 1, down = 0;
     * @throws InterruptedException
     */
    private void moveLabel(int direction) throws InterruptedException {
        // Down
        if (direction == 0) {
            for (int i = 0; i < 115; i++) {
                eL.setY(eL.getY() + 1);
                eL.setBounds(eL.getX(), eL.getY(), eL.getBoundX(), eL.getBoundY());
                view.updateElevatorLabel(eL);
                Thread.sleep(10);
            }// for
        }// if
        
        // Up
        if (direction == 1) {
            for (int i = 0; i < 115; i++) {
                eL.setY(eL.getY() - 1);
                eL.setBounds(eL.getX(), eL.getY(), eL.getBoundX(), eL.getBoundY());
                view.updateElevatorLabel(eL);
                Thread.sleep(10);
            }// for
        }// if
    }// moveLabel

    /**
     * When the elevatorGuy is in the elevator he is moved to the specified direction.
     * @param direction : 0 = down, 1 = up
     */
    private void moveGuy(int direction) {
        // Down
        if (direction == 0) {
            if (eG.getY() - 20 == eL.getY()) {
                if (this.elevatorInfo == "Elevator 1") {
                    if(eG.getX() <= Constants.ELEVATORLEFTENTRY && eL.getY() == (eG.getY() - (eL.getBoundY() - eG.getBoundY()))){
                        this.eG.setY(eG.getY() + 115);
                        view.updateElevatorGuy(eG);
                    }//if
                }else if (this.elevatorInfo == "Elevator 2") {
                    if(eG.getX() >= Constants.ELEVATORRIGHTENTRY-eG.getBoundX() && eL.getY() == (eG.getY() - (eL.getBoundY() - eG.getBoundY()))){
                        this.eG.setY(eG.getY() + 115);     
                        view.updateElevatorGuy(eG);
                    }//if
                }//if
            }//if
        }// if
        // Up
        if (direction == 1) {
            if (eG.getY() - 20 == eL.getY()) {
                if (this.elevatorInfo == "Elevator 1") {
                    if(eG.getX() <= Constants.ELEVATORLEFTENTRY && eL.getY() == (eG.getY() - (eL.getBoundY() - eG.getBoundY()))){
                        this.eG.setY(eG.getY() - 115);
                        view.updateElevatorGuy(eG);
                    }//if
                }else if (this.elevatorInfo == "Elevator 2") {
                    if(eG.getX() >= Constants.ELEVATORRIGHTENTRY-eG.getBoundX() && eL.getY() == (eG.getY() - (eL.getBoundY() - eG.getBoundY()))){
                        this.eG.setY(eG.getY() - 115);
                        view.updateElevatorGuy(eG);
                    }//if
                }//if
            }//if
        }// if
    }//moveGuy

    /**
     * Threads run() looks if there are targets in targetList and resolves the belonging ElevatorLabel.<br>
     * while (true) {<br>
     * If there are targets in the targetList the thread calls move()<br>
     * Otherwise it makes a Sleep(200) and checks for targets in targetList. If there are targets it sets the boolean
     * work to true.<br>
     * }
     */
    public void run() {
        if (!targets.isEmpty()) {
            work = true;
        }// if
        for (ElevatorLabel eL : view.getLabelList()) {
            if (eL.getName().equals(this.elevatorInfo)) {
                this.eL = eL;
                break;
            }// if
        }// for
        for (ElevatorGuy eG : view.getGuyLabelList()) {
            if (eG.getName().equals("Elevator Guy 1")) {
                this.eG = eG;
                break;
            }// if
        }// for
        while (true) {
            if (work) {
                try {
                    move();
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }// catch
            } else {
                try {
                    Thread.sleep(200);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }// catch
                // check if there's something to do
                if (!targets.isEmpty()) {
                    work = true;
                }// if
            }// else
        }// while
    }// run

    public void setPriorityDrive(boolean priorityDrive) {
        this.priorityDrive = priorityDrive;
    }// setPriorityDrive

    public void setKeepDoorsOpen(boolean keepDoorsOpen) {
        this.keepDoorsOpen = keepDoorsOpen;
    }// setKeepDoorsOpen
}// ElevatorModel
