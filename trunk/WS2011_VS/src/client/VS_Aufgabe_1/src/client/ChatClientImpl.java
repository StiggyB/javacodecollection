package client;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.Registry;

import server.MessageServerIF;

//Client
public class ChatClientImpl {

	public static final String SERVER_NAME = "MessageServer";
	public String ID;
	public static final String NO_MORE_MSG = "java.rmi.RemoteException: no more messages";

	private String server_ip;// = "localhost";
	private int server_port; //= Registry.REGISTRY_PORT;
    private MessageServerIF server;


	public ChatClientImpl(String ID) {
        server_ip = "localhost";
        server_port = Registry.REGISTRY_PORT;
        this.ID = ID;
    	bind();
	}
	
	private void bind() {
        try {
        	String url = "//" + server_ip + ":" + server_port + "/" + SERVER_NAME;
			server = (MessageServerIF) Naming.lookup(url);
			System.out.println("Found server: " + url);
		} catch (MalformedURLException e) {
			e.printStackTrace();
		} catch (RemoteException e) {
			e.printStackTrace();
		} catch (NotBoundException e) {
			e.printStackTrace();
		}		
	}

	public void sendMSG(String msg) {
		try {
			server.dropMessage(ID, msg);
		} catch (RemoteException e) {
			e.printStackTrace();
		}
	}
	
    public String receiveMSG() {
    	try {
			return server.getMessage(ID);
		} catch (RemoteException e) {
			if (e.getCause().toString().equals(NO_MORE_MSG)) {
				return e.getCause().toString();
			} else {
				e.printStackTrace();
			}
		}
		return null;
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

}
