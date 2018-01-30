package network;

import com.google.gson.Gson;
import com.google.gson.JsonObject;
import com.google.gson.stream.JsonReader;
import database.DataBaseManager;
import datapoint.DataPoint;
import jsonObjects.JsonHandler;

import java.io.*;
import java.net.Socket;

public class ReceiverThread extends Thread {
    Socket sensorSocket;
    InputStream in;
    SensorStationList list;

    public ReceiverThread(Socket socket, SensorStationList list){
        sensorSocket = socket;
        this.list = list;
        try {
            in = socket.getInputStream();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void run(){
        DataBaseManager manager = new DataBaseManager();
        Gson jsonParser = new Gson();

        try {
            JsonReader reader = new JsonReader(new InputStreamReader(in, "UTF-8"));
            JsonObject commandObject = jsonParser.fromJson(reader, JsonObject.class);

            String deviceID = sensorSocket.getRemoteSocketAddress().toString();
            list.addStation(deviceID, new SensorStation(sensorSocket));

            new JsonHandler(commandObject, deviceID, sensorSocket);

            reader.close();
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
