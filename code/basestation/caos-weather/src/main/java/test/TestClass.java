package test;

import database.DataBaseConfig;
import database.DataBaseManager;
import database.DataBaseSetup;
import database.WeatherObject;
import datapoint.DataPoint;

import java.util.List;

public class TestClass {

    /**
     * This is a simple main class to be able to test the Networking,
     * first setup process and database queries
     * @param args
     */
    public static void main(String[] args){
        DataBaseConfig config = new DataBaseConfig();

        if(!config.isDbConfiged()){
            new DataBaseSetup();
        }

        DataBaseManager manager = new DataBaseManager();
        manager.addDataPoint(new DataPoint(124132, 2, 3, 4, 20180124, 1511));
        manager.addDataPoint(new DataPoint(436513, 2, 3, 4, 20180120, 1511));
        manager.addDataPoint(new DataPoint(234366, 2, 3, 123, 20180123, 1511));


        WeatherObject weatherObject = new WeatherObject(20180122, 20180125);

        List<DataPoint> dataPoints = weatherObject.getByType(3);

        for (DataPoint d : dataPoints) {
            System.out.println(d.getDeviceID());
        }

       // System.out.println("used weather api");
    }
}
