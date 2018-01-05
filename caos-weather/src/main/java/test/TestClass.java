package test;

import database.DataBaseConfig;
import database.WeatherObject;

import java.io.IOException;

public class TestClass {

    /**
     * This is a simple test main class to be able to test the Networking,
     * and first setup process
     * @param args
     */
    public static void main(String[] args){
        DataBaseConfig config = new DataBaseConfig();
        boolean success = true;
        try {
            config.initialConfig();
        } catch (IOException e) {
            e.printStackTrace();
        }
        if(!success){
            System.out.println("the DB has not been initialized");
        }
        //Server server = new Server();
        //server.startServer();
        WeatherObject weatherObject = new WeatherObject(5, 0);
       // System.out.println("used weather api");
    }
}
