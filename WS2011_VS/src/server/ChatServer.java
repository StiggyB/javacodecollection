package server;

public class ChatServer {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			ChatServerImpl impl = new ChatServerImpl();
		} catch (Exception e) {
			e.printStackTrace();
		}
		System.out.println("Server up an running...");
	}

}
