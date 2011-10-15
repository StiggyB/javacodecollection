package client;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.Registry;
import java.util.PriorityQueue;
import java.util.Queue;

import server.MessageServerIF;

//Client
public class ChatClientImpl {

	public static final String SERVER_NAME = "MessageServer";
	public static final String NO_MORE_MSG = "java.rmi.RemoteException: no more messages";
	public static final int MAX_RECONNECTIONS = 10; //--

	public 	String ID;
	private String server_ip;	// = "localhost";
	private int server_port; 	//= Registry.REGISTRY_PORT;
    private MessageServerIF server;
    private Queue<String> msgList;
    private String url;
    private long s; 


	public ChatClientImpl(String ID, long s) {
		this.server_ip = "localhost";
        this.server_port = Registry.REGISTRY_PORT;
        this.msgList = new PriorityQueue<String>();
        this.ID = ID;
        this.s = s;
    	try {
			bind();
		} catch (MalformedURLException e) {
			e.printStackTrace();
		} catch (RemoteException e) {
			e.printStackTrace();
		} catch (NotBoundException e) {
			e.printStackTrace();
		}
	}
	
	public int getServer_port() {
		return server_port;
	}

	public void setServer_port(int server_port) {
		this.server_port = server_port;
	}

	public String getServer_ip() {
		return server_ip;
	}

	public void setServer_ip(String server_ip) {
		this.server_ip = server_ip;
	}
	
	private void bind() throws MalformedURLException, RemoteException, NotBoundException {
    	url = "//" + server_ip + ":" + server_port + "/" + SERVER_NAME;
		server = (MessageServerIF) Naming.lookup(url);
		System.out.println("Found server: " + url);	
	}

	/**
	 * This method implements a <i>at least once</i>
	 * error handling
	 * 
	 * @param msg
	 */
	public void sendMSG(String msg) {
		msgList.add(msg);
		try {
			server.dropMessage(ID, msg);
		} catch (RemoteException e) {
			System.err.print("Server not available.");
			//Check the connection to the server!
			if(checkServerTimeout(System.currentTimeMillis())) {
				sendMSG(msgList.poll());
			}
			e.printStackTrace();
		}
		msgList.clear();
	}
	
    /**
     * This method implements a <i>maybe</i>
     * error handling
     * 
     * @return
     */
    public String receiveMSG() {
    	try {
			return server.getMessage(ID);
		} catch (RemoteException e) {
			if (e.getCause().toString().equals(NO_MORE_MSG)) {
				return e.getCause().toString();
			} else {
				System.err.print("Server not available.");
				e.printStackTrace();
			}
		}
		return null;
    }
    
    private boolean checkServerTimeout(long timestamp) {
    	boolean success = false;
    	while(Math.abs(timestamp - System.currentTimeMillis()) < s) {
			try {
				bind();
				success = true;
			} catch (MalformedURLException e) {
				e.printStackTrace();
			} catch (RemoteException e) {
				e.printStackTrace();
			} catch (NotBoundException e) {
				success = false;
				e.printStackTrace();
			}
    	}
    	return success;
    }
}
