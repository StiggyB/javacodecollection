package client;

import java.util.HashMap;

public class ClientData {

	private String clientID;
	private HashMap<String, Long> msgs;
	private long rTime;
	
	public ClientData(String clientID, long rTime) {
		this.clientID = clientID;
		this.msgs = new HashMap<String, Long>();
		this.rTime = rTime;
	}

	public String getClientID() {
		return clientID;
	}

	public boolean hasPassed(String msg) {
		for (String m : msgs.keySet()) {
			if (m.equals(msg)) {
				if ((Math.abs(msgs.get(m) - System.currentTimeMillis())) > rTime) {
					return true;
				}
			}
		}
		return false;
	}
	
	public void addMsg(String msg) {
		msgs.put(msg, System.currentTimeMillis());
	}
	
	public boolean containsMsg(String msg) {
		return (msgs.containsKey(msg));
	}
	
	public boolean hasMessages() {
		return (!msgs.isEmpty());
	}
	
}
