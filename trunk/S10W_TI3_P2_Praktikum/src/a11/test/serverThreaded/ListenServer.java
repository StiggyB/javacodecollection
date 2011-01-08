package a11.test.serverThreaded;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

class ListenServer extends Thread  {

    Server_Threaded source;
    ServerSocket listenSocket;
    int port;
    Socket connection;
    HandleServer handle;
    boolean again = true;


    // **************  ListenServer constructor

        ListenServer ( Server_Threaded s)  {

            super ();

            source = (Server_Threaded ) s;

        }  // end constructor


    // **************  run

        public void run  ()  {

            if ( ! ( source.portDisplay.getText () ).equals ( "" ) ) port = Integer.parseInt ( source.portDisplay.getText () );
            else port = source.DEFAULT_PORT;

            try  {

                listenSocket = new ServerSocket ( port );
                source.logDisplay.setText ( "Server started:\n  listening on port " + port + "\n\n" );

                while ( true )  {

                    Socket connection = listenSocket.accept();
                    HandleServer handleServer = new HandleServer ( connection, source );
                    handleServer.start ();

                }  // end while

        }  catch ( IOException e )  {
            e.printStackTrace ();
            source.logDisplay.setText ( "Error is opening ServerSocket\n" );
            System.exit ( 1 );
        }  // end catch


    }  // end run


    }  // end ListenServer
