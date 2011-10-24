package client;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

// Client Controller
public class ClientGUIImpl {

	private ChatClientImpl client;
	private ClientGUI gui;
	
    public ClientGUIImpl(ChatClientImpl client, ClientGUI gui) {
        this.client = client;
        this.gui = gui;
    }
    
    public void start() {
    	gui.startup();
        gui.setSendBtnListener(new SendBtnActionListener());
        gui.setRcvBtnListener(new RcvBtnActionListener());
        gui.setRcvAllBtnListener(new RcvAllBtnActionListener());
        gui.setClearBtnListener(new ClearBtnActionListener());
    }
    
    private class SendBtnActionListener implements ActionListener{
        public void actionPerformed(ActionEvent e) {
            client.sendMSG(gui.getSendFieldText());
            gui.clearSendText();
        }
    }
    
    private class RcvBtnActionListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String msg = client.receiveMSG();
            if (msg == null) {
                System.err.println("Message receive failed");
            } else if (!msg.equals(ChatClientImpl.NO_MORE_MSG)) {
                gui.appendRcvAreaText(msg);
            }
        }
    }
    
    private class RcvAllBtnActionListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String msg = client.receiveMSG();
            while (msg != null && !msg.equals(ChatClientImpl.NO_MORE_MSG)) {
                gui.appendRcvAreaText(msg);
                msg = client.receiveMSG();
            }
            if (msg == null) {
                System.err.println("Receiving message failed: check stack trace");
            }
        }
    }
    
    private class ClearBtnActionListener implements ActionListener{
        public void actionPerformed(ActionEvent e) {
        	gui.clearRcvText();
        }
    }
    
}
