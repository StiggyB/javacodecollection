package a06BasicTextElevator;

public class ElevatorModel {

    private boolean[] floorList = new boolean[5]; // FloorList for 5 Floors
    private int actualFloor; 
    private boolean doorOpen; 
    private boolean priorityDrive;
    private String elevatorInfo;

    // Constructor
    public ElevatorModel(String info) {
        this.actualFloor = 0; // GroundFloor
        this.doorOpen = true;
        this.priorityDrive = false;
        this.elevatorInfo = info;
    }// ElevatorModel

    // call Elevator to a specific floor
    public void callElevator(int floor) {
        if (floor < 5) {
            boolean[] fL = this.getFloorList();
            fL[floor] = true;
            this.setFloorList(fL);
            move();
        }else {
            System.out.println(this.getElevatorInfo() + "'s floor does not exist!");
        }
    }// callElevator

    public void move() {
        boolean[] fL = this.getFloorList();
        for (int i = 0; i < this.floorList.length; i++) { // iterate over floorList
            if (fL[i]) { // if floor is true (selected)
                if (i == this.getActualFloor()) { // if selected floor equals actualFloor
                    // do nothing
                }else { // check if selected floor is smaller than actualFloor
                    if (i < this.getActualFloor()) {
                        this.setDoorOpen(false);
                        System.out.println(this.getElevatorInfo() + " Door closed.");
                        System.out.printf(this.getElevatorInfo() + " Moving from Floor " + this.getActualFloor());
                        for (; i != this.getActualFloor();) {
                            decrementFloor();
                        }
                        fL[i] = false; // if elevator has reached selected floor
                        this.setFloorList(fL); // set selection to false and update fL
                        System.out.println(" to Floor " + this.getActualFloor());
                        this.setDoorOpen(true);
                        System.out.println(this.getElevatorInfo() + " Door opened.");
                    }else {
                        this.setDoorOpen(false);
                        System.out.println(this.getElevatorInfo() + " Door closed.");
                        System.out.printf(this.getElevatorInfo() + " Moving from Floor " + this.getActualFloor());
                        for (; i != this.getActualFloor();) {
                            incrementFloor();
                        }
                        fL[i] = false; // if elevator has reached selected floor
                        this.setFloorList(fL); // set selection to false and update fL
                        System.out.println(" to Floor " + this.getActualFloor());
                        this.setDoorOpen(true);
                        System.out.println(this.getElevatorInfo() + " Door opened.");
                    }// else
                }// else
            }// if
        }// for
    }// move

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
