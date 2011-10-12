package client;


public class ChatClient {
	
    static public void main(String args[]) {
    	ChatClientImpl c = new ChatClientImpl();
    }

	/**
	 * @uml.property  name="chatClientImpl"
	 * @uml.associationEnd  inverse="chatClient:client.ChatClientImpl"
	 */
	private ChatClientImpl chatClientImpl;

	/**
	 * Getter of the property <tt>chatClientImpl</tt>
	 * @return  Returns the chatClientImpl.
	 * @uml.property  name="chatClientImpl"
	 */
	public ChatClientImpl getChatClientImpl() {
		return chatClientImpl;
	}

	/**
	 * Setter of the property <tt>chatClientImpl</tt>
	 * @param chatClientImpl  The chatClientImpl to set.
	 * @uml.property  name="chatClientImpl"
	 */
	public void setChatClientImpl(ChatClientImpl chatClientImpl) {
		this.chatClientImpl = chatClientImpl;
	}

}
