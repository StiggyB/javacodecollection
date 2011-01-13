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
    Reaction r;
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
//        String s = clientSentence.toLowerCase() + '\n';
        String s = clientSentence.CASE_INSENSITIVE_ORDER.toString();
        try {
            outToClient.writeBytes(s);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
    
    private void echo() {
        String s = clientSentence;
        try {
            outToClient.writeBytes(s);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        this.r = Reaction.REVERSE;
    }

    private void reverse() {
        String s = new StringBuffer(clientSentence).reverse().toString();
        try {
            outToClient.writeBytes(s);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        this.r = Reaction.LOL;
    }

    private void lol() {
        char [] vocale = new char[]{'a','e','i','o','u','�','�','�'};
        String s = clientSentence.toLowerCase();
        char work;
        for(int i = 0; i < s.length(); i++){
            work = s.charAt(i);
            
            boolean match = false;
            for(int j = 0; j < vocale.length; j++){
                if(work != vocale[j]){
                    match = true;
                }
            }
            if(match){
                String sub1 = s.substring(0, i);
                String sub2 = s.charAt(i) + "o" + s.charAt(i);
                String sub3 = s.substring(i+2, s.length());
                s = sub1 + sub2 + sub3;
                i+=2;
            }
            
        }
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
