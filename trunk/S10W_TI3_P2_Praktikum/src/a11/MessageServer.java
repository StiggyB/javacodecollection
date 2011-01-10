package a11;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class MessageServer implements Runnable {
    Socket connectionSocket;
    String clientSentence;
    String modifiedSentence;
    States s;
    boolean run = true;
    boolean sysrun = true;
    BufferedReader inFromClient = null;
    DataOutputStream outToClient = null;

    public MessageServer(Socket clientConnection) {
        this.connectionSocket = clientConnection;
        s = States.REGULAR;
    }
    
    private void regular() {
        String s = clientSentence.toUpperCase() + '\n';
        try {
            outToClient.writeBytes(s);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
    private void busy() {
        String s = "Server is busy.\n";
        try {
            outToClient.writeBytes(s);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
    private void hacked() {
        String s = clientSentence.toLowerCase() + '\n';
        try {
            outToClient.writeBytes(s);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
    
    private void echo() {
        
    }

    private void reverse() {

    }

    private void lol() {

    }

    public void run() {
        try {
            inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));

        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
            sysrun = false;
            System.out.println("inFromClient caused Exception");
        }

        try {
            outToClient = new DataOutputStream(connectionSocket.getOutputStream());
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
            sysrun = false;
            System.out.println("outToClient caused Exception");
        }
        do {
            // Wait for incoming messages from client

            // Open Servers outputstream

            try {
                if ((clientSentence = inFromClient.readLine()) != null) {
                    if (clientSentence == "$null") {
                        run = false;
                        sysrun = false;
                    }
                    if(clientSentence.contains("busy")){
                        s = States.BUSY;
                    }
                }
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
                sysrun = false;
                System.out.println("inFromClient.readLine() caused Exception");
            }

            if (clientSentence == null || connectionSocket.isClosed() && !sysrun) {
                System.out.println("Client closed connection");
                run = false;
                connectionSocket = null;
            } else {
                System.out.println("Received: " + clientSentence);
                // State unterscheidung mit switch case
                switch (s) {
                    case REGULAR:
                        regular();
                        break;
                    case BUSY:
                        busy();
                        break;
                    case HACKED:
                        hacked();
                        break;
                    default:
                        break;
                }
//                modifiedSentence = clientSentence.toUpperCase() + '\n';
//                try {
//                    outToClient.writeBytes(modifiedSentence);
//                    outToClient.writeBytes("bla 2. nachricht\n");
//                    
//                } catch (IOException e) {
//                    // TODO Auto-generated catch block
//                    e.printStackTrace();
//                    sysrun = false;
//                    System.out.println("outToClient.writeBytes caused Exception");
//                }
                run = true;
            }// else
        } while (run && sysrun);
        System.out.printf("MessageServer terminating");
        for (int i = 0; i < 3; i++) {
            try {
                Thread.sleep(500);
                System.out.printf(".");
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
        System.out.printf("\n");
    }// run
}// MessageServer
