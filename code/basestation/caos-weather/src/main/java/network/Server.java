package network;

import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

public class Server extends Thread {

    /**
     * Starts a server for the SensorStations to connect to. The Server Listens for a incoming connection on port 1030.
     * If a client connects to the Server a new SensorStationThread is spun up for the client to communicate on.
     */
    public void run(){
        int connectedUsers = 1;
        int port = 1030;

        String serverIP = "";

        try {
            serverIP = InetAddress.getLocalHost().getHostAddress();
        } catch (UnknownHostException e) {
            System.out.println("Exception: " + e);
        }

        try{
            ServerSocket BaseStationServer = new ServerSocket(port);
            System.out.println("Server running with ip " + serverIP);
            while(true) {
                Socket socket = BaseStationServer.accept();
                (new ReceiverThread(socket)).start(); //creats a new thread for the SensorStations to use
            }
        } catch (IOException e) {
            System.err.println(e.toString());
            System.exit(1);
        }
    }
}
