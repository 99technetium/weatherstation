package network;

import datapoint.DataPoint;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;

public class ReceiverThread extends Thread {
    Socket sensorSocket;
    InputStream in;
    public ReceiverThread(Socket socket){
        sensorSocket = socket;
        try {
            in = socket.getInputStream();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void run(){
        SensorStationList list = SensorStationList.getInstance();
        DataPoint dataPoint = null;
        String deviceID = dataPoint.getDeviceID();
        list.addStation(deviceID, new SensorStation(sensorSocket));
    }
}
