package a11.test.serverThreaded;

import java.awt.Color;
import java.io.*;
import java.net.InetAddress;
import java.net.Socket;

class HandleServer extends Thread  {

    Server_Threaded source;
    Socket connection;

    InputStream inStream;
    DataInputStream inDataStream;
    OutputStream outStream;
    DataOutputStream outDataStream;

    String message;


    // **************  HandleServer constructor

        HandleServer ( Socket socket, Server_Threaded s)  {

            super ();
            connection =  socket;
            source =  s;

        }  // end constructor


    // **************  run

        public void run  ()  {

            String stringIn, stringOut;
            boolean again = true;

            InetAddress inet = connection.getInetAddress ();
            String origin = inet.getHostName ();
            int originport = connection.getPort ();

            source.logDisplay.append ( "Adding Client: \n  "+origin+":"+originport+"\n\n" );


            try  {

                outStream = connection.getOutputStream ();
                outDataStream = new DataOutputStream ( outStream );
                inStream = connection.getInputStream ();
                inDataStream = new DataInputStream ( inStream );

                while ( true )  {

                    message = inDataStream.readUTF ();
                    source.logDisplay.append ( "  Message, below, received\n" );
                    source.msgDisplay.setForeground ( Color.red );
                    source.msgDisplay.setText ( message );

                    outDataStream.writeUTF ( message );
                    source.logDisplay.append ( "  Message returned to client \n\n" );

                }  // end while

            }  // end try

            catch ( EOFException except ) {
                source.logDisplay.append ( "  Connection closed by Client\n\n" );
                try  {
                    connection.close ();
                    return;
                }
                catch ( IOException e )  {
                    e.printStackTrace ();
                    return;
                }  // end IOException

             }  // end catch EOFException
             catch ( IOException e )  {
                source.logDisplay.append ( "  Connection closed abormally\n" );
                e.printStackTrace ();
                return;
             }  // end catch IOException


        }  // end run


    }  // end HandleServer
