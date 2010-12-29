package a06;

public class TestMain {

    /**
     * @param args
     */
    public static void main(String[] args) {
        ElevatorControl eC = new ElevatorControl();
        ShowInFrame.show("Elevator GUI", eC.getView());
//        ElevatorView.main(args);
        
//        ElevatorModel el = new ElevatorModel("Elevator 1");
//        ElevatorModel el2 = new ElevatorModel("Elevator 2");
//        //Start threads
//        el.start();
//        el2.start();
//        
//        System.out.println("FloorList Entries:");
//        for (boolean  f : el.getFloorList()) {
//            
//            System.out.println(f);
//        }
//        System.out.println(el.getActualFloor());
//        
//        
//        el.callElevator(3);
//        el2.callElevator(2);
//        el.callElevator(1);
//        el2.callElevator(1);
//        el.callElevator(4);
//        el2.callElevator(4);
//        el.callElevator(2);
//        el2.callElevator(0);
//        el.callElevator(5);
//        el2.callElevator(5);
    }
    

}
