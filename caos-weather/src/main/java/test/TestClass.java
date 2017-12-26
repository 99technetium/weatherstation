package test;

import database.WeatherObject;

public class TestClass {

    /**
     * This is a simple test main class to be able to test the Networking,
     * and first setup process
     * @param args
     */
    public static void main(String[] args){
        WeatherObject weatherObject = new WeatherObject(5, 0);
        System.out.println("used weather api");
    }
}
