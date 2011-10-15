package server;

import java.net.InetAddress;
import java.net.MalformedURLException;
import java.net.UnknownHostException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayDeque;
import java.util.HashMap;
import java.util.Map;
import java.util.Queue;
import java.util.concurrent.atomic.AtomicInteger;

import client.ClientData;

public class ChatServerImpl extends UnicastRemoteObject implements
		MessageServerIF {

	//TODO Error reaction to implement - maybe more ;)!
	//TODO Log-file creation to implement!

	private static final long serialVersionUID = -4917373673314532190L;
	public static final int PORT = Registry.REGISTRY_PORT;
	private static final long MAX_REMEM_TIME = 10000;

	private static AtomicInteger idCnt = new AtomicInteger(0);

	private Map<String, ClientData> clientDataMap;
	private Queue<Message> msgs;
	private int nom;		//TODO Should be possbl to set over the gui

	public ChatServerImpl(int nom) throws RemoteException {
		this.clientDataMap = new HashMap<String, ClientData>();
		this.msgs = new ArrayDeque<Message>();
		this.nom = nom;
	}

	public ChatServerImpl() throws RemoteException {
		this(5);
	}

	public void setUp() {
		try {
			LocateRegistry.createRegistry(PORT);
			System.out.println("Created Registry: " + PORT);
			InetAddress addr;
			addr = InetAddress.getLocalHost();
			Naming.rebind("//" + addr.getHostAddress() + ":" + PORT
					+ "/MessageServer", this);
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (RemoteException e) {
			e.printStackTrace();
		} catch (MalformedURLException e) {
			e.printStackTrace();
		}
	}

	@Override
	public String getMessage(String clientID) throws RemoteException {
		ClientData tmpClData;
		checkClientTime();
		if (!(existsClient(clientID))) {
			System.out.println("cID:" + clientID);
			tmpClData = new ClientData(clientID, MAX_REMEM_TIME);
			clientDataMap.put(clientID, tmpClData);
		}
		if (msgs.isEmpty())
			throw new RemoteException("no more messages");
		tmpClData = clientDataMap.get(clientID);
		for (Message msgIt : msgs) {
			if (!(tmpClData.getClientMsgs().contains(msgIt))) {
				System.out.println("recv: " + msgIt.getMsg());
				tmpClData.addMsg(msgIt);
				tmpClData.setRememTime(System.currentTimeMillis());
				return msgIt.toString();
			}
		}
		tmpClData.setRememTime(System.currentTimeMillis());
		throw new RemoteException("no more messages");
	}

    /**
     * This method implements the function to send
     * messages to the server. That works over the
     * java.rmi as a call method.
     * The <i>at most once</i> error handling
     * implements the java.rmi over the RemoteExceptions
     * @see http://download.oracle.com/javase/1.4.2/docs/api/index.html 
     */
	@Override
	public void dropMessage(String clientID, String msg) throws RemoteException {
		ClientData tmpClData;
		if (!(existsClient(clientID))) {
			System.out.println("cID:" + clientID);
			tmpClData = new ClientData(clientID, MAX_REMEM_TIME);
			clientDataMap.put(clientID, tmpClData);
		}
		if (msgs.size() >= nom) {
			msgs.poll();
		}
		System.out.println("MSG: " + msg);
		msgs.add(new Message(idCnt.getAndIncrement(), clientID, msg));
	}

	private boolean existsClient(String clientID) {
		return clientDataMap.isEmpty() ? false : clientDataMap
				.containsKey(clientID);
	}
	
	private void checkClientTime() {
		if (!(clientDataMap.isEmpty())) {
			for (String client : clientDataMap.keySet()) {
				if (Math.abs((clientDataMap.get(client).getRememTime() - System
						.currentTimeMillis())) > MAX_REMEM_TIME) {
					clientDataMap.remove(client);
					client = null; // -- be sure that all references are deleted
									// ->ConcurrentModificationException!
				}
			}
		}
	}
}