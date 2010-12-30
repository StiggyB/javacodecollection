package a06;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JOptionPane;
/**
 * 
 * http://blog.bigbasti.com/tutorial-model-view-controller-mvc-struktur-in-java-projekten-nutzen/
 * 
 */
public class ElevatorControl {
    
    private ElevatorModel model;
    private ElevatorView view;
    
    public ElevatorView getView() {
        return view;
    }

    public ElevatorControl(){
        this.model = new ElevatorModel("Elevator 1");
        this.view = new ElevatorView();
        addListener();
        
    }
    
    public ActionListener getCallButtonActionListener(){
        ActionListener aL = new CallButtonActionListener();
        return aL;
    }

    private void addListener(){
        view.setCallButtonActionListener(new CallButtonActionListener());
        view.setKeepDoorsOpenActionListener(new KeepDoorsOpenActionListener());
        view.registerButtonActionListeners();
        
        
    }
    private class CallButtonActionListener implements ActionListener { // Innere/Element
        // Klasse
        public void actionPerformed(ActionEvent ev) {
            JButton source = (JButton) ev.getSource();
            if (source.getText().contains("Ground floor")) {
                    JOptionPane.showMessageDialog(null, "Called Ground floor",
                            "Caller Message", JOptionPane.WARNING_MESSAGE);
                    
            }
            if(source.getText().contains("First  floor")){
                JOptionPane.showMessageDialog(null, "Called First floor",
                        "Caller Message", JOptionPane.WARNING_MESSAGE);
                
            }
            if(source.getText().contains("Second floor")){
                JOptionPane.showMessageDialog(null, "Called Second floor",
                        "Caller Message", JOptionPane.WARNING_MESSAGE);
            }
            if(source.getText().contains("Thrid  floor")){
                JOptionPane.showMessageDialog(null, "Called Third floor",
                        "Caller Message", JOptionPane.WARNING_MESSAGE);
            }
            if(source.getText().contains("Fourth floor")){
                JOptionPane.showMessageDialog(null, "Called Fourth floor",
                        "Caller Message", JOptionPane.WARNING_MESSAGE);
            }
        }// actionPerformed
    }// CallButtonActionListener
    
    private class KeepDoorsOpenActionListener implements ActionListener { // Innere/Element
        // Klasse
        public void actionPerformed(ActionEvent ev) {
            JButton source = (JButton) ev.getSource();
            
            if (source.getName().contains("< >") && source.getName().contains(" Elevator 1")){
            JOptionPane.showMessageDialog(null, "Keeping Door Open on Elevator 1",
                    "Caller Message", JOptionPane.WARNING_MESSAGE);
            }
            if (source.getName().contains("< >") && source.getName().contains(" Elevator 2")){
                JOptionPane.showMessageDialog(null, "Keeping Door Open on Elevator 2",
                        "Caller Message", JOptionPane.WARNING_MESSAGE);
                }
        }// actionPerformed
    }// KeepDoorsOpenActionListener

    /**
     * @param args
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub

    }

}
