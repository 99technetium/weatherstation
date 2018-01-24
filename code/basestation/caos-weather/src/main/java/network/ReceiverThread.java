package network;

import database.DataBaseManager;
import datapoint.DataPoint;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.util.Scanner;

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
        DataBaseManager manager = new DataBaseManager();
        SensorStationList list = SensorStationList.getInstance();

        Scanner scanner = new Scanner(in).useDelimiter("\\A");
        String inputString = scanner.hasNext() ? scanner.next() : "";

        DataPoint dataPoint = (new JsonHandler(inputString)).getDatapoint();

        manager.addDataPoint(dataPoint);

        int deviceID = dataPoint.getDeviceID();
        list.addStation(deviceID, new SensorStation(sensorSocket));
    }
}
