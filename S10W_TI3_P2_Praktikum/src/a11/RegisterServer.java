package a11;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ThreadPoolExecutor;

public class RegisterServer extends Thread {

    Socket connectionSocket;
//    List<Socket> clientList = new ArrayList<Socket>();
    int port;
    ThreadPoolExecutor tPE;
    ServerSocket welcomeSocket;

    public RegisterServer(int port, ThreadPoolExecutor tPE) {
        this.port = port;
        this.tPE = tPE;
        try {
            welcomeSocket = new ServerSocket(port);
            System.out.println("Server initialized on Port: " + port);
        } catch (IOException e) {
            System.err.println("Server initialisation on Port: " + port + " failed!");
            e.printStackTrace();
            System.exit(0);
        }
        
    }

    public void run() {
        while (true) {
            
                try {
                    connectionSocket = welcomeSocket.accept();
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            System.out.println("Connection Accepted");
            if (connectionSocket != null) {
//                clientList.add(connectionSocket);
                // Start new thread to receive clients messages
                MessageServer mS = new MessageServer(connectionSocket);
                tPE.submit(mS);
            }// if
        }// while
    }// run
}// OwnServer
