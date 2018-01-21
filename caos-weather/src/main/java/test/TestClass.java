package test;

import database.DataBaseConfig;
import database.DataBaseSetup;
import database.WeatherObject;

import java.io.IOException;

public class TestClass {

    /**
     * This is a simple test main class to be able to test the Networking,
     * and first setup process
     * @param args
     */
    public static void main(String[] args){
        DataBaseSetup setup = new DataBaseSetup();

        WeatherObject weatherObject = new WeatherObject(5, 0);
       // System.out.println("used weather api");
    }
}
