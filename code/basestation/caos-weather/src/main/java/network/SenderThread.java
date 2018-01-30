package network;

import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.Socket;

public class SenderThread extends Thread{
    String jsonCommand;
    OutputStream out;

    public SenderThread(String deviceID, String jsonCommand){
        this.jsonCommand = jsonCommand;

        SensorStation sensorStation = SensorStationList.getInstance().getSensorStation(deviceID);
        Socket sensorSocket = sensorStation.getSocket();

        try {
            out = sensorSocket.getOutputStream();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void run() {

        try {
            OutputStreamWriter outputStreamWriter = new OutputStreamWriter(out, "UTF-8");
            outputStreamWriter.write(jsonCommand);
            outputStreamWriter.close();
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
