package a06.BasicTextElevator;

public class TestMain {

    /**
     * @param args
     */
    public static void main(String[] args) {
        ElevatorModel el = new ElevatorModel("Elevator 1");
        ElevatorModel el2 = new ElevatorModel("Elevator 2");
        
        System.out.println("FloorList Entries:");
        for (boolean  f : el.getFloorList()) {
            
            System.out.println(f);
        }
        System.out.println(el.getActualFloor());
        System.out.println("#####START#######");
        el.callElevator(3);
        System.out.println("##################");
        el2.callElevator(2);
        System.out.println("##################");
        el.callElevator(1);
        System.out.println("##################");
        el2.callElevator(1);
        System.out.println("##################");
        el.callElevator(4);
        System.out.println("##################");
        el2.callElevator(4);
        System.out.println("##################");
        el.callElevator(2);
        System.out.println("##################");
        el2.callElevator(0);
        System.out.println("##################");
        el.callElevator(5);
        System.out.println("##################");
        el2.callElevator(5);
        System.out.println("####END##########");
    }
    

}
