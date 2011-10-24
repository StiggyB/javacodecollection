package server;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface MessageServerIF extends Remote {
	public String getMessage(String clientID) throws RemoteException;
	public void dropMessage(String clientID, String msg) throws RemoteException;
}
