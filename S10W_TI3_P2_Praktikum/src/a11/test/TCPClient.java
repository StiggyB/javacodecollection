package a11.test;

import java.io.*;
import java.net.*;

class TCPClient
{
 public static void main(String argv[]) throws Exception
 {
  String sentence;
  String modifiedSentence;
  boolean run = true;
  Socket clientSocket = new Socket("localhost",8901/*6789*/);
  while(run){
      BufferedReader inFromUser = new BufferedReader( new InputStreamReader(System.in));
      DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
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