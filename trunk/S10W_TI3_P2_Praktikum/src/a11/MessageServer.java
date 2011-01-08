package a11;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class MessageServer {
    Socket connectionSocket;
    String clientSentence;
    String modifiedSentence;
    boolean run = true;
    
    public MessageServer(Socket clientConnection) {
        this.connectionSocket = clientConnection;
    }
    
    public void run() throws IOException{
        
        do {
            
            BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket
                    .getInputStream()));
            DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
            clientSentence = inFromClient.readLine();
            if(clientSentence == null){
                System.out.println("Client closed connection");
                run = false;
                connectionSocket = null;
            }else{
                System.out.println("Received: " + clientSentence);
                modifiedSentence = clientSentence.toUpperCase() + '\n';
                outToClient.writeBytes(modifiedSentence);   
                outToClient.writeBytes("Goodbye.");   
                run = true;
            }
        }while(run);
    }

}
