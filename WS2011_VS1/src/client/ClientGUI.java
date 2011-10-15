package client;

import java.awt.BorderLayout;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JToggleButton;

import org.jdesktop.application.SingleFrameApplication;


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
/**
 * 
 */
public class ClientGUI extends SingleFrameApplication {
    private JButton receiveBtn;
    private JToggleButton receiveAllTimeTBtn;
    private JLabel fifoInfoLabel;
    private JTextField setFifoTxtFld;
    private JButton setFifoBtn;
	private JButton clearBtn;
    private JButton receiveAllBtn;
    private JTextArea receiveArea;
    private JButton sendBtn;
    private JTextField sendField;
    private JPanel topPanel;
    private JPanel contentPanel;

    @Override
    protected void startup() {
    	{
	    	getMainFrame().setSize(616, 257);
    	}
        {
            topPanel = new JPanel();
            BorderLayout panelLayout = new BorderLayout();
            topPanel.setLayout(panelLayout);
            topPanel.setPreferredSize(new java.awt.Dimension(500, 300));
            {
            	contentPanel = new JPanel();
            	topPanel.add(contentPanel, BorderLayout.CENTER);
            	contentPanel.setLayout(null);
            	contentPanel.setPreferredSize(new java.awt.Dimension(591, 223));
            	{
            		sendField = new JTextField();
            		contentPanel.add(sendField);
            		sendField.setName("SendField");
            		sendField.setBounds(126, 182, 465, 31);
            	}
            	{
            		sendBtn = new JButton("Send");
            		contentPanel.add(sendBtn);
            		sendBtn.setBounds(0, 186, 103, 23);
            		sendBtn.setName("SendBtn");
            	}
            	{
            		receiveArea = new JTextArea();
//            		receiveArea.setLineWrap(true);
//            		receiveArea.setWrapStyleWord(true);
            		contentPanel.add(receiveArea);
            		receiveArea.setBounds(126, 3, 465, 173);
            		receiveArea.setName("receiveArea");
            	}
            	{
            		receiveBtn = new JButton("Receive");
            		contentPanel.add(receiveBtn);
            		receiveBtn.setBounds(0, 10, 103, 23);
            		receiveBtn.setName("receiveBtn");
            	}
            	{
            		receiveAllBtn = new JButton("Receive All");
            		contentPanel.add(receiveAllBtn);
            		receiveAllBtn.setBounds(0, 33, 103, 23);
            		receiveAllBtn.setName("receiveAllBtn");
            	}
            	{
            		clearBtn = new JButton("Clear");
            		contentPanel.add(clearBtn);
            		clearBtn.setBounds(0, 77, 103, 23);
            		clearBtn.setName("clearBtn");
            	}
            	{
            		receiveAllTimeTBtn = new JToggleButton("Receive All Time");
            		contentPanel.add(receiveAllTimeTBtn);
            		receiveAllTimeTBtn.setBounds(0, 56, 103, 21);
            		receiveAllTimeTBtn.setName("jToggleButton");
            	}
            	{
            		setFifoBtn = new JButton("Submit");
            		contentPanel.add(setFifoBtn);
            		setFifoBtn.setBounds(0, 150, 103, 21);
            		setFifoBtn.setName("setFifoBtn");
            	}
            	{
            		setFifoTxtFld = new JTextField("enter en sek...");
            		contentPanel.add(setFifoTxtFld);
            		setFifoTxtFld.setBounds(0, 123, 103, 21);
            		setFifoTxtFld.setName("setFifoTxtFld");
            	}
            	{
            		fifoInfoLabel = new JLabel("Duration of retries");
            		contentPanel.add(fifoInfoLabel);
            		fifoInfoLabel.setBounds(0, 107, 119, 14);
            		fifoInfoLabel.setName("fifoInfoLabel");
            	}
            }
        }
        show(topPanel);
    }

    public JToggleButton getjToggleButton() {
		return receiveAllTimeTBtn;
	}
    
    public String getSendFieldText() {
        return sendField.getText();
    }
    
    public void appendRcvAreaText(String txt) {
        receiveArea.append(txt + "\n");
    }
    
    public void clearRcvText() {
        receiveArea.setText("");
    }
    
    public void clearSendText() {
        sendField.setText("");
    }
    
    // Action Listeners
    public void setSendBtnListener(ActionListener l) {
        sendBtn.addActionListener(l);
    }
    
    public void setRcvBtnListener(ActionListener l) {
        receiveBtn.addActionListener(l);
    }
    
    public void setRcvAllBtnListener(ActionListener l) {
        receiveAllBtn.addActionListener(l);
    }

	public void setClearBtnListener(ActionListener l) {
		clearBtn.addActionListener(l);
	}
	
	public void setjToggleButtonListener(ActionListener l) {
		receiveAllTimeTBtn.addActionListener(l);
	}
}
