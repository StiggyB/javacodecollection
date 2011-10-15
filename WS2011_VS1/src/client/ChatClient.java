package client;

import java.math.BigInteger;
import java.security.SecureRandom;


public class ChatClient {
	
    static public void main(String args[]) {
    	SecureRandom sr = new SecureRandom();
    	ChatClientImpl c = new ChatClientImpl(new BigInteger(10, sr).toString(), 5000);
    	ClientGUI gui = new ClientGUI();
    	ClientGUIImpl guiimpl = new ClientGUIImpl(c, gui);
    	guiimpl.start();
    }
}

