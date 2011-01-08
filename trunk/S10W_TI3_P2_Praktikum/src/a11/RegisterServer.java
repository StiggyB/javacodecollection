package a11;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class RegisterServer extends Thread{

    Socket connectionSocket;
    List<Socket> clientList = new ArrayList<Socket>();
    int port;
    
    public RegisterServer(int port) {
        this.port = port;
    }
    
    public void run(){
        while(true){
            try {
                ServerSocket welcomeSocket = new ServerSocket(port);
                connectionSocket = welcomeSocket.accept();
            }catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
                System.err.println("Error initializing Server on Port "+port);
                System.exit(0);
            }//catch
            System.out.println("Connection Accepted");        
            if (connectionSocket != null) {
                clientList.add(connectionSocket);
            //Start new thread to receive clients messages
                MessageServer mS = new MessageServer(connectionSocket);
            }//if
        }//while
    }//run
}//OwnServer
