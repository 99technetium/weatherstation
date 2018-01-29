package com.company;

import com.google.gson.Gson;
import com.google.gson.JsonObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

public class Main {

    public static void main(String[] args) {
        int port = 1030;

        String serverIP = "";

        try {
            serverIP = InetAddress.getLocalHost().getHostAddress();
        } catch (UnknownHostException e) {
            System.out.println("Exception: " + e);
        }

        try{
            ServerSocket BaseStationServer = new ServerSocket(port);
            while(true) {
                Socket socket = BaseStationServer.accept();
                Gson gson = new Gson();

                InputStream in  =  socket.getInputStream();

                BufferedReader streamReader = new BufferedReader(new InputStreamReader(in, "UTF-8"));
                StringBuilder responseStrBuilder = new StringBuilder();

                String inputStr;
                while ((inputStr = streamReader.readLine()) != null)
                    responseStrBuilder.append(inputStr);
                System.out.println(responseStrBuilder.toString());
                JsonObject object = gson.fromJson(responseStrBuilder.toString(), JsonObject.class);

                System.out.println(gson.toJson(object));

            }
        } catch (IOException e) {
            System.err.println(e.toString());
            System.exit(1);
        }

    }
}
