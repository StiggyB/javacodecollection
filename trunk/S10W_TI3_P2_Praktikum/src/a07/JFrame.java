package a07;
import java.awt.BorderLayout;
import java.awt.FlowLayout;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;

import javax.swing.WindowConstants;
import javax.swing.SwingUtilities;


/**
* This code was edited or generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a corporation,
* company or business for any purpose whatever) then you
* should purchase a license for each developer using Jigloo.
* Please visit www.cloudgarden.com for details.
* Use of Jigloo implies acceptance of these licensing terms.
* A COMMERCIAL LICENSE HAS NOT BEEN PURCHASED FOR
* THIS MACHINE, SO JIGLOO OR THIS CODE CANNOT BE USED
* LEGALLY FOR ANY CORPORATE OR COMMERCIAL PURPOSE.
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
            getContentPane().setBackground(new java.awt.Color(0,0,0));
            {
                controlPanel = new JPanel();
                BorderLayout controlPanelLayout = new BorderLayout();
                controlPanel.setLayout(controlPanelLayout);
                getContentPane().add(controlPanel, BorderLayout.WEST);
                controlPanel.setSize(198, 735);
                controlPanel.setPreferredSize(new java.awt.Dimension(198, 735));
                controlPanel.setToolTipText("Elevator Control Area");
                controlPanel.setMinimumSize(new java.awt.Dimension(198, 735));
                controlPanel.setBackground(new java.awt.Color(0,0,0));
                {
                    elevatorControlPanel1 = new JPanel();
                    controlPanel.add(elevatorControlPanel1, BorderLayout.NORTH);
                    elevatorControlPanel1.setSize(198, 367);
                    elevatorControlPanel1.setPreferredSize(new java.awt.Dimension(198, 367));
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
                    elevatorShaft1.setIcon(new ImageIcon(getClass().getClassLoader().getResource("a07/icons/elevatorOpen.jpg")));
                    elevatorShaft1.setBounds(123, 577, 103, 189);
                }
                {
                    elevatorShaft2 = new JLabel();
                    screenPanel.add(elevatorShaft2);
                    elevatorShaft2.setIcon(new ImageIcon(getClass().getClassLoader().getResource("a07/icons/elevatorOpen.jpg")));
                    elevatorShaft2.setBounds(599, 576, 103, 189);
                }
                {
                    buildingLabel = new JLabel();
                    screenPanel.add(buildingLabel);
                    buildingLabel.setIcon(new ImageIcon(getClass().getClassLoader().getResource("a07/icons/building.jpg")));
                    buildingLabel.setAlignmentY(0.0f);
                    buildingLabel.setBounds(0, 0, 824, 768);
                }
            }
            pack();
            this.setSize(1024, 768);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

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
