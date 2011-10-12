package server;

import java.net.InetAddress;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.LinkedList;
import java.util.Queue;

public class ChatServerImpl extends UnicastRemoteObject implements MessageServerIF {
	
	private static final long serialVersionUID = -4917373673314532190L;
    public static final int PORT = Registry.REGISTRY_PORT;
    public static final int nom = 5;
    
	
	/**
	 * @uml.property  name="msgs"
	 * @uml.associationEnd  multiplicity="(0 -1)" elementType="java.lang.String"
	 */
	Queue<String> msgs = new LinkedList<String>(); 	//--ArrayDeque or ArrayList is more usable

	public ChatServerImpl() throws RemoteException {
		try {
			LocateRegistry.createRegistry(PORT);
			System.out.println("Created Registry: " + PORT);
			InetAddress addr = InetAddress.getLocalHost();
			Naming.rebind("//"+addr.getHostAddress()+":"+PORT, this);
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public String getMessage(String clientID) throws RemoteException {
		if (msgs.isEmpty()) throw new RemoteException("no more messages");
		
		return msgs.poll();
	}
	
	@Override
	public void dropMessage(String clientID, String msg) throws RemoteException {
		if (msgs.size() >= nom) {
			msgs.poll();
		}
		msgs.add(msg);
	}

}