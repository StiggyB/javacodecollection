package server;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.rmi.server.RemoteServer;


public class ChatServer {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		System.out.println("Setting up server...");
		try {
			ChatServerImpl impl = new ChatServerImpl();
			impl.setUp();
		} catch (Exception e) {
			e.printStackTrace();
		}
		System.getProperties().put("java.rmi.server.logCalls","true");
		FileOutputStream logFile = null;
		try {
			logFile = new FileOutputStream(new File("src/server/logfile.txt"));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		RemoteServer.setLog(logFile);
		System.out.println("Server up an running...");
	}
}
