package client;


public class Receiver implements Runnable {

	private ChatClientImpl client;
	private ClientGUI gui;
	
    public Receiver(ChatClientImpl client, ClientGUI gui) {
        this.client = client;
        this.gui = gui;
    }
	
	@Override
	public void run() {
		String msg = null;
		for (;;) {
			System.out.println("run");
			msg = client.receiveMSG();
			if(msg == null || msg.equals(ChatClientImpl.NO_MORE_MSG)) {
				return;
			} else {
				gui.appendRcvAreaText(msg);
			}
		}		
	}
}
