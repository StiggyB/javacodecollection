package a07_old;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

public class ElevatorControl {
    static class ElevatorButtonControl implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            try {
                switch (e.getSource()){
                    case : 
                }
            }catch (NumberFormatException ex) {
                ex.printStackTrace();
                JOptionPane.showMessageDialog(null, "Error: Minimum one entry is false or not complete.",
                        "Entry Error", JOptionPane.WARNING_MESSAGE);
            }
        }
    }
}
