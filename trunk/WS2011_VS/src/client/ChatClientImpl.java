package client;

import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.Registry;

import server.MessageServerIF;

public class ChatClientImpl {

	public static final String SERVER_NAME = "ChatServer";
	public static final String ID = "test";
    /**
	 * @uml.property  name="server_port"
	 */
    private int server_port; //= Registry.REGISTRY_PORT;
	/**
	 * @uml.property  name="server_ip"
	 */
	private String server_ip;// = "localhost";
    /**
	 * @uml.property  name="server"
	 * @uml.associationEnd  multiplicity="(1 1)"
	 */
    private MessageServerIF server;


	public ChatClientImpl() {
        try {
        	setServer_port(Registry.REGISTRY_PORT);
        	setServer_ip("localhost");
            String url = "//" + server_ip + ":" + server_port + "/" + SERVER_NAME;
            server = (MessageServerIF) Naming.lookup(url);
            System.out.println("Found server: " + url);
        } catch (Exception e) {
        	e.printStackTrace();
        }
	}
	
	public void sendMSG(String msg) throws RemoteException {
		server.dropMessage(ID, msg);
	}
	
    public String receiveMSG() throws RemoteException {
    	return server.getMessage(ID);
    }

	/**
	 * @return
	 * @uml.property  name="server_port"
	 */
	public int getServer_port() {
		return server_port;
	}

	/**
	 * @param server_port
	 * @uml.property  name="server_port"
	 */
	public void setServer_port(int server_port) {
		this.server_port = server_port;
	}

	/**
	 * @return
	 * @uml.property  name="server_ip"
	 */
	public String getServer_ip() {
		return server_ip;
	}

	/**
	 * @param server_ip
	 * @uml.property  name="server_ip"
	 */
	public void setServer_ip(String server_ip) {
		this.server_ip = server_ip;
	}

	/**
	 * @uml.property  name="chatClient"
	 * @uml.associationEnd  inverse="chatClientImpl:client.ChatClient"
	 */
	private ChatClient chatClient;


	/**
	 * Getter of the property <tt>chatClient</tt>
	 * @return  Returns the chatClient.
	 * @uml.property  name="chatClient"
	 */
	public ChatClient getChatClient() {
		return chatClient;
	}

	/**
	 * Setter of the property <tt>chatClient</tt>
	 * @param chatClient  The chatClient to set.
	 * @uml.property  name="chatClient"
	 */
	public void setChatClient(ChatClient chatClient) {
		this.chatClient = chatClient;
	}
	

}
