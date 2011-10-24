package server;

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
		
		System.out.println("Server up an running...");
		
	}

}
