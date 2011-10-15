package server;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JTextField;
import javax.swing.JLabel;
import javax.swing.JTextArea;

public class ServerGUI {

	private JFrame frame;
	private JTextField textField;
	private JTextField textField_1;
	private JTextField textField_2;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					ServerGUI window = new ServerGUI();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public ServerGUI() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBounds(100, 100, 450, 300);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		textField = new JTextField();
		textField.setBounds(76, 11, 86, 20);
		frame.getContentPane().add(textField);
		textField.setColumns(10);
		
		textField_1 = new JTextField();
		textField_1.setBounds(76, 40, 86, 20);
		frame.getContentPane().add(textField_1);
		textField_1.setColumns(10);
		
		textField_2 = new JTextField();
		textField_2.setBounds(76, 70, 86, 20);
		frame.getContentPane().add(textField_2);
		textField_2.setColumns(10);
		
		JLabel lblServerName = new JLabel("Server Name");
		lblServerName.setBounds(10, 21, 78, 14);
		frame.getContentPane().add(lblServerName);
		
		JLabel lblServerPort = new JLabel("Server Port");
		lblServerPort.setBounds(10, 50, 67, 14);
		frame.getContentPane().add(lblServerPort);
		
		JLabel lblDeliveryQueueLength = new JLabel("Queue length");
		lblDeliveryQueueLength.setBounds(10, 75, 107, 14);
		frame.getContentPane().add(lblDeliveryQueueLength);
		
		JTextArea textArea = new JTextArea();
		textArea.setBounds(203, 39, 211, 216);
		frame.getContentPane().add(textArea);
		
		JLabel lblServerLog = new JLabel("Server Log");
		lblServerLog.setBounds(201, 11, 82, 14);
		frame.getContentPane().add(lblServerLog);
	}
}
