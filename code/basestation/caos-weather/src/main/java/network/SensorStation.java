package network;

import java.net.Socket;

public class SensorStation {
    private Socket socket;

    public Socket getSocket() {
        return socket;
    }

    public SensorStation(Socket socket){
        this.socket = socket;
    }
}
