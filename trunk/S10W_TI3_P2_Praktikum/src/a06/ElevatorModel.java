package a06;

import java.awt.Color;

import a05.RingBuffer;

public class ElevatorModel extends Thread {

    private int actualFloor;
    private boolean doorOpen;
    private String elevatorInfo;
    private ElevatorView view;
    private boolean work = true;
    private ElevatorLabel eL;
    private RingBuffer<Integer> targets;
    
    /**
     * 
     * @param info String: Elevator Name
     * @param view ElevatorView: GUI
     */
    // Constructor
    public ElevatorModel(String info, ElevatorView view) {
        this.targets = new RingBuffer<Integer>(Constants.FLOORNO); // target
        // list
        this.view = view;
        this.actualFloor = 0; // GroundFloor
        this.setDoorOpen(true);
        this.elevatorInfo = info;
    }// ElevatorModel

    /**
     * call Elevator to a specific floor
     * @param floor int: number of floor 
     */
    public void callElevator(int floor) {
        System.out.println("Elevator called!");
        if (floor < 5) {
            this.targets.enqueue(floor);
        } else {
            System.out.println(this.elevatorInfo + "'s floor does not exist!");
        }
    }// callElevator

    /**
     * Elevators move() to move the elevator to the target from targetList
     * @throws InterruptedException
     */
    public void move() throws InterruptedException {
        // System.out.println("In Move!");
        // System.out.println("Work: " + work);
        while (work) {
            if (!targets.isEmpty()){
                int target = targets.peek();
                if (target == this.actualFloor) { // if selected floor
                    // equals actualFloor
                    targets.dequeue(); //remove target from targetList
                } else { // check if selected floor is smaller than
                    // actualFloor
                    if (target < this.actualFloor) {
                        this.setDoorOpen(false);
                        eL.setBackground(Color.RED);
                        System.out.println(this.elevatorInfo + " Door closed.");
                        Thread.sleep(500);
                        System.out.println(this.elevatorInfo + " Moving from Floor " + this.actualFloor + " to Floor " + target);
                        for (; target != this.actualFloor;) {
                            this.actualFloor --;
                            moveLabel(0);
                            System.out.println(this.elevatorInfo + " now on Floor " + this.actualFloor);
                        }//for
                        targets.dequeue(); // if elevator has reached selected
                        // floor remove target from targetList
                        System.out.println(this.elevatorInfo + " has reached destination Floor " + this.actualFloor);
                        this.setDoorOpen(true);
                        eL.setBackground(Color.GREEN);
                        System.out.println(this.elevatorInfo + " Door opened.");
                        Thread.sleep(1000);
                    } else {
                        this.setDoorOpen(false);
                        eL.setBackground(Color.RED);
                        System.out.println(this.elevatorInfo + " Door closed.");
                        Thread.sleep(500);
                        System.out.println(this.elevatorInfo + " Moving from Floor " + this.actualFloor + " to Floor " + target);
                        for (; target != this.actualFloor;) {
                            actualFloor++;
                            moveLabel(1);
                            System.out.println(this.elevatorInfo + " now on Floor " + this.actualFloor);
                        }//for
                        targets.dequeue(); // if elevator has reached selected floor
                        System.out.println(this.elevatorInfo + " has reached destination Floor " + this.actualFloor);
                        this.setDoorOpen(true);
                        eL.setBackground(Color.GREEN);
                        System.out.println(this.elevatorInfo + " Door opened.");
                        Thread.sleep(1000);
                    }// else
                }// else
            }else {
                work = false;
            }//else
//            System.out.println("Boolean work = " + work);
        }// while
    }// move

    /**
     * moves the elevators label to specified direction
     * @param direction int: up = 1, down = 0;
     * @throws InterruptedException
     */
    private void moveLabel(int direction) throws InterruptedException {
        // Down
        // System.out.println("In MoveLabel!");
        if (direction == 0) {
//            System.out.println("Down Schleife!");
            for (int i = 0; i < 115; i++) {
                eL.setY(eL.getY() + 1);
                eL.setBounds(eL.getX(), eL.getY(), eL.getBoundX(), eL.getBoundY());
                view.updateElevatorLabel(eL);
                Thread.sleep(10);
            }// for
        }// if
        // Up
        if (direction == 1) {
//            System.out.println("Up Schleife!");
            for (int i = 0; i < 115; i++) {
                eL.setY(eL.getY() - 1);
                eL.setBounds(eL.getX(), eL.getY(), eL.getBoundX(), eL.getBoundY());
                view.updateElevatorLabel(eL);
                Thread.sleep(10);
            }// for
        }// if
    }// moveLabel

    /**
     * Threads run() looks if there are targets in targetList and resolves the belonging ElevatorLabel.<br> 
     * while (true) {<br>
     * If there are targets in the targetList the thread calls move()<br>
     * Otherwise it makes a Sleep(200) and checks for targets in targetList.
     * If there are targets it sets the boolean work to true.<br>
     * }
     */
    public void run() {
        System.out.println(Thread.currentThread().getName() + " Started!");
        if(!targets.isEmpty()){
            work = true;            
        }//if
        for (ElevatorLabel eL : view.getLabelList()) {
            if (eL.getName().equals(this.elevatorInfo)) {
//                System.out.println("In run(): Found Elevator. Setting this.eL = eL");
                this.eL = eL;
                break;
            }// if
        }// for
        while (true) {
            // System.out.println("In run(): boolean work = " + work);
            if (work) {
                try {
                    move();
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }// catch
            } else {
                try {
                    sleep(200);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }// catch
                //check if there's something to do
                if(!targets.isEmpty()){
                    work = true;            
                }//if
            }// else
        }// while
    }//run

    public void setDoorOpen(boolean doorOpen) {
        this.doorOpen = doorOpen;
    }//setDoorOpen

    public boolean isDoorOpen() {
        return doorOpen;
    }//isDoorOpen
    
}//ElevatorModel
