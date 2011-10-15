package client;

import java.util.concurrent.TimeUnit;


public class Receiver implements Runnable {

	private ChatClientImpl client;
	private ClientGUI gui;
	private boolean running;
	
    public Receiver(ChatClientImpl client, ClientGUI gui) {
        this.client = client;
        this.gui = gui;
        this.running = true;
    }
	
    public void setStopped(){
    	running = false;
    }
    
	@Override
	public void run() {
		String msg = null;
//	for (;;) {
//			System.out.println("run");
//			msg = client.receiveMSG();
//			if(msg == null || msg.equals(ChatClientImpl.NO_MORE_MSG)) {
//				return;
//			} else {
//				gui.appendRcvAreaText(msg);
//			}
//		}
		while(running) {
			boolean nmm = false;
			while (!nmm) {
				msg = client.receiveMSG();
				if (msg.equals(ChatClientImpl.NO_MORE_MSG)) {
					nmm = true;
				} else {
					gui.appendRcvAreaText(msg);
				}
			}
			try {
				TimeUnit.SECONDS.sleep(1);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
