package a07_old;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

import javax.swing.WindowConstants;
import javax.swing.SwingUtilities;

/**
 * This code was edited or generated using CloudGarden's Jigloo SWT/Swing GUI Builder, which is free for non-commercial
 * use. If Jigloo is being used commercially (ie, by a corporation, company or business for any purpose whatever) then
 * you should purchase a license for each developer using Jigloo. Please visit www.cloudgarden.com for details. Use of
 * Jigloo implies acceptance of these licensing terms. A COMMERCIAL LICENSE HAS NOT BEEN PURCHASED FOR THIS MACHINE, SO
 * JIGLOO OR THIS CODE CANNOT BE USED LEGALLY FOR ANY CORPORATE OR COMMERCIAL PURPOSE.
 */
public class JFrame extends javax.swing.JFrame {
    /**
     * 
     */
    private static final long serialVersionUID = 1L;
    private JPanel screenPanel;
    private JPanel controlPanel;
    private JPanel elevatorControlPanel1;
    private JPanel elevatorControlPanel2;
    private JLabel elevatorShaft2;
    private JLabel elevatorShaft1;
    private JLabel buildingLabel;
    private ElevatorLabel ele1 = new ElevatorLabel(1);
    private ElevatorLabel ele2 = new ElevatorLabel(2);
    private JButton[] elevatorControlButtons1 = new JButton[4];
    private JButton[] elevatorControlButtons2 = new JButton[4];

    /**
     * Auto-generated main method to display this JFrame
     */
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                JFrame inst = new JFrame();
                inst.setLocationRelativeTo(null);
                inst.setVisible(true);
            }
        });
    }

    public JFrame() {
        super();
        initGUI();
    }

    private void initGUI() {
        try {
            this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
            this.setIgnoreRepaint(true);
            this.setResizable(false);
            this.setName("mainFrame");
            this.setUndecorated(true);
            this.setMinimumSize(new java.awt.Dimension(1024, 768));
            getContentPane().setBackground(new java.awt.Color(0, 0, 0));
            {
                controlPanel = new JPanel();
                BorderLayout controlPanelLayout = new BorderLayout();
                controlPanel.setLayout(controlPanelLayout);
                getContentPane().add(controlPanel, BorderLayout.WEST);
                controlPanel.setSize(198, 735);
                controlPanel.setPreferredSize(new java.awt.Dimension(198, 735));
                controlPanel.setToolTipText("Elevator Control Area");
                controlPanel.setMinimumSize(new java.awt.Dimension(198, 735));
                controlPanel.setBackground(new java.awt.Color(0, 0, 0));
                {
                    elevatorControlPanel1 = new JPanel();
                    controlPanel.add(elevatorControlPanel1, BorderLayout.NORTH);
                    elevatorControlPanel1.setSize(198, 367);
                    elevatorControlPanel1.setPreferredSize(new java.awt.Dimension(198, 367));

                    for (int i = 0; i < 4; i++) {
                        switch (i){
                            case 0 : elevatorControlButtons1[i].setText(Floors.GROUNDFLOOR.toString()); break;
                            case 1 : elevatorControlButtons1[i].setText(Floors.FIRSTFLOOR.toString()); break;
                            case 2 : elevatorControlButtons1[i].setText(Floors.SECONDFLOOR.toString()); break;
                            case 3 : elevatorControlButtons1[i].setText(Floors.THIRDFLOOR.toString()); break;
                        }//switch
                        elevatorControlButtons1[i].addActionListener(new ElevatorControl.ElevatorButtonControl()); 
                    }//for

                }
                {
                    elevatorControlPanel2 = new JPanel();
                    controlPanel.add(elevatorControlPanel2, BorderLayout.SOUTH);
                    elevatorControlPanel2.setPreferredSize(new java.awt.Dimension(198, 368));
                }
            }
            {
                screenPanel = new JPanel();
                getContentPane().add(screenPanel, BorderLayout.EAST);
                screenPanel.setLayout(null);
                screenPanel.setSize(824, 723);
                screenPanel.setPreferredSize(new java.awt.Dimension(824, 723));
                screenPanel.setAlignmentY(0.0f);
                screenPanel.setAlignmentX(0.0f);
                {
                    elevatorShaft1 = new JLabel();
                    screenPanel.add(elevatorShaft1);
                    elevatorShaft1.setIcon(ele1.getCurrentIcon());
                    elevatorShaft1.setBounds(ele1.getBounds());
                    elevatorShaft1.setPreferredSize(ele1.getPreferredSize());
                    elevatorShaft1.setSize(ele1.getSize());
                }
                {
                    elevatorShaft2 = new JLabel();
                    screenPanel.add(elevatorShaft2);
                    elevatorShaft2.setIcon(ele2.getCurrentIcon());
                    elevatorShaft2.setBounds(ele2.getBounds());
                    elevatorShaft2.setPreferredSize(ele2.getPreferredSize());
                    elevatorShaft2.setSize(ele2.getSize());
                }
                {
                    buildingLabel = new JLabel();
                    screenPanel.add(buildingLabel);
                    buildingLabel.setIcon(new ImageIcon(getClass().getClassLoader().getResource(
                            "a07/icons/building.jpg")));
                    buildingLabel.setAlignmentY(0.0f);
                    buildingLabel.setBounds(0, 0, 824, 768);
                }
            }
            pack();
            this.setSize(1024, 768);
        }catch (Exception e) {
            e.printStackTrace();
        }
    }

    private class MyECB1ActionListener implements ActionListener { // Innere/Element
        // Klasse
        public void actionPerformed(ActionEvent ev) {
            for(int i = 0; i<elevatorControlButtons1.length; i++){
                if(ev.getSource().equals(elevatorControlButtons1[i])){
                    ele1.selectFloor(Floors.valueOf(elevatorControlButtons1[i].getText()));
                    ElevatorThread et = new ElevatorThread(ele1);
            }
//                case elevatorControlButtons1[0] : ElevatorThread et = new ElevatorThread(ele1);
//                                               Thread t = new Thread(et);
//                                                      t.start();
            }
        }// actionPerformed
    }// MyButtonActionListener

    public JLabel getElevatorShaft2() {
        return elevatorShaft2;
    }

    public void setElevatorShaft2(JLabel elevatorShaft2) {
        this.elevatorShaft2 = elevatorShaft2;
    }

    public JLabel getElevatorShaft1() {
        return elevatorShaft1;
    }

    public void setElevatorShaft1(JLabel elevatorShaft1) {
        this.elevatorShaft1 = elevatorShaft1;
    }

}
