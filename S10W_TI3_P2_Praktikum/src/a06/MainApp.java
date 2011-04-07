package a06;

/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 06<br>
 * 
 * Version: V1<br>
 * Aenderungen:
 * 
 * Quellen:
 * 
 * <br><br><b>Description:</b> <br>This class starts the application.<br>
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br><br>
 * 
 */

public class MainApp {
    
    public static void main(String[] args) {
        ElevatorControl eC = new ElevatorControl();
        ShowInFrame.show("Elevator GUI", eC.getView());
    }//main
}//MainApp
