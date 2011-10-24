package a11;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class ReceiveClient extends Thread{
    
    Socket clientSocket;
    boolean run = true;
    BufferedReader inFromServer = null;
    
    public ReceiveClient(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }
    

    public void close(){
        run = false;
        try {
            inFromServer.close();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
    @Override
    public void run() {
        
        try {
            inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        } catch (IOException e1) {
            // TODO Auto-generated catch block
            e1.printStackTrace();
        }
        while(clientSocket.isConnected() && !clientSocket.isClosed() && run){
            try {
                String modifiedSentence;
                while(run && clientSocket.isConnected()&& (modifiedSentence = inFromServer.readLine()) != null){
                    if(modifiedSentence == "\n" || modifiedSentence == "" || clientSocket.isClosed() || !run){
                        
                    }else{ 
                        System.out.println("FROM SERVER: " + modifiedSentence);                    
                    }
                }
            }catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
                run = false;
                
            }
        }
        
    }
}
