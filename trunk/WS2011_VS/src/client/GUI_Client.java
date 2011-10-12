package client;

import java.awt.FlowLayout;
import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JTextPane;

public class GUI_Client extends JFrame{

	private static final long serialVersionUID = 5257248828637263369L;

	/**
	 * @uml.property  name="sendLabel"
	 * @uml.associationEnd  multiplicity="(1 1)"
	 */
	private JLabel sendLabel;
    /**
	 * @uml.property  name="sendField"
	 * @uml.associationEnd  multiplicity="(1 1)"
	 */
    private JTextField sendField;
    
	/**
	 * @uml.property  name="rcvLabel"
	 * @uml.associationEnd  multiplicity="(1 1)"
	 */
	private JLabel rcvLabel;
    /**
	 * @uml.property  name="rcvField"
	 * @uml.associationEnd  multiplicity="(1 1)"
	 */
    private JTextPane rcvField;
    
	public GUI_Client() {
//		setLayout(new GridLayout());
		
		//send
		sendLabel = new JLabel("Send");
		add(sendLabel);
		sendField = new JTextField(20);
		add(sendField);
		
		//rcv
		rcvLabel= new JLabel("Received");
		add(rcvLabel);
		rcvField = new JTextPane();
		add(rcvField);
		
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        setSize(400, 400);
        setVisible(true);
        setTitle("Chat");
	}

	public static void main(String[] args) {
		GUI_Client gui = new GUI_Client();
	}

}
