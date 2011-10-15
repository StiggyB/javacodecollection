package client;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


// Client Controller
public class ClientGUIImpl {

	private ChatClientImpl client;
	private ClientGUI gui;
	private Thread rcvThread;
	
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
        gui.setjToggleButtonListener(new RcvAllTimeActionListener());
    }
    
    private class SendBtnActionListener implements ActionListener{
        public void actionPerformed(ActionEvent e) {
            client.sendMSG(gui.getSendFieldText());
            gui.clearSendText();
            System.out.println("send");
        }
    }
    
    private class RcvBtnActionListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String msg = client.receiveMSG();
            if (msg == null) {
                System.err.println("Message receive failed");
            } else if (!msg.equals(ChatClientImpl.NO_MORE_MSG)) {
                gui.appendRcvAreaText(msg);
            } else {
            	System.err.println(msg);
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
    
	private class RcvAllTimeActionListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			if (gui.getjToggleButton().getModel().isSelected()) {
				long ms = System.currentTimeMillis();
				rcvThread = new Thread(new Receiver(client, gui), "ClientController");
				rcvThread.start();
				ThreadController.printAllThreads(ThreadController.getAllThreads());
				for (int i = 0; i < 100; i++) { //While the for is running - gui is freeze
					System.out.println("for");
					if (rcvThread.isInterrupted()) {
						System.out.println("start");
						rcvThread.start();
					} else if(isTimeout(ms)) {
						ms = System.currentTimeMillis();
						try {
							rcvThread.join();	//does not work!
						} catch (InterruptedException e1) {
							e1.printStackTrace();
						} 
						continue;
					}
					if(!(gui.getjToggleButton().getModel().isSelected())) {
						try {
							rcvThread.join();
						} catch (InterruptedException e1) {
							e1.printStackTrace();
						}
						break;
					}
				}
			}
		}
	}
   
    private class ClearBtnActionListener implements ActionListener{
        public void actionPerformed(ActionEvent e) {
        	gui.clearRcvText();
        }
    }
    
    private boolean isTimeout(long ms) {
    	return (Math.abs(ms - System.currentTimeMillis()) > 500) ? true : false;
    }
}
