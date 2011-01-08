package a11.test;

import java.io.*;
import java.net.*;

class TCPServer {
    
    
    public static void main(String argv[]) throws Exception {
        String clientSentence = null;;
        String capitalizedSentence;
        ServerSocket welcomeSocket = new ServerSocket(6789);
        Socket connectionSocket = null;
        boolean run = true;
        while (true) {
            while (true) {
                connectionSocket = welcomeSocket.accept();
                System.out.println("Connection Accepted");
                if (connectionSocket != null) {
                    break;
                }
            }
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
                    capitalizedSentence = clientSentence.toUpperCase() + '\n';
                    outToClient.writeBytes(capitalizedSentence);   
                    run = true;
                }
            }while(run);
        }
    }
}