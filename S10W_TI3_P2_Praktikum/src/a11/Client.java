package a11;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.Socket;

public class Client {
    static DataOutputStream outToServer;
    static Socket clientSocket;


    // jeder client hat eine ID 8Zeichen im Nachrichten String.
    public static void main(String argv[]) throws Exception {
        String sentence;
        boolean run = true;
        System.out.println("Trying to connect on server Port " + argv[0]);
        clientSocket = new Socket("localhost", Integer.valueOf(argv[0]));
        ReceiveClient rC = new ReceiveClient(clientSocket);
        rC.start();
        System.out.println("Clients ReceiveClient started.");
        outToServer = new DataOutputStream(clientSocket.getOutputStream());
        while (run) {
            BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
            // BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            sentence = inFromUser.readLine();
            if(sentence != null){
                if (sentence.endsWith("$end")) {
                    run = false;
                    sentence = sentence.substring(0, sentence.length() - 4);
                }
                if(sentence == ""){
                }else{
                    outToServer.writeBytes(sentence + '\n');                                
                }                
            }else {
                run=false;
            }
        }
        System.out.println("Closing connection to server.");
        outToServer = new DataOutputStream(clientSocket.getOutputStream());
        outToServer.writeBytes("$null\n");
        rC.close();
        clientSocket.close();
    }
}
