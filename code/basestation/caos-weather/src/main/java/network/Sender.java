package network;

import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.Socket;

public class Sender{
    String jsonCommand;
    OutputStream out;

    public Sender(String deviceID, String jsonCommand, Socket sensorSocket){
        this.jsonCommand = jsonCommand;

        try {
            out = sensorSocket.getOutputStream();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void send() {

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
