package a06;

import a05.RingBuffer;

public class ElevatorModel extends Thread {

    private boolean[] floorList = new boolean[5]; // FloorList for 5 Floors
    private int actualFloor;
    private boolean doorOpen;
    private boolean priorityDrive;
    private String elevatorInfo;
    private ElevatorView view;
    private boolean work = true;
    private ElevatorLabel eL;

    // private RingBuffer<Integer> targets;

    // Constructor
    public ElevatorModel(String info, ElevatorView view) {
        // this.targets = new RingBuffer<Integer>(Constants.FLOORNO); //target list
        this.view = view;
        this.actualFloor = 0; // GroundFloor
        this.doorOpen = true;
        this.priorityDrive = false;
        this.elevatorInfo = info;
    }// ElevatorModel

    // call Elevator to a specific floor
    public void callElevator(int floor) {
        System.out.println("Elevator called!");
        if (floor < 5) {
            boolean[] fL = this.getFloorList();
            fL[floor] = true;
            this.setFloorList(fL);
        }else {
            System.out.println(this.getElevatorInfo() + "'s floor does not exist!");
        }
    }// callElevator

    public void move() throws InterruptedException {
        System.out.println("In Move!");
        System.out.println("Work: " + work);
        while (work) {
            boolean[] fL = this.getFloorList();
            for (int i = 0; i < this.floorList.length; i++) { // iterate over floorList
                if (fL[i]) { // if floor is true (selected)
                    if (i == this.getActualFloor()) { // if selected floor equals actualFloor
                        fL[i] = false; // disable selection
                    }else { // check if selected floor is smaller than actualFloor
                        if (i < this.getActualFloor()) {
                            this.setDoorOpen(false);
                            System.out.println(this.getElevatorInfo() + " Door closed.");
                            System.out.println(this.getElevatorInfo() + " Moving from Floor " + this.getActualFloor()
                                    + "to Floor " + i);
                            for (; i != this.getActualFloor();) {
                                decrementFloor();
                                moveLabel(0);
                                System.out.println(this.getElevatorInfo() + " now on Floor " + this.getActualFloor());
                            }
                            fL[i] = false; // if elevator has reached selected floor
                            this.setFloorList(fL); // set selection to false and update fL
                            System.out.println(this.getElevatorInfo() + " has reached destination Floor "
                                    + this.getActualFloor());
                            this.setDoorOpen(true);
                            System.out.println(this.getElevatorInfo() + " Door opened.");
                        }else {
                            this.setDoorOpen(false);
                            System.out.println(this.getElevatorInfo() + " Door closed.");
                            System.out.println(this.getElevatorInfo() + " Moving from Floor " + this.getActualFloor()
                                    + "to Floor " + i);
                            for (; i != this.getActualFloor();) {
                                incrementFloor();
                                moveLabel(1);
                                System.out.println(this.getElevatorInfo() + " now on Floor " + this.getActualFloor());
                            }
                            fL[i] = false; // if elevator has reached selected floor
                            this.setFloorList(fL); // set selection to false and update fL
                            System.out.println(this.getElevatorInfo() + " has reached destination Floor "
                                    + this.getActualFloor());
                            this.setDoorOpen(true);
                            System.out.println(this.getElevatorInfo() + " Door opened.");
                        }// else
                    }// else
                }// if
            }// for
            for (boolean cFL : this.getFloorList()) { // check if there is something to do
                work = false;
                if (cFL) {
                    work = true;
                }// if
            }// for
            System.out.println("Boolean work = " + work);
        }// while
    }// move
    
    private void moveLabel(int destination) throws InterruptedException{
//        int goTo = 0;
//        
//        // floor dist 115
//        switch (eL.getY()) {
//            case 0:
//                goTo = eL.getGroundFloor();
//                break;
//            case 1:
//                goTo = eL.getFirstFloor();
//                break;
//            case 2:
//                goTo = eL.getSecondFloor();
//                break;
//            case 3:
//                goTo = eL.getThirdFloor();
//                break;
//            case 4:
//                goTo = eL.getFourthFloor();
//                break;
//        }//switch
////        System.out.println("goTo: "+goTo);
//        
//        
        // Up and down schleifen!!!!
        //Down
        
        System.out.println("In MoveLabel!");
        if(destination == 0){
            System.out.println("Down Schleife!");
//            System.out.println("In y < goTo");
            for (int i = 0; i < 115; i++){
                eL.setY(eL.getY()+1);
                eL.setBounds(eL.getX(), eL.getY(), eL.getBoundX(), eL.getBoundY());
                view.updateElevatorLabel(eL);
                Thread.sleep(10);
            }
        }
        //Up
        if(destination == 1){
//            System.out.println("In y > goTo");
            System.out.println("Down Schleife!");
            for (int i = 0; i < 115; i++){
                eL.setY(eL.getY()-1);
                eL.setBounds(eL.getX(), eL.getY(), eL.getBoundX(), eL.getBoundY());
                view.updateElevatorLabel(eL);
                Thread.sleep(10);
            }
        }
//            this.repaint();
//            Thread.sleep(10);
//        }else {
//            eL.setWork(false);
//        }//else
        
    }//moveLabel

    public void run() {
        System.out.println("Thread Started!");
        work = true;
        for (ElevatorLabel eL : view.getLabelList()) {
            System.out.println(eL.getName() + " == "+this.getElevatorInfo()+ " ?");
            if(eL.getName().equals(this.getElevatorInfo())){
                this.eL = eL;
            }//if
        }//for
        while (true) {
            if (work == true) {
                try {
                    move();
                }catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }// catch
            }else{
                try {
                    sleep(200);
                }catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }//else
            for (boolean cFL : this.getFloorList()) { // check if there is something to do
                work = false;
                if (cFL) {
                    work = true;
                }// if
            }// for
        }// while
    }

    public void incrementFloor() {
        int aF = this.getActualFloor();
        aF++;
        this.setActualFloor(aF);
    }// incrementFloor

    public void decrementFloor() {
        int aF = this.getActualFloor();
        aF--;
        this.setActualFloor(aF);
    }// decrementFloor

    public int getActualFloor() {
        return actualFloor;
    }// getActualFloor

    public void setActualFloor(int actualFloor) {
        this.actualFloor = actualFloor;
    }// setActualFloor

    public boolean isDoorOpen() {
        return doorOpen;
    }// isDoorOpen

    public void setDoorOpen(boolean doorOpen) {
        this.doorOpen = doorOpen;
    }// setDoorOpen

    public boolean isPriorityDrive() {
        return priorityDrive;
    }// isPriorityDrive

    public void setPriorityDrive(boolean priorityDrive) {
        this.priorityDrive = priorityDrive;
    }

    public void setFloorList(boolean[] floorList) {
        this.floorList = floorList;
    }

    public boolean[] getFloorList() {
        return floorList;
    }

    public String getElevatorInfo() {
        return elevatorInfo;
    }
}
