package client;
import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JEditorPane;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JSplitPane;
import javax.swing.JTextArea;
import javax.swing.ListModel;
import javax.swing.SwingUtilities;
import javax.swing.WindowConstants;


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
public class GUI_Client extends javax.swing.JFrame {

	{
		//Set Look & Feel
		try {
			javax.swing.UIManager.setLookAndFeel(javax.swing.UIManager.getSystemLookAndFeelClassName());
		} catch(Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private JSplitPane jSplitPane1;
	private JSplitPane jSplitPane2;
	private JList jList1;
	private JButton sendButton;
	private JTextArea jTextArea1;
	private JEditorPane jEditor;

	/**
	* Auto-generated main method to display this JFrame
	*/
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				GUI_Client inst = new GUI_Client();
				inst.setLocationRelativeTo(null);
				inst.setVisible(true);
			}
		});
	}
	
	public GUI_Client() {
		super();
		initGUI();
	}
	
	private void initGUI() {
		try {
			BorderLayout thisLayout = new BorderLayout();
			setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
			getContentPane().setLayout(thisLayout);
			{
				jSplitPane1 = new JSplitPane();
				getContentPane().add(jSplitPane1, BorderLayout.CENTER);
				jSplitPane2 = new JSplitPane();
				getContentPane().add(jSplitPane2, BorderLayout.SOUTH);
				{
					ListModel jList1Model = 
						new DefaultComboBoxModel(
								new String[] { "Item One", "Item Two" });
					jList1 = new JList();
					jSplitPane1.add(jList1, JSplitPane.RIGHT);
					jList1.setModel(jList1Model);
				}
				{
					jTextArea1 = new JTextArea();
					jSplitPane1.add(jTextArea1, JSplitPane.LEFT);
					jTextArea1.setText("jTextArea1");
				}
				{
					jEditor = new JEditorPane();
					jSplitPane2.add(jEditor, JSplitPane.RIGHT);
				}
				{
					sendButton = new JButton();
					jSplitPane2.add(sendButton, JSplitPane.LEFT);
					sendButton.setText("Send");
					sendButton.addActionListener(
					/**
					 * Anonyme Klasse, die beim JButton calculate angemeldet ist mit lokaler
					 * Exceptionbehandlung - letzte Moeglichkeit.
					 * 
					 * @author Administrator
					 * 
					 */
					new ActionListener() {

						@Override
						public void actionPerformed(ActionEvent e) {
							try {
								/* dropMessage() to server */
							} catch (NumberFormatException ex) {
								ex.printStackTrace();
								JOptionPane
										.showMessageDialog(
												null,
												"Error: Minimum one entry is false or not complete.",
												"Entry Error", JOptionPane.WARNING_MESSAGE);
							}
						}
					});
				}
			}
			pack();
			setSize(400, 300);
		} catch (Exception e) {
		    //add your error handling code here
			e.printStackTrace();
		}
	}

}
