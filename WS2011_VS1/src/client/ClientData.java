package client;

import java.util.ArrayList;
import java.util.List;

import server.Message;

public class ClientData {

	private String clientID;
	private long rememTime;
	private List<Message> clientMsgs;
	
	public ClientData(String clientID, long rTime) {
		this.clientID = clientID;
		this.rememTime = rTime;
		this.clientMsgs = new ArrayList<Message>();
	}

	public long getRememTime() {
		return rememTime;
	}
	
	public void setRememTime(long rememTime) {
		this.rememTime = rememTime;
	}

	public List<Message> getClientMsgs() {
		return clientMsgs;
	}

	public String getClientID() {
		return clientID;
	}
	
	public void addMsg(Message msg) {
		clientMsgs.add(msg);
	}
	
	public boolean containsMsg(Message msg) {
		return clientMsgs.isEmpty() ? false : clientMsgs.contains(msg);
	}
	
}
