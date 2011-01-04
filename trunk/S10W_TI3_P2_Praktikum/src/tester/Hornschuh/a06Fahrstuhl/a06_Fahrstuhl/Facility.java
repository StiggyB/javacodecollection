package tester.Hornschuh.a06Fahrstuhl.a06_Fahrstuhl;

/**
 * @author Jonas Hornschuh, Behzad Mahmoudi
 *
 */

import java.awt.Color;
import java.awt.Container;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSplitPane;

public class Facility extends JFrame implements ActionListener {

    // _________________________________________________________________________
    // Declarations
    
    private static final long serialVersionUID = 1L;
    private JPanel floorGUI;            // panel for floor representation
    private JPanel elevGUI;             // panel for elevator representation
    private JLabel[][] elevIcons;       // matrix with elevator images
    private JButton[] buttons;          // buttons for elevator call
    private JSplitPane sp;              // left side floor, right side elevators
    private Controller controller;      // controller for the elevators
    private ImageIcon iconOpened = new ImageIcon("src/a06/elevator_opened.gif");
    private ImageIcon iconClosed = new ImageIcon("src/a06/elevator_closed.gif");
    private ImageIcon iconNo = new ImageIcon("src/a06/elevator_no.gif");

    
    // _________________________________________________________________________
    // Constructors
    
    public Facility( Controller controller ) {
        super("Fahrstuhlsimulation");
        this.controller = controller;
        createFrame();
    }

    // _________________________________________________________________________
    // Methods
    
    private void createFrame() {
        createButtons();
        createIconGrid();
        sp = new JSplitPane();
        
        Container cp = getContentPane();
        cp.add(sp);
        sp.setLeftComponent(floorGUI);
        sp.setRightComponent( elevGUI );
        
        this.pack();
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
        this.setResizable(false);
        this.setVisible(true);
    }  
    
    private void createButtons() {
        floorGUI = new JPanel();
        floorGUI.setLayout( new GridLayout(Constants.FLOORCOUNT, 1) );
        buttons = new JButton[ Constants.FLOORCOUNT];
        for( int i=Constants.FLOORCOUNT-1; i>=0; i-- ) {
            buttons[i] = new JButton("Stockwerk " + i);
            buttons[i].setActionCommand( Integer.toString(i) );
            buttons[i].addActionListener(this);
            floorGUI.add( buttons[i] );
        }
    }
    
    // representation of the elevators and their positions
    private void createIconGrid() {
        elevGUI = new JPanel();
        elevGUI.setLayout( new GridLayout(Constants.FLOORCOUNT, Constants.ELEVATORCOUNT) );
        elevIcons = new JLabel[Constants.FLOORCOUNT][Constants.ELEVATORCOUNT];
        for( int i=Constants.FLOORCOUNT-1; i>=0; i-- ) {
            for( int j=0; j<Constants.ELEVATORCOUNT; j++ ) {
                elevIcons[i][j] = new JLabel( iconNo );
                elevIcons[i][j].setBorder(BorderFactory.createLineBorder(Color.WHITE));
                
                // all elevators are placed in the first floor
                if( i == 0 ) {
                    elevIcons[i][j] = new JLabel( iconClosed );
                }
                
                elevGUI.add(elevIcons[i][j]);
            }
        }
    }
    
    
    // elevator with opened doors at this position
    public synchronized void setIconToOpened( int row, int col ) {
        elevIcons[row][col].setIcon( iconOpened );
    }
    
    // elevator with closed doors at this position
    public synchronized void setIconToClosed( int row, int col ) {
        elevIcons[row][col].setIcon( iconClosed );
    }
    
    // no elevator at this position
    public synchronized void setIconToNo( int row, int col ) {
        elevIcons[row][col].setIcon( iconNo );
    }
    
    
    /**
     * listen for elevator calls and transfer them to the controller
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        int target = Integer.parseInt( e.getActionCommand() );
        for( int i=0; i<Constants.FLOORCOUNT; i++ ) {
            if( i == target ) {
                // set target in Controller
                System.out.println("Stockwerk " + i + " ruft Fahrstuhl");
                controller.addTarget( target );
            }
        }
    }
}
