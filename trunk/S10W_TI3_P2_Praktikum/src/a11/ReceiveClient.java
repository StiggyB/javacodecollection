package a11;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;

public class ReceiveClient {
    
    Socket clientSocket;
    
    public ReceiveClient(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }
    
    BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
}
