package network;

import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

public class Server {

    /**
     * Starts a server for the SensorStations to connect to. The Server Listens for a incoming connection on port 1030.
     * If a client connects to the Server a new SensorStationThread is spun up for the client to communicate on.
     */
    public void startServer(){
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
            System.out.print("Server running with ip " + serverIP + ", waiting for client connection on Port " + port + "\n");
            while(true) {
                Socket socket = BaseStationServer.accept();
                //TODO: this should create an event so that basestation knows to update gui
                (new ReceiverThread(socket)).start(); //creats a new thread for the SensorStations to use
            }
        } catch (IOException e) {
            System.err.println(e.toString());
            System.exit(1);
        }
    }
}
