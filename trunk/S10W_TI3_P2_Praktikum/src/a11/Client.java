package a11;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.Socket;

public class Client extends Thread{
    static DataOutputStream outToServer;
    static Socket clientSocket;
    
    public void run(){
        outToServer = new DataOutputStream(clientSocket.getOutputStream());
    }
    
    public static void main(String argv[]) throws Exception
    {
     String sentence;
     String modifiedSentence;
     boolean run = true;
     clientSocket = new Socket("localhost",Integer.valueOf(argv[0]));
     while(run){
         BufferedReader inFromUser = new BufferedReader( new InputStreamReader(System.in));
         
         BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
         sentence = inFromUser.readLine();
         if(sentence.endsWith("$end")){
             run = false;
             sentence = sentence.substring(0, sentence.length()-4);
         }
         outToServer.writeBytes(sentence + '\n');
         modifiedSentence = inFromServer.readLine();
         System.out.println("FROM SERVER: " + modifiedSentence);
     }
     clientSocket.close();
    }
   }
}

