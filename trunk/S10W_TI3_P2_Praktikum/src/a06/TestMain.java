package a06;

public class TestMain {

    /**
     * @param args
     */
    public static void main(String[] args) {
        ElevatorControl eC = new ElevatorControl();
        ShowInFrame.show("Elevator GUI", eC.getView());
    }
}
