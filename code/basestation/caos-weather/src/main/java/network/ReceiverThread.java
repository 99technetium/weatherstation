package network;

import com.google.gson.Gson;
import com.google.gson.JsonObject;
import database.DataBaseManager;
import datapoint.DataPoint;
import jsonObjects.JsonHandler;

import java.io.*;
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
        DataBaseManager manager = new DataBaseManager();
        SensorStationList list = SensorStationList.getInstance();
        Gson jsonParser = new Gson();

        try {
            BufferedReader streamReader = new BufferedReader(new InputStreamReader(in, "UTF-8"));
            StringBuilder responseStrBuilder = new StringBuilder();

            String inputStr;
            while ((inputStr = streamReader.readLine()) != null)
                responseStrBuilder.append(inputStr);
            JsonObject commandObject = jsonParser.fromJson(responseStrBuilder.toString(), JsonObject.class);

            String deviceID = sensorSocket.getRemoteSocketAddress().toString();

            System.out.println(commandObject.get("1"));

            new JsonHandler(commandObject, deviceID);

            list.addStation(deviceID, new SensorStation(sensorSocket));
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
