package a06.withoutContainer;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;

/**
 * 
 * http://blog.bigbasti.com/tutorial-model-view-controller-mvc-struktur-in-java-projekten-nutzen/
 * 
 */
public class ElevatorControl extends Thread {

    private ElevatorModel elevator1;
    private ElevatorModel elevator2;
    private ElevatorView view;

    public ElevatorView getView() {
        return view;
    }

    //Constructor
    public ElevatorControl() {
        
        this.view = new ElevatorView();
        this.elevator1 = new ElevatorModel("Elevator 1", view);
        this.elevator2 = new ElevatorModel("Elevator 2", view);
        addListener();
        elevator1.start();
        elevator2.start();
    }//ElevatorControl

    public ActionListener getCallButtonActionListener() {
        ActionListener aL = new CallButtonActionListener();
        return aL;
    }//getCallButtonActionListener

    private void addListener() {
        view.setCallButtonActionListener(new CallButtonActionListener());
//        view.setKeepDoorsOpenActionListener(new KeepDoorsOpenActionListener());
        view.registerButtonActionListener();

    }//addListener

    private class CallButtonActionListener implements ActionListener { // Innere/Element
        // Klasse
        public void actionPerformed(ActionEvent ev) {
            JButton source = (JButton) ev.getSource();
            if (source.getText().contains("Ground floor")) {
//                JOptionPane.showMessageDialog(null, "Called Ground floor", "Caller Message",
//                        JOptionPane.WARNING_MESSAGE);
                if (source.getName().contains("Elevator 1")){                    
                    elevator1.callElevator(0);
                }else if (source.getName().contains("Elevator 2")){
                    elevator2.callElevator(0);
                }//else
            }//if
            
            if (source.getText().contains("First  floor")) {
//                JOptionPane
//                        .showMessageDialog(null, "Called First floor", "Caller Message", JOptionPane.WARNING_MESSAGE);
                if (source.getName().contains("Elevator 1")){                    
                    elevator1.callElevator(1);
                }else if (source.getName().contains("Elevator 2")){
                    elevator2.callElevator(1);
                }//else
            }//if
            if (source.getText().contains("Second floor")) {
//                JOptionPane.showMessageDialog(null, "Called Second floor", "Caller Message",
//                        JOptionPane.WARNING_MESSAGE);
                if (source.getName().contains("Elevator 1")){                    
                    elevator1.callElevator(2);
                }else if (source.getName().contains("Elevator 2")){
                    elevator2.callElevator(2);
                }//else
            }
            if (source.getText().contains("Thrid  floor")) {
//                JOptionPane
//                        .showMessageDialog(null, "Called Third floor", "Caller Message", JOptionPane.WARNING_MESSAGE);
                if (source.getName().contains("Elevator 1")){                    
                    elevator1.callElevator(3);
                }else if (source.getName().contains("Elevator 2")){
                    elevator2.callElevator(3);
                }//else
            }
            if (source.getText().contains("Fourth floor")) {
//                JOptionPane.showMessageDialog(null, "Called Fourth floor", "Caller Message",
//                        JOptionPane.WARNING_MESSAGE);
                if (source.getName().contains("Elevator 1")){                    
                    elevator1.callElevator(4);
                }else if (source.getName().contains("Elevator 2")){
                    elevator2.callElevator(4);
                }//else
            }
        }// actionPerformed
    }// CallButtonActionListener

//    private class KeepDoorsOpenActionListener implements ActionListener { // Innere/Element
//        // Klasse
//        public void actionPerformed(ActionEvent ev) {
//            JButton source = (JButton) ev.getSource();
//
//            if (source.getName().contains("< >") && source.getName().contains(" Elevator 1")) {
//                JOptionPane.showMessageDialog(null, "Keeping Door Open on Elevator 1", "Caller Message",
//                        JOptionPane.WARNING_MESSAGE);
//                
//            }
//            if (source.getName().contains("< >") && source.getName().contains(" Elevator 2")) {
//                JOptionPane.showMessageDialog(null, "Keeping Door Open on Elevator 2", "Caller Message",
//                        JOptionPane.WARNING_MESSAGE);
//            }
//        }// actionPerformed
//    }// KeepDoorsOpenActionListener

    /**
     * @param args
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub

    }

}
